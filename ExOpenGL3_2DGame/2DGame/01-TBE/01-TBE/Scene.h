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


	void initStartMenu();
	void initStartControls();
	void initStartPause();
	void initStartGameover();
	void initStartPlaying(int levelNum);

	void updateMenu(int deltaTime);
	void updateControls(int deltaTime);
	void updatePause(int deltaTime);
	void updateGameover(int deltaTime);
	void updatePlaying(int deltaTime);

	void update(int deltaTime);
	void render();
	void switchGodMode();
	void openBarriers();
	string getState();
	void setState(string newState);
	bool getGodmode();

private:
	void initShaders();
	void checkMinAndMaxCoords();
	void clearComponents();
	void resetCameraCenter();

	void loadLvl0Objects();
	void loadLvl1Objects();
	void loadLvl2Objects();
	void loadLvl3Objects();
	void loadLvl4Objects();
	void loadLvl5Objects();

private:
	irrklang::ISoundEngine* soundEngine;
	irrklang::ISound* snd;
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
	//glm::ivec2 minCoord;
	//glm::ivec2 maxCoord;
	glm::ivec2 cameraCenter;
	float zoomOut = 1.0f;
	int currentLevel = 0;
	bool godMode = false;
	std::vector<Barrier*> barriers;
	Sea* sea;
	float finishTimer;
	int numSelect = 0;
	glm::vec2 playerInitPos;
	glm::vec2 playerInvInitPos;

	glm::vec2 iniPosSelectorMenu, iniPosSelectorPause, iniPosSelectorGameover;

	Texture spritesheet, spritesheetSelector, spritesheetControls;
	Sprite* sprite, *spriteSelector, * spriteControls;
	string state = "GAMEOVER"; //MENU, CONTROLS, PLAYING, GAMEOVER, PAUSE
};


#endif // _SCENE_INCLUDE

