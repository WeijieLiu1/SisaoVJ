#ifndef _BAROPENER_INCLUDE
#define _BAROPENER_INCLUDE

#include "Object.h"

class BarrierOpener : public Object
{
	Texture spritesheet;
	Sprite* sprite;
	glm::ivec2 position;
	int orientation = 0;
	bool haveCollided = false;
public:
	BarrierOpener(const glm::ivec2& pos, ShaderProgram& shaderProgram, int or = 0);
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided() override;

};

#endif

