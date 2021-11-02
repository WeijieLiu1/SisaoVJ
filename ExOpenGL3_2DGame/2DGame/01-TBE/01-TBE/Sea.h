#ifndef _SEA_INCLUDE
#define _SEA_INCLUDE

#include "Object.h"

class Sea : public Object
{
	bool haveCollided = false;
	Texture spritesheet;
	Sprite* sprite;
public:
	Sea(const glm::ivec2& pos, ShaderProgram& shaderProgram);
	EventQueue update(float deltaTime) override;
	void render() override;
	void lateRender();
	bool collided(glm::ivec2 source, glm::ivec2 size) override;
};

#endif
