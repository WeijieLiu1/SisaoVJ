#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Texture.h"
#include "Sprite.h"
#include "TileMap.h"
class Object
{
	glm::vec2 position;
public:
	void setPosition(glm::vec2 p);
	glm::vec2 getPosition();
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	//Returns wheder the object is solid and performs the actions required
	virtual bool collided() = 0;
};
#endif

