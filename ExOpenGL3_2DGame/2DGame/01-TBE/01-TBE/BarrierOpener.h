#ifndef _BAROPENER_INCLUDE
#define _BAROPENER_INCLUDE

#include "Barrier.h"
#include "irrKlang.h"
class BarrierOpener : public Object
{
	Texture spritesheet;
	Sprite* sprite;
	glm::ivec2 position;
	Barrier* barrierToOpen;
	bool opened = false;
	irrklang::ISoundEngine* soundEngine;

public:
	BarrierOpener(const glm::ivec2& pos, ShaderProgram& shaderProgram, Barrier* bTO);
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided(glm::ivec2 source, glm::ivec2 size) override;
	void setSoundEngine(irrklang::ISoundEngine* se);

};

#endif

