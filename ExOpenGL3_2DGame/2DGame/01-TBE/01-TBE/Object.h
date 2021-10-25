#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Texture.h"
#include "Sprite.h"
#include "EventQueue.h"
class Object
{
	glm::vec2 position;
	glm::vec2 size;
public:
	void setPosition(glm::vec2 p);
	glm::vec2 getPosition();
	void  setSize(glm::vec2 s);
	glm::vec2 getSize();
	virtual EventQueue update(float deltaTime) = 0;
	virtual void render() = 0;
	//Returns wheder the object is solid and performs the actions required
	virtual bool collided() = 0;
};
#endif

