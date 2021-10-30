#include "Spikes.h"

Spikes::Spikes(const glm::ivec2& pos, ShaderProgram& shaderProgram, int or)
{
	orientation = or ;
	spritesheet.loadFromFile("images/ObjectsUsed.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.2), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.2f * (or +1), 0.f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(pos.x + position.x), float(pos.y + position.y)));

	setPosition(pos);
	setSize(glm::vec2(32, 32));
}

EventQueue Spikes::update(float deltaTime)
{
	sprite->update(deltaTime);
	EventQueue ret;
	if (haveCollided) ret.queue.push(ret.playerDead);
	return ret;
}
void Spikes::render()
{
	sprite->render();
}
bool Spikes::collided()
{
	haveCollided = true;
	return true;
}


