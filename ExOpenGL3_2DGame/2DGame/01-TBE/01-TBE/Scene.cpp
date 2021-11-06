#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 4

#define INIT_INV_PLAYER_X_TILES 4
#define INIT_INV_PLAYER_Y_TILES 12
Scene::Scene()
{
	map = NULL;
	player = NULL;
	soundEngine = irrklang::createIrrKlangDevice();
}

Scene::~Scene()
{
	clearComponents();
}



void Scene::init(int levelNum)
{
	clearComponents();
	if(!snd) snd = soundEngine->play2D("sounds/inflatableIsland.wav", true, false, true);
	auto a = snd->getIsPaused();
	snd->setIsPaused(false);
	auto b = snd->getIsPaused();

	if (snd)
	{
		snd->setVolume(0.5f);
	}
	currentLevel = levelNum;
	initShaders();
	collisionengine = new CollisionEngine();

	if (currentLevel == 0)loadLvl0Objects();
	else if(currentLevel == 1) loadLvl1Objects();
	else if(currentLevel == 2) loadLvl2Objects();
	else if(currentLevel == 3) loadLvl3Objects();
	else if(currentLevel == 4) loadLvl4Objects();
	else if(currentLevel == 5) loadLvl5Objects();
	else loadLvl0Objects();

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(playerInitPos);
	player->setCollEngine(collisionengine);
	player->setSoundEngine(soundEngine);
	playerInv = new Player();
	playerInv->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, true);
	playerInv->setPosition(playerInvInitPos);
	playerInv->setCollEngine(collisionengine);
	playerInv->setSoundEngine(soundEngine);
	//playerInv->setTileMap(map);
	// 
	//projection = glm::ortho(-float(CAMERA_WIDTH - 1 + 320), float(CAMERA_WIDTH - 1+320), float(CAMERA_HEIGHT - 1+320), -float(CAMERA_HEIGHT - 1 + 320));
	checkMinAndMaxCoords();
	//projection = glm::ortho(float(std::max(minCoord.x-15,0)), float(std::max(maxCoord.x,CAMERA_WIDTH - 1)), 
	//	float(std::max(maxCoord.y,CAMERA_HEIGHT - 1)), float(std::min(minCoord.y,0)));
	currentTime = 0.0f;


}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	sky->update(deltaTime);
	skyInv->update(deltaTime);
	map->update(deltaTime);
	EventQueue aux = objectsController->update(deltaTime);
	EventQueue aux2 = player->update(deltaTime);
	while (!aux2.queue.empty())
	{
		aux.queue.push(aux2.queue.front());
		aux2.queue.pop();
	}
	aux2 = playerInv->update(deltaTime);
	while (!aux2.queue.empty())
	{
		aux.queue.push(aux2.queue.front());
		aux2.queue.pop();
	}
	checkMinAndMaxCoords();

	while (!aux.queue.empty())
	{
		if (aux.queue.front() == EventQueue::playerDead && !godMode)
		{
			//init(currentLevel);
			player->kill();
			playerInv->kill();
		}
		else if (aux.queue.front() == EventQueue::RestartLevel)
		{
			init(currentLevel);
		}
		else if (aux.queue.front() == EventQueue::levelCompleted)
		{
			if (currentLevel >= 5) currentLevel = 1;
			init(currentLevel +1);
		}
		aux.queue.pop();
	}
}

void Scene::render()
{
	sky->render();
	skyInv->render();
	glm::mat4 modelview = glm::mat4(1.0f);;
	//modelview = glm::scale(modelview, glm::vec3(1.0f, -1.0f, 1.0f));
	texProgram.use();
	checkMinAndMaxCoords();
	projection = glm::ortho(float(zoomOut*(cameraCenter.x - CAMERA_WIDTH/2)), float(zoomOut * (cameraCenter.x + CAMERA_WIDTH / 2)),
		float(zoomOut * (cameraCenter.y + CAMERA_HEIGHT / 2)), float(zoomOut * (cameraCenter.y - CAMERA_HEIGHT / 2)));
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//modelview = glm::mat4(1.0f);
	//modelview = glm::scale(modelview, glm::vec3(1.0f, 1.0f, 1.0f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	objectsController->render();
	player->render();
	playerInv->render_inv_y();
	sea->lateRender();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}
