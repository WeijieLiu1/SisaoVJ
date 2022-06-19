#ifndef _SKY_INCLUDE
#define _BKY_INCLUDE
#include "Sprite.h"

class Sky
{
	Texture spritesheet;
	Sprite* sprite;
	bool inverse;
public:
	Sky(const glm::ivec2& pos, glm::vec2 size, ShaderProgram& shaderProgram, bool inv = false);
	void update(float deltaTime);
	void render();
};

#endif
