#ifndef _BARRIER_INCLUDE
#define _BARRIER_INCLUDE

#include "Object.h"

class Barrier : public Object
{
	Texture spritesheet;
	Sprite* sprite;
	bool opened = false;
public:
	Barrier(const glm::ivec2& pos, ShaderProgram& shaderProgram);
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided(glm::ivec2 source, glm::ivec2 size) override;
	void open();
};

#endif
