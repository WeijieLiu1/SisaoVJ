#include "Barrier.h"

Barrier::Barrier(const glm::ivec2& pos, ShaderProgram& shaderProgram )
{
	spritesheet.loadFromFile("images/ObjectsUsed.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(0.2, 0.4), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.2f, 0.2f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(pos.x + position.x), float(pos.y + position.y)));

	setPosition(pos);
	setSize(glm::vec2(32, 63));
}

EventQueue Barrier::update(float deltaTime)
{
	sprite->update(deltaTime);
	EventQueue ret;
	return ret;
}
void Barrier::render()
{
	if(!opened)sprite->render();
}
bool Barrier::collided(glm::ivec2 source, glm::ivec2 size)
{
	return true;
}

void Barrier::open()
{
	setSize(glm::ivec2(0,0));
	opened = true;
}

