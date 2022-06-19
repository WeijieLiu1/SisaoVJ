#include "Barrier.h"

Barrier::Barrier(const glm::ivec2& pos, ShaderProgram& shaderProgram )
{
	spritesheet.loadFromFile("images/ObjectsUsed.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(0.2, 0.4), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.2f, 0.2f));

	sprite->setAnimationSpeed(1, 3);
	sprite->addKeyframe(1, glm::vec2(0.8f, 0.f));
	sprite->addKeyframe(1, glm::vec2(0.8f, 0.4f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(pos.x + position.x), float(pos.y + position.y)));

	setPosition(pos);
	setSize(glm::vec2(32, 64));
}

EventQueue Barrier::update(float deltaTime)
{
	sprite->update(deltaTime);
	if (opened)
	{
		if (sprite->animation() != 1) sprite->changeAnimation(1);
		if(animTimer>-1)animTimer += deltaTime;
		if (animTimer > 666) animTimer = -1;
	}
	EventQueue ret;
	return ret;
}
void Barrier::render()
{
	if(!opened ||animTimer >= 0)sprite->render();
}
bool Barrier::collided(glm::ivec2 source, glm::ivec2 size)
{
	return true;
}

void Barrier::open()
{
	setSize(glm::ivec2(-INT_MAX,0));
	animTimer = 0;
	opened = true;
}

