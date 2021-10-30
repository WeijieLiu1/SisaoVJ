#ifndef _BOX_INCLUDE
#define _BOX_INCLUDE

#include "Object.h"

class Box : public Object
{
	Texture spritesheet;
	Sprite* sprite;
	bool haveCollided = false;
	bool inverse;
public:
	Box(const glm::ivec2& pos, ShaderProgram& shaderProgram, bool in = false);
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided() override;

};

#endif
