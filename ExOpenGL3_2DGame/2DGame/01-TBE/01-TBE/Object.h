#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Texture.h"
#include "Sprite.h"
#include "EventQueue.h"
#include "TileMap.h"
class Object
{

protected:
	glm::ivec2 position;
	glm::ivec2 size;
	TileMap* til;
public:
	void setPosition(glm::ivec2 p);
	glm::vec2 getPosition();
	void  setSize(glm::ivec2 s);
	glm::vec2 getSize();
	void setTilemap(TileMap* t);

	virtual EventQueue update(float deltaTime) = 0;
	virtual void render() = 0;
	//Returns wheder the object is solid and performs the actions required
	virtual bool collided(glm::ivec2 source, glm::ivec2 size) = 0;
};
#endif

