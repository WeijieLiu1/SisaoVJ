#ifndef _STAR_INCLUDE
#define _STAR_INCLUDE

#include "Object.h"

class Star : public Object
{
	Texture spritesheet;
	Sprite* sprite;
	glm::ivec2 position;
	bool haveCollided = false;
	bool inverted = false;
	int animTimer = -1;
public:
	Star(const glm::ivec2& pos, ShaderProgram& shaderProgram, bool inv);
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided(glm::ivec2 source, glm::ivec2 size) override;

};

#endif

