#ifndef _SPIKES_INCLUDE
#define _SPIKES_INCLUDE

#include "Object.h"

class Spikes : public Object 
{
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	glm::ivec2 tileMapDispl, position;

public:
	Spikes(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(float deltaTime) override;
	void render() override;
	void collided() override;

};

#endif
