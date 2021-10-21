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

public:
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual void collided() = 0;
};
#endif

