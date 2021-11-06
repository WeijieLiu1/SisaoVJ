#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include <Windows.h>

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 6

#define INIT_INV_PLAYER_X_TILES 4
#define INIT_INV_PLAYER_Y_TILES 12

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
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

string Scene::getState()
{
	return state;
}

void Scene::setState(string newState) 
{
	state = newState;
}

void Scene::initStartMenu()
{
	
	// background
	spritesheet.loadFromFile("images/sonic_mainMenu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	sprite->setNumberAnimations(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));

	// selector
	spritesheetSelector.loadFromFile("images/sonic_selector.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteSelector = Sprite::createSprite(glm::ivec2(30, 20), glm::vec2(1.f, 1.f), &spritesheetSelector, &texProgram);
	spriteSelector->setNumberAnimations(0);
	spriteSelector->setPosition(iniPosSelectorMenu);

	//SoundSystem::instance().playMusic("", "MENU");
}

void Scene::initStartPause()
{

	// background
	spritesheet.loadFromFile("images/sonic_pauseMenu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	sprite->setNumberAnimations(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));

	// selector
	spritesheetSelector.loadFromFile("images/sonic_selector.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteSelector = Sprite::createSprite(glm::ivec2(30, 20), glm::vec2(1.f, 1.f), &spritesheetSelector, &texProgram);
	spriteSelector->setNumberAnimations(0);
	spriteSelector->setPosition(iniPosSelectorPause);

	//SoundSystem::instance().playMusic("", "MENU");
}

void Scene::initStartGameover()
{

	// background
	spritesheet.loadFromFile("images/sonic_Gameover.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	sprite->setNumberAnimations(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));

	// selector
	spritesheetSelector.loadFromFile("images/sonic_selector.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteSelector = Sprite::createSprite(glm::ivec2(30, 20), glm::vec2(1.f, 1.f), &spritesheetSelector, &texProgram);
	spriteSelector->setNumberAnimations(0);
	spriteSelector->setPosition(iniPosSelectorGameover);

	//SoundSystem::instance().playMusic("", "MENU");
}


void Scene::initStartControls()
{

	// background
	spritesheetControls.loadFromFile("images/sonic_controls.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteControls = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1.f, 1.f), &spritesheetControls, &texProgram);
	spriteControls->setNumberAnimations(0);
	spriteControls->setPosition(glm::vec2(float(0), float(0)));
	

	//SoundSystem::instance().playMusic("", "MENU");
}

void Scene::init(int levelNum)
{
	iniPosSelectorMenu = glm::vec2(float(135), float(265));
	iniPosSelectorPause = glm::vec2(float(135), float(200));
	iniPosSelectorGameover = glm::vec2(float(135), float(285));
	clearComponents();
	soundEngine->play2D("sounds/inflatableIsland.wav", true);
	currentLevel = levelNum;
	initShaders();
	if (state == "MENU") {
		initStartMenu();
	}
	else if (state == "CONTROLS") {
		initStartControls();
	}
	else if (state == "PAUSE") {
		initStartPause();
	}
	else if (state == "GAMEOVER") {
		initStartGameover();
	}
	else if(state == "PLAYING") {
		collisionengine = new CollisionEngine();

		objectsController = new ObjectsController();
		Spikes* sp = new Spikes(glm::ivec2(224, 128), texProgram, 3);
		objectsController->addObject(sp);
		Spikes* sk = new Spikes(glm::ivec2(320, 192), texProgram, 2);
		objectsController->addObject(sk);
		//Box* sp1 = new Box(glm::ivec2(288, 320), texProgram, true);
		//objectsController->addObject(sp1);
		Box* sp2 = new Box(glm::ivec2(192, 320), texProgram, true);
		objectsController->addObject(sp2);
		Box* sp3 = new Box(glm::ivec2(356, 128), texProgram, false);
		objectsController->addObject(sp3);
		Star* st1 = new Star(glm::ivec2(256, 352), texProgram, true);
		objectsController->addObject(st1);
		Star* st2 = new Star(glm::ivec2(256, 128), texProgram, false);
		objectsController->addObject(st2);
		Barrier* b1 = new Barrier(glm::ivec2(416, 96), texProgram);
		objectsController->addObject(b1);
		barriers.push_back(b1);
		BarrierOpener* bo1 = new BarrierOpener(glm::ivec2(256, 192), texProgram, b1);
		objectsController->addObject(bo1);
		sea = new Sea(glm::ivec2(-500, 240), texProgram);
		objectsController->addObject(sea);

		collisionengine->setObjectsController(objectsController);

		if (levelNum == 0)map = TileMap::createTileMap("levels/level01.txt", glm::vec2(0, 0), texProgram);
		else if(levelNum == 1)map = TileMap::createTileMap("levels/level02.txt", glm::vec2(0, 0), texProgram);
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

		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setCollEngine(collisionengine);
		playerInv = new Player();
		playerInv->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, true);
		playerInv->setPosition(glm::vec2(INIT_INV_PLAYER_X_TILES * map->getTileSize(), INIT_INV_PLAYER_Y_TILES * map->getTileSize()));


		//playerInv->setTileMap(map);
		//projection = glm::ortho(0.f, float(SCREEN_X - 1), float(SCREEN_Y - 1), 0.f);
		//projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1 + 32), float(CAMERA_HEIGHT - 1 + 32), 0.f);
		playerInv->setCollEngine(collisionengine);
		currentTime = 0.0f;
		camOffset = glm::vec2(0, 0);
	}
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	//camOffset = glm::vec2(0, 0);
}

void Scene::updateControls(int deltaTime) {
	sprite->update(deltaTime);
	//13 = return
	if (Game::instance().getKey(13)) {
		Sleep(400);
		state = "MENU";
		init(0);
	}
	//spriteControls->render();
	//Sleep(1000);
}

void Scene::updateMenu(int deltaTime) {
	sprite->update(deltaTime);
	//numSelect = (numSelect + 1) % 3;
	
	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		
		//numSelect = (numSelect - 1) % 3;
		numSelect = numSelect + 1;
		numSelect = numSelect % 3;
		glm::vec2 newPosSelector = iniPosSelectorMenu + glm::vec2(0, 50.f * numSelect);
		//glm::vec2 posSelector = spriteSelector->getPosition();
		//if (posSelector.y < 268) posSelector.y += 50.f;
		//posSelector.y += 5.f;
		spriteSelector->setPosition(newPosSelector);
		spriteSelector->render();
		Sleep(400);
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		numSelect = numSelect - 1;
		
		//numSelect = numSelect % 3;
		if (numSelect < 0) numSelect += 3;
		glm::vec2 newPosSelector = iniPosSelectorMenu + glm::vec2(0, 50.f * numSelect);
		//glm::vec2 posSelector = spriteSelector->getPosition();
		//if (posSelector.y > 316) posSelector.y += 50.f;
		//posSelector.y -= 5.f;
		spriteSelector->setPosition(newPosSelector);
		spriteSelector->render();
		Sleep(400);
	}
	// return key == 13
	else if (Game::instance().getKey(13)) {
		if (numSelect == 0) state = "PLAYING";
		else if (numSelect == 1) state = "CONTROLS";
		else if (numSelect == 2) exit(0);
		numSelect = 0;
		Sleep(400);
		init(0);
		
		/*
		if ((spriteSelector->getPosition()).y == 267) state = "PLAYING";
		else state = "CONTROLS";
		init();
		*/	
	}
}



void Scene::updateGameover(int deltaTime) {
	sprite->update(deltaTime);
	//numSelect = (numSelect + 1) % 3;

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {

		//numSelect = (numSelect - 1) % 3;
		numSelect = numSelect + 1;
		numSelect = numSelect % 3;
		glm::vec2 newPosSelector = iniPosSelectorGameover + glm::vec2(0, 55.f * numSelect);
		//glm::vec2 posSelector = spriteSelector->getPosition();
		//if (posSelector.y < 268) posSelector.y += 50.f;
		//posSelector.y += 5.f;
		spriteSelector->setPosition(newPosSelector);
		spriteSelector->render();
		Sleep(400);
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		numSelect = numSelect - 1;
		//numSelect = numSelect % 3;
		if (numSelect < 0) numSelect += 3;
		glm::vec2 newPosSelector = iniPosSelectorGameover + glm::vec2(0, 55.f * numSelect);
		//glm::vec2 posSelector = spriteSelector->getPosition();
		//if (posSelector.y > 316) posSelector.y += 50.f;
		//posSelector.y -= 5.f;
		spriteSelector->setPosition(newPosSelector);
		spriteSelector->render();
		Sleep(400);
	}
	// return key == 13
	else if (Game::instance().getKey(13)) {
		if (numSelect == 0) state = "PLAYING";
		else if (numSelect == 1) state = "MENU";
		else if (numSelect == 2) exit(0);
		numSelect = 0;
		Sleep(400);
		init(0);

		/*
		if ((spriteSelector->getPosition()).y == 267) state = "PLAYING";
		else state = "CONTROLS";
		init();
		*/
	}
}

void Scene::updatePause(int deltaTime) {
	sprite->update(deltaTime);
	//numSelect = (numSelect + 1) % 3;

	if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {

		//numSelect = (numSelect - 1) % 3;
		numSelect = numSelect + 1;
		numSelect = numSelect % 4;
		glm::vec2 newPosSelector = iniPosSelectorPause + glm::vec2(0, 50.f * numSelect);
		//glm::vec2 posSelector = spriteSelector->getPosition();
		//if (posSelector.y < 268) posSelector.y += 50.f;
		//posSelector.y += 5.f;
		spriteSelector->setPosition(newPosSelector);
		spriteSelector->render();
		Sleep(400);
	}

	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		numSelect = numSelect - 1;
		//numSelect = numSelect % 3;
		if (numSelect < 0) numSelect += 4;
		glm::vec2 newPosSelector = iniPosSelectorPause + glm::vec2(0, 50.f * numSelect);
		//glm::vec2 posSelector = spriteSelector->getPosition();
		//if (posSelector.y > 316) posSelector.y += 50.f;
		//posSelector.y -= 5.f;
		spriteSelector->setPosition(newPosSelector);
		spriteSelector->render();
		Sleep(400);
	}
	// return key == 13
	else if (Game::instance().getKey(13)) {
		if (numSelect == 0) state = "PLAYING";
		else if (numSelect == 1) state = "CONTROLS";
		else if (numSelect == 2) state = "MENU";
		else if (numSelect == 3) exit(0);
		numSelect = 0;
		Sleep(400);
		init(0);

		/*
		if ((spriteSelector->getPosition()).y == 267) state = "PLAYING";
		else state = "CONTROLS";
		init();
		*/
	}
}


void Scene::update(int deltaTime)
{
	if (state == "MENU") {
		updateMenu(deltaTime);
	}
	else if (state == "CONTROLS") {
		updateControls(deltaTime);
	}
	else if (state == "PAUSE") {
		updatePause(deltaTime);
	}
	else if (state == "GAMEOVER") {
		updateGameover(deltaTime);
	}
	else {
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
		if (player->getPosition().x - camOffset.x > float(CAMERA_WIDTH - 1) * 2 / 3) camOffset.x += 2;
		if (player->getPosition().x - camOffset.x < float(CAMERA_WIDTH - 1) / 3) camOffset.x -= 2;

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
				init(currentLevel + 1);
			}

			aux.queue.pop();
		}
	}
	
}

void Scene::resetCamOffset() {
	camOffset = glm::vec2(0, 0);
}

void Scene::render()
{
	

	glm::mat4 modelview = glm::mat4(1.0f);;
	//modelview = glm::scale(modelview, glm::vec3(1.0f, -1.0f, 1.0f));
	texProgram.use();
	/*
	
	
	
	*/
	auto projAux = glm::translate(projection, glm::vec3(-camOffset, 0));
	texProgram.setUniformMatrix4f("projection", projAux);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//modelview = glm::mat4(1.0f);
	//modelview = glm::scale(modelview, glm::vec3(1.0f, 1.0f, 1.0f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	if (state == "MENU") {
		sprite->render();
		spriteSelector->render();
	}
	else if (state == "CONTROLS") {
		spriteControls->render();
		
	}
	else if (state == "PAUSE") {
		sprite->render();
		spriteSelector->render();
	}
	else if (state == "GAMEOVER") {
		sprite->render();
		spriteSelector->render();
	}
	else if (state == "PLAYING") {
		sky->render();
		skyInv->render();
		map->render();
		objectsController->render();
		player->render();
		playerInv->render_inv_y();
		sea->lateRender();
	}
	/*
	map->render();
	objectsController->render();
	player->render();
	playerInv->render_inv_y();
	sea->lateRender();
	*/
	
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
	soundEngine->stopAllSounds();
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