void Scene::checkMinAndMaxCoords()
{
	auto cor1 = player->getPosition();
	auto cor2 = playerInv->getPosition();
	auto minCoord = cor1;
	if (cor2.x < minCoord.x) minCoord.x = cor2.x;
	if (cor2.y < minCoord.y) minCoord.y = cor2.y;
	auto maxCoord = cor1;
	if (cor2.x > maxCoord.x) maxCoord.x = cor2.x;
	if (cor2.y > maxCoord.y) maxCoord.y = cor2.y;
	cameraCenter = glm::vec2((minCoord.x-32 + maxCoord.x) / 2, (minCoord.y + maxCoord.y) / 2);
	float ratioW = (64+maxCoord.x - minCoord.x)/CAMERA_WIDTH;
	float ratioH = (maxCoord.y+32 - minCoord.y)/CAMERA_HEIGHT;
	zoomOut = std::max(ratioH, ratioW);
	zoomOut = std::max(zoomOut, 1.0f);

	if (zoomOut > 200) zoomOut = 200;
}
void Scene::clearComponents()
{
	if (map != NULL)
		delete map;
	if (player != NULL) delete player;
	if (playerInv != NULL) delete playerInv;
	if (objectsController != NULL) delete objectsController;
	//soundEngine->stopAllSounds();
}

void Scene::loadLvl0Objects()
{
	objectsController = new ObjectsController();
	Spikes* sp = new Spikes(glm::ivec2(224, 128), texProgram, 3);
	sp->setSoundEngine(soundEngine);
	objectsController->addObject(sp);
	Spikes* sk = new Spikes(glm::ivec2(320, 192), texProgram, 2);
	sk->setSoundEngine(soundEngine);
	objectsController->addObject(sk);
	//Box* sp1 = new Box(glm::ivec2(288, 320), texProgram, true);
	//objectsController->addObject(sp1);
	Box* sp2 = new Box(glm::ivec2(192, 320), texProgram, true);
	objectsController->addObject(sp2);
	Box* sp3 = new Box(glm::ivec2(356, 128), texProgram, false);
	objectsController->addObject(sp3);
	Star* st1 = new Star(glm::ivec2(256, 352), texProgram, true);
	objectsController->addObject(st1);
	st1->setSoundEngine(soundEngine);
	Star* st2 = new Star(glm::ivec2(256, 128), texProgram, false);
	objectsController->addObject(st2);
	st2->setSoundEngine(soundEngine);
	Barrier* b1 = new Barrier(glm::ivec2(416, 96), texProgram);
	objectsController->addObject(b1);
	barriers.push_back(b1);
	BarrierOpener* bo1 = new BarrierOpener(glm::ivec2(256, 192), texProgram, b1);
	bo1->setSoundEngine(soundEngine);
	objectsController->addObject(bo1);
	sea = new Sea(glm::ivec2(-500, 240), texProgram);
	objectsController->addObject(sea);
	sea->setSoundEngine(soundEngine);

	collisionengine->setObjectsController(objectsController);

	map = TileMap::createTileMap("levels/level00.txt", glm::vec2(0, 0), texProgram);
	collisionengine->setTileMap(map);
	sp3->setTilemap(map);
	sp2->setTilemap(map);
	objectsController->setTileSize(map->getTileSize());
	int tileSize = map->getTileSize();
	glm::vec2 auxSize = glm::vec2(map->getMapSize().x * tileSize + 320, map->getMapSize().y / 2 * tileSize);
	sky = new Sky(glm::ivec2(-320, 0), auxSize, texProgram);
	skyInv = new Sky(glm::ivec2(-320, map->getMapSize().y * tileSize - 33), auxSize, texProgram, true);

	sp2->setObjectsToCollide(objectsController->getAllObjects());
	sp3->setObjectsToCollide(objectsController->getAllObjects());
	playerInitPos = glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize());
	playerInvInitPos = glm::vec2(INIT_INV_PLAYER_X_TILES * map->getTileSize(), INIT_INV_PLAYER_Y_TILES * map->getTileSize());
}

