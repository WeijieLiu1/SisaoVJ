#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.25f, 0.25f, 0.875f, 1.0f);
	scene.setState("MENU");
	scene.initStartMenu();
	scene.init(1);
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	//if(key == 27) // Escape code
		//bPlay = false;
	string state = scene.getState();
	if (state == "PLAYING") {
		if (key == 'g')
			scene.switchGodMode();
		else if (key == 'b')
			scene.openBarriers();
		else if (key == '0') scene.init(0);
		else if (key == '1') scene.init(1);
    else if (key == '2') scene.init(2);
   	else if (key == '3') scene.init(3);
  	else if (key == '4') scene.init(4);
	  else if (key == '5') scene.init(5);
		else if (key == 27) {
			// Escape code
			//scene.resetCamOffset();
			scene.setState("PAUSE");
			scene.initStartPause();
		}
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

bool Game::getSpecialKeyPressed(int key) const
{
	return specialKeys[key];
}



