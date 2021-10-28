#include "Box.h"

#define FALL_STEP 4

Box::Box(const glm::ivec2& pos, ShaderProgram& shaderProgram , bool inv)
{
	inverse = inv;
	spritesheet.loadFromFile("images/ObjectsUsed.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.2), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.2f));
	sprite->changeAnimation(0);
	//sprite->setPosition(glm::vec2(float(pos.x + position.x), float(pos.y + position.y)));
	sprite->setPosition(glm::vec2(float(pos.x), float(pos.y)));


	setPosition(pos);
	setSize(glm::vec2(32, 32));
}

EventQueue Box::update(float deltaTime)
{
	sprite->update(deltaTime);
	if (inverse)
	{
		position.y -= FALL_STEP;

		til->collisionMoveUp(position, glm::ivec2(32, 32), &position.y);

	}
	else
	{
		position.y += FALL_STEP;
		til->collisionMoveDown(position, glm::ivec2(32, 32), &position.y);

	}

	sprite->setPosition(position);

	EventQueue ret;
	return ret;
}
void Box::render()
{
	sprite->render();
}
bool Box::collided()
{
	return true;
}