void Scene::loadLvl1Objects()
{
	objectsController = new ObjectsController();
	Star* st1 = new Star(glm::ivec2(576, 352), texProgram, true);
	objectsController->addObject(st1);
	st1->setSoundEngine(soundEngine);
	Star* st2 = new Star(glm::ivec2(576, 128), texProgram, false);
	objectsController->addObject(st2);
	st2->setSoundEngine(soundEngine);
	sea = new Sea(glm::ivec2(-500, 240), texProgram);
	objectsController->addObject(sea);
	sea->setSoundEngine(soundEngine);

	collisionengine->setObjectsController(objectsController);

	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(0, 0), texProgram);
	collisionengine->setTileMap(map);
	objectsController->setTileSize(map->getTileSize());
	int tileSize = map->getTileSize();
	glm::vec2 auxSize = glm::vec2(map->getMapSize().x * tileSize + 320, map->getMapSize().y / 2 * tileSize);
	sky = new Sky(glm::ivec2(-320, 0), auxSize, texProgram);
	skyInv = new Sky(glm::ivec2(-320, map->getMapSize().y * tileSize - 33), auxSize, texProgram, true);
	playerInitPos = glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize());
	playerInvInitPos = glm::vec2(INIT_INV_PLAYER_X_TILES * map->getTileSize(), INIT_INV_PLAYER_Y_TILES * map->getTileSize());
}

void Scene::loadLvl2Objects()
{
	objectsController = new ObjectsController();
	Star* st1 = new Star(glm::ivec2(576, 352-32), texProgram, true);
	objectsController->addObject(st1);
	st1->setSoundEngine(soundEngine);
	Star* st2 = new Star(glm::ivec2(576, 128), texProgram, false);
	objectsController->addObject(st2);
	st2->setSoundEngine(soundEngine);

	Spikes* sp1 = new Spikes(glm::ivec2(384, 128), texProgram, 3);
	sp1->setSoundEngine(soundEngine);
	objectsController->addObject(sp1);
	Spikes* sp2 = new Spikes(glm::ivec2(384+32, 128), texProgram, 3);
	sp2->setSoundEngine(soundEngine);
	objectsController->addObject(sp2);
	Spikes* sp3 = new Spikes(glm::ivec2(384+64, 128), texProgram, 3);
	sp3->setSoundEngine(soundEngine);
	objectsController->addObject(sp3);

	sea = new Sea(glm::ivec2(-500, 240), texProgram);
	objectsController->addObject(sea);
	sea->setSoundEngine(soundEngine);

	collisionengine->setObjectsController(objectsController);

	map = TileMap::createTileMap("levels/level02.txt", glm::vec2(0, 0), texProgram);
	collisionengine->setTileMap(map);
	objectsController->setTileSize(map->getTileSize());
	int tileSize = map->getTileSize();
	glm::vec2 auxSize = glm::vec2(map->getMapSize().x * tileSize + 320, map->getMapSize().y / 2 * tileSize);
	sky = new Sky(glm::ivec2(-320, 0), auxSize, texProgram);
	skyInv = new Sky(glm::ivec2(-320, map->getMapSize().y * tileSize - 33), auxSize, texProgram, true);
	playerInitPos = glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize());
	playerInvInitPos = glm::vec2(INIT_INV_PLAYER_X_TILES * map->getTileSize(), INIT_INV_PLAYER_Y_TILES * map->getTileSize());
}
void Scene::loadLvl3Objects()
{
	objectsController = new ObjectsController();
	Star* st1 = new Star(glm::ivec2(576-5*32, 288), texProgram, true);
	objectsController->addObject(st1);
	st1->setSoundEngine(soundEngine);
	Star* st2 = new Star(glm::ivec2(576-3*32, 96), texProgram, false);
	objectsController->addObject(st2);
	st2->setSoundEngine(soundEngine);

	
	Spikes* sp1 = new Spikes(glm::ivec2(384 + 128, 128), texProgram, 1);
	sp1->setSoundEngine(soundEngine);
	objectsController->addObject(sp1);
	Barrier* b1 = new Barrier(glm::ivec2(96, 356), texProgram);
	objectsController->addObject(b1);
	barriers.push_back(b1);
	BarrierOpener* bo1 = new BarrierOpener(glm::ivec2(256+2*32, 192-4*32), texProgram, b1);
	bo1->setSoundEngine(soundEngine);
	objectsController->addObject(bo1);
	Box* sp3 = new Box(glm::ivec2(32, 128+7*32), texProgram, true);
	objectsController->addObject(sp3);


	sea = new Sea(glm::ivec2(-500, 240), texProgram);
	objectsController->addObject(sea);
	sea->setSoundEngine(soundEngine);

	collisionengine->setObjectsController(objectsController);

	map = TileMap::createTileMap("levels/level03.txt", glm::vec2(0, 0), texProgram);
	collisionengine->setTileMap(map);
	objectsController->setTileSize(map->getTileSize());
	int tileSize = map->getTileSize();
	glm::vec2 auxSize = glm::vec2(map->getMapSize().x * tileSize + 320, map->getMapSize().y / 2 * tileSize);
	sky = new Sky(glm::ivec2(-320, 0), auxSize, texProgram);
	skyInv = new Sky(glm::ivec2(-320, map->getMapSize().y * tileSize - 33), auxSize, texProgram, true);

	sp3->setObjectsToCollide(objectsController->getAllObjects());
	sp3->setTilemap(map);
	playerInitPos = glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize());
	playerInvInitPos = glm::vec2(INIT_INV_PLAYER_X_TILES * map->getTileSize(), INIT_INV_PLAYER_Y_TILES * map->getTileSize());
}

