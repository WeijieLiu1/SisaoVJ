#ifndef _SPIKES_INCLUDE
#define _SPIKES_INCLUDE

#include "Object.h"
#include "irrKlang.h"

class Spikes : public Object 
{
	Texture spritesheet;
	Sprite* sprite;
	glm::ivec2 position;
	int orientation = 0;
	bool haveCollided = false;
	irrklang::ISoundEngine* soundEngine;
public:
	Spikes(const glm::ivec2& pos, ShaderProgram& shaderProgram, int or = 0);
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided(glm::ivec2 source, glm::ivec2 size) override;
	void setSoundEngine(irrklang::ISoundEngine* se);

};

#endif
