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
	if(map != NULL)
		delete map;
	if (player != NULL) delete player;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(0,0), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	playerInv = new Player();
	playerInv->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, true);
	playerInv->setPosition(glm::vec2(INIT_INV_PLAYER_X_TILES * map->getTileSize(), INIT_INV_PLAYER_Y_TILES * map->getTileSize()));
	playerInv->setTileMap(map);
	//projection = glm::ortho(-float(CAMERA_WIDTH - 1 + 320), float(CAMERA_WIDTH - 1+320), float(CAMERA_HEIGHT - 1+320), -float(CAMERA_HEIGHT - 1 + 320));
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1 + 32), float(CAMERA_HEIGHT - 1 + 32), 0.f);
	currentTime = 0.0f;
	camOffset = glm::vec2(0, 0);
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	map->update(deltaTime);
	player->update(deltaTime);
	playerInv->update(deltaTime);
	//ÒÆ¶¯»­Ãæ
	if (player->getPosition().x - camOffset.x > float(CAMERA_WIDTH - 1)*2/3) camOffset.x += 2;
	if (player->getPosition().x - camOffset.x < float(CAMERA_WIDTH - 1) / 3) camOffset.x -= 2;
}

void Scene::render()
{
	glm::mat4 modelview = glm::mat4(1.0f);;
	//modelview = glm::scale(modelview, glm::vec3(1.0f, -1.0f, 1.0f));
	texProgram.use();
	auto projAux = glm::translate(projection, glm::vec3(-camOffset, 0));
	texProgram.setUniformMatrix4f("projection", projAux);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//modelview = glm::mat4(1.0f);
	//modelview = glm::scale(modelview, glm::vec3(1.0f, 1.0f, 1.0f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	playerInv->render_inv_y();
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