void Scene::loadLvl4Objects()
{
	objectsController = new ObjectsController();
	Star* st1 = new Star(glm::ivec2(576 - 4 * 32, 288), texProgram, true);
	objectsController->addObject(st1);
	st1->setSoundEngine(soundEngine);
	Star* st2 = new Star(glm::ivec2(0, 192), texProgram, false);
	objectsController->addObject(st2);
	st2->setSoundEngine(soundEngine);


	Spikes* sp1 = new Spikes(glm::ivec2(384 + 96, 128+64), texProgram, 0);
	sp1->setSoundEngine(soundEngine);
	objectsController->addObject(sp1);
	Spikes* sp2 = new Spikes(glm::ivec2(384 + 64, 128+64), texProgram, 0);
	sp2->setSoundEngine(soundEngine);
	objectsController->addObject(sp2);
	Spikes* sp3 = new Spikes(glm::ivec2(384 , 128+32), texProgram, 0);
	sp3->setSoundEngine(soundEngine);
	//objectsController->addObject(sp3);
	Spikes* sp4 = new Spikes(glm::ivec2(384 -32, 128+32), texProgram,0);
	sp4->setSoundEngine(soundEngine);
	objectsController->addObject(sp4);
	Spikes* sp5 = new Spikes(glm::ivec2(384 - 64, 128+32), texProgram, 0);
	sp5->setSoundEngine(soundEngine);
	//objectsController->addObject(sp5);
	Spikes* sp6 = new Spikes(glm::ivec2(5*32, 256+64), texProgram, 0);
	sp6->setSoundEngine(soundEngine);
	objectsController->addObject(sp6);
	Spikes* sp7 = new Spikes(glm::ivec2(6*32, 256+64), texProgram, 0);
	sp7->setSoundEngine(soundEngine);
	objectsController->addObject(sp7);
	Barrier* b1 = new Barrier(glm::ivec2(128, 96), texProgram);
	objectsController->addObject(b1);
	barriers.push_back(b1);
	BarrierOpener* bo1 = new BarrierOpener(glm::ivec2(5 * 32, 256 + 32), texProgram, b1);
	bo1->setSoundEngine(soundEngine);
	objectsController->addObject(bo1);


	sea = new Sea(glm::ivec2(-500, 240), texProgram);
	objectsController->addObject(sea);
	sea->setSoundEngine(soundEngine);

	collisionengine->setObjectsController(objectsController);

	map = TileMap::createTileMap("levels/level04.txt", glm::vec2(0, 0), texProgram);
	collisionengine->setTileMap(map);
	objectsController->setTileSize(map->getTileSize());
	int tileSize = map->getTileSize();
	glm::vec2 auxSize = glm::vec2(map->getMapSize().x * tileSize + 320, map->getMapSize().y / 2 * tileSize);
	sky = new Sky(glm::ivec2(-320, 0), auxSize, texProgram);
	skyInv = new Sky(glm::ivec2(-320, map->getMapSize().y * tileSize - 33), auxSize, texProgram, true);

	playerInitPos = glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize()+320+160, INIT_PLAYER_Y_TILES * map->getTileSize());
	playerInvInitPos = glm::vec2(INIT_INV_PLAYER_X_TILES * map->getTileSize() + 320+160, INIT_INV_PLAYER_Y_TILES * map->getTileSize());
}

