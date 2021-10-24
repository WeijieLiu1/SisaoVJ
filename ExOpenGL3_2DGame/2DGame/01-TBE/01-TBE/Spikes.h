#ifndef _SPIKES_INCLUDE
#define _SPIKES_INCLUDE

#include "Object.h"

class Spikes : public Object 
{
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	glm::ivec2 position;

public:
	Spikes(const glm::ivec2& pos, ShaderProgram& shaderProgram);
	void update(float deltaTime) override;
	void render() override;
	bool collided() override;

};

#endif
