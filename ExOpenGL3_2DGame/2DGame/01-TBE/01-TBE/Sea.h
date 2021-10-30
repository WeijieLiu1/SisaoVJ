#ifndef _SEA_INCLUDE
#define _SEA_INCLUDE

#include "Object.h"

class Sea : public Object
{
	glm::ivec2 position;
	bool haveCollided = false;
public:
	Sea(const glm::ivec2& pos, ShaderProgram& shaderProgram);
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided() override;
};

#endif