void Scene::loadLvl5Objects()
{
	objectsController = new ObjectsController();
	Star* st1 = new Star(glm::ivec2(576 + 7 * 32, 352), texProgram, true);
	objectsController->addObject(st1);
	st1->setSoundEngine(soundEngine);
	Star* st2 = new Star(glm::ivec2(576 + 5 * 32, 160), texProgram, false);
	objectsController->addObject(st2);
	st2->setSoundEngine(soundEngine);

	Barrier* b1 = new Barrier(glm::ivec2(320+64, 96+6*32), texProgram);
	objectsController->addObject(b1);
	barriers.push_back(b1);
	BarrierOpener* bo1 = new BarrierOpener(glm::ivec2(8 * 32, 256 -64), texProgram, b1);
	bo1->setSoundEngine(soundEngine);
	objectsController->addObject(bo1);

	Box* sp3 = new Box(glm::ivec2(320+96, 96 + 6 * 32), texProgram, true);
	objectsController->addObject(sp3);
	Box* sp4 = new Box(glm::ivec2(320 + 96, 128), texProgram, false);
	objectsController->addObject(sp4);


	sea = new Sea(glm::ivec2(-500, 250), texProgram);
	objectsController->addObject(sea);
	sea->setSoundEngine(soundEngine);

	collisionengine->setObjectsController(objectsController);

	map = TileMap::createTileMap("levels/level05.txt", glm::vec2(0, 0), texProgram);
	collisionengine->setTileMap(map);
	objectsController->setTileSize(map->getTileSize());
	int tileSize = map->getTileSize();
	glm::vec2 auxSize = glm::vec2(map->getMapSize().x * tileSize + 320, map->getMapSize().y / 2 * tileSize);
	sky = new Sky(glm::ivec2(-320, 0), auxSize, texProgram);
	skyInv = new Sky(glm::ivec2(-320, map->getMapSize().y * tileSize - 33), auxSize, texProgram, true);

	sp3->setObjectsToCollide(objectsController->getAllObjects());
	sp3->setTilemap(map);
	sp4->setObjectsToCollide(objectsController->getAllObjects());
	sp4->setTilemap(map);

	playerInitPos = glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize() + 320 + 160, INIT_PLAYER_Y_TILES * map->getTileSize());
	playerInvInitPos = glm::vec2(INIT_INV_PLAYER_X_TILES * map->getTileSize() + 64, INIT_INV_PLAYER_Y_TILES * map->getTileSize());
}


void Scene::switchGodMode()
{
	godMode = !godMode;
}
void Scene::openBarriers()
{
	for (int i = 0; i < barriers.size(); i++)
	{
		barriers[i]->open();
	}
}
