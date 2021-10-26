#include "Star.h"
Star::Star(const glm::ivec2& pos, ShaderProgram& shaderProgram )
{
	spritesheet.loadFromFile("images/ObjectsUsed.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.2), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(pos.x + position.x), float(pos.y + position.y)));

	setPosition(pos);
	setSize(glm::vec2(32, 32));
}

EventQueue Star::update(float deltaTime)
{
	sprite->update(deltaTime);
	EventQueue ret;
	if (haveCollided) ret.queue.push(ret.levelCompleted);
	return ret;
}
void Star::render()
{
	sprite->render();
}
bool Star::collided()
{
	haveCollided = true;
	return true;
}