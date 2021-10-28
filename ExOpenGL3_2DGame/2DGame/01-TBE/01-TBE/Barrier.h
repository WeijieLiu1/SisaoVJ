#ifndef _BARRIER_INCLUDE
#define _BARRIER_INCLUDE

#include "Object.h"

class Barrier : public Object
{
	Texture spritesheet;
	Sprite* sprite;
	glm::ivec2 position;
	int orientation = 0;
	bool haveCollided = false;
public:
	Barrier(const glm::ivec2& pos, ShaderProgram& shaderProgram, int or = 0);
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided() override;

};

#endif
