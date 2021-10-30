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
bool Box::checkCollidedy(const glm::vec2 pos1, const glm::vec2 size1, const glm::vec2 pos2, const glm::vec2 size2) const
{
	// collision x-axis?
	bool collisionX = pos1.x + size1.x >= pos2.x && pos2.x + size2.x >= pos1.x;
	// collision y-axis?
	bool collisionY = pos1.y + size1.y >= pos2.y && pos2.y + size2.y >= pos1.y;
	// collision only if on both axes
	return collisionX && collisionY;
}
EventQueue Box::update(float deltaTime)
{
	sprite->update(deltaTime);
	if (inverse)
	{
		position.y -= FALL_STEP;
		if (!til->collisionMoveUp(position, glm::ivec2(32, 32), &position.y))
		{
			for (int i = 0; i < obToCollide.size(); i++)
			{
				if (obToCollide[i] != this)
				{
					bool a = checkCollidedy(position, size, obToCollide[i]->getPosition(), obToCollide[i]->getSize());
					if (a)
					{
						position.y += FALL_STEP;
					}
				}
			}
		}
	}
	else
	{
		position.y += FALL_STEP;
		if (!til->collisionMoveDown(position, glm::ivec2(32, 32), &position.y))
		{
			for (int i = 0; i < obToCollide.size(); i++)
			{
				if (obToCollide[i] != this)
				{
					bool a = checkCollidedy(position, size, obToCollide[i]->getPosition(), obToCollide[i]->getSize());
					if (a)
					{
						position.y -= FALL_STEP;
					}
				}
			}
		}
	}

	sprite->setPosition(position);

	EventQueue ret;
	return ret;
}
void Box::render()
{
	sprite->render();
}
bool Box::collided(glm::ivec2 source, glm::ivec2 size)
{
	auto pos = getPosition();
	auto siz = getSize();
	if (pos.y + siz.y > source.y+5 && source.y + size.y-5 > pos.y)
	{
		if (source.x <= pos.x)
		{
			pos.x++;
			til->collisionMoveRight(pos, glm::ivec2(32, 32));
			for (int i = 0; i < obToCollide.size(); i++)
			{
				if (obToCollide[i] != this)
				{
					bool a = checkCollidedy(pos, size, obToCollide[i]->getPosition(), obToCollide[i]->getSize());
					if (a)
					{
						pos.x--;
					}
				}
			}
		}
		else
		{
			pos.x--;
			til->collisionMoveRight(pos, glm::ivec2(32, 32));
			for (int i = 0; i < obToCollide.size(); i++)
			{
				if (obToCollide[i] != this)
				{
					bool a = checkCollidedy(pos, size, obToCollide[i]->getPosition(), obToCollide[i]->getSize());
					if (a)
					{
						pos.x++;
					}
				}
			}
		}
	}
	setPosition(pos);
	return true;
}
void Box::setObjectsToCollide(std::vector<Object*> oc)
{
	obToCollide = oc;
}
