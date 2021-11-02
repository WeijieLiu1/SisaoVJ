#include "Star.h"
Star::Star(const glm::ivec2& pos, ShaderProgram& shaderProgram, bool inv )
{
	spritesheet.loadFromFile("images/ObjectsUsed.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.2), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(pos.x + position.x), float(pos.y + position.y)));

	sprite->setAnimationSpeed(1, 2);
	sprite->addKeyframe(1, glm::vec2(0.f, 0.4f));
	sprite->addKeyframe(1, glm::vec2(0.f, 0.6f));

	setPosition(pos);
	setSize(glm::vec2(32, 32));
	inverted = inv;
}

EventQueue Star::update(float deltaTime)
{
	sprite->update(deltaTime);
	EventQueue ret;
	if (haveCollided)
	{
		
		haveCollided = false;

		if (sprite->animation() != 1) sprite->changeAnimation(1);
		
		
	}
	if(animTimer!=-1)animTimer += deltaTime;
	if (animTimer > 1000)
	{
		sprite->changeAnimation(0);
		animTimer = -1;
	}
	if (animTimer > 500) //this is meant to give the player more flexibility (i.e. the stars don't have to be pressed the same frame)
	{
		if (inverted) ret.queue.push(ret.invertedStarOver);
		else ret.queue.push(ret.StarOver);
	}
	
	return ret;
}
void Star::render()
{
	if(inverted) sprite->render_inv_y();
	else sprite->render();
}
bool Star::collided(glm::ivec2 source, glm::ivec2 size)
{
	haveCollided = true;
	if (animTimer == -1) animTimer = 0;
	return false; //Is not solid
}