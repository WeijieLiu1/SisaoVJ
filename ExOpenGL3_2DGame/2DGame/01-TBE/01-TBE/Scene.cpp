#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 6

#define INIT_INV_PLAYER_X_TILES 4
#define INIT_INV_PLAYER_Y_TILES 12
Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	clearComponents();
}


void Scene::init(int levelNum)
{
	currentLevel = levelNum;
	initShaders();
	collisionengine = new CollisionEngine();

	objectsController = new ObjectsController();
	Spikes* sp = new Spikes(glm::ivec2(192, 128), texProgram,3);
	objectsController->addObject(sp);
	Spikes* sp2 = new Spikes(glm::ivec2(576, 256), texProgram,3);
	//objectsController->addObject(sp2);
	Box* sp3 = new Box(glm::ivec2(200, 64), texProgram);
	
	objectsController->addObject(sp3);
	Star* st1 = new Star(glm::ivec2(256, 320), texProgram, true);
	objectsController->addObject(st1);
	Star* st2 = new Star(glm::ivec2(256, 128), texProgram, false);
	objectsController->addObject(st2);
	Sea* sea = new Sea(glm::ivec2(0, 240), texProgram);
	objectsController->addObject(sea);

	collisionengine->setObjectsController(objectsController);

	if(levelNum == 0)map = TileMap::createTileMap("levels/level01.txt", glm::vec2(0,0), texProgram);
	else map = TileMap::createTileMap("levels/level02.txt", glm::vec2(0,0), texProgram);
	collisionengine->setTileMap(map);
	sp3->setTilemap(map);
	objectsController->setTileSize(map->getTileSize());
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setCollEngine(collisionengine);
	playerInv = new Player();
	playerInv->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, true);
	playerInv->setPosition(glm::vec2(INIT_INV_PLAYER_X_TILES * map->getTileSize(), INIT_INV_PLAYER_Y_TILES * map->getTileSize()));
	playerInv->setCollEngine(collisionengine);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	camOffset = glm::vec2(0, 0);

}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	map->update(deltaTime);
	EventQueue aux = objectsController->update(deltaTime);
	player->update(deltaTime);
	playerInv->update(deltaTime);
	if (player->getPosition().x - camOffset.x > float(CAMERA_WIDTH - 1)*2/3) camOffset.x += 2;
	if (player->getPosition().x - camOffset.x < float(CAMERA_WIDTH - 1) / 3) camOffset.x -= 2;

	while (!aux.queue.empty())
	{
		if (aux.queue.front() == EventQueue::playerDead)
		{
			clearComponents();
			init(currentLevel);
		}
		else if (aux.queue.front() == EventQueue::levelCompleted)
		{
			clearComponents();
			init(currentLevel +1);
		}
		aux.queue.pop();
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	auto projAux = glm::translate(projection, glm::vec3(-camOffset, 0));
	texProgram.setUniformMatrix4f("projection", projAux);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	objectsController->render();
	player->render();
	playerInv->render();
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

void Scene::clearComponents()
{
	if (map != NULL)
		delete map;
	if (player != NULL) delete player;
	if (playerInv != NULL) delete playerInv;
	if (objectsController != NULL) delete objectsController;
}

