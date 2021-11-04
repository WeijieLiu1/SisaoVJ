#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <irrKlang.h>
#include "ShaderProgram.h"
#include "EventQueue.h"
#include "TileMap.h"
#include "Player.h"
#include "Sky.h"
#include "ObjectsController.h"
#include "Object.h"
#include "Spikes.h"
#include "Star.h"
#include "Sea.h"
#include "Barrier.h"
#include "BarrierOpener.h"
#include "Box.h"


#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(int levelNum = 0);
	void update(int deltaTime);
	void render();
	void switchGodMode();
	void openBarriers();
private:
	void initShaders();
	void clearComponents();
	void loadLvl0Objects();
	void loadLvl1Objects();
	void loadLvl2Objects();
private:
	irrklang::ISoundEngine* soundEngine;
	TileMap *map;
	ObjectsController *objectsController;
	CollisionEngine* collisionengine;
	Player* player;
	Player* playerInv;
	Sky* sky;
	Sky* skyInv;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	glm::vec2 camOffset;
	int currentLevel = 0;
	bool godMode = false;
	std::vector<Barrier*> barriers;
	Sea* sea;
	float finishTimer;
};


#endif // _SCENE_INCLUDE

