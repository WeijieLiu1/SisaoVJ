#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "ObjectsController.h"
#include "Object.h"
#include "Spikes.h"


#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map;
	ObjectsController *objectsController;
	CollisionEngine* collisionengine;
	Player* player;
	Player* playerInv;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	glm::vec2 camOffset;
	
};


#endif // _SCENE_INCLUDE

