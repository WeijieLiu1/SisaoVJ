#ifndef _STAR_INCLUDE
#define _STAR_INCLUDE

#include "Object.h"

class Star : public Object
{
	Texture spritesheet;
	Sprite* sprite;
	glm::ivec2 position;
	bool haveCollided = false;
public:
	Star(const glm::ivec2& pos, ShaderProgram& shaderProgram);
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided() override;

};

#endif

