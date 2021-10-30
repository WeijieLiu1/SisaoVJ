#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

#define xSpriteSize 0.06667
#define ySpriteSize 0.125
enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, bool inv )
{
	bJumping = false;
	spritesheet.loadFromFile("images/sonic.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sizePlayer = glm::ivec2(24, 32);
	sprite = Sprite::createSprite(sizePlayer, glm::vec2(xSpriteSize, ySpriteSize), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(STAND_LEFT, 4);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f * xSpriteSize, 0.f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(1.f * xSpriteSize, 0.f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(2.f * xSpriteSize, 0.f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(3.f * xSpriteSize, 0.f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(4.f * xSpriteSize, 0.f));

	sprite->setAnimationSpeed(STAND_RIGHT, 4);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f * xSpriteSize, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(1.f * xSpriteSize, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(2.f * xSpriteSize, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(3.f * xSpriteSize, 0.f));
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(4.f * xSpriteSize, 0.f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(5.0f* xSpriteSize, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(6.0f* xSpriteSize, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(7.0f* xSpriteSize, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(8.0f* xSpriteSize, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(9.0f* xSpriteSize, 0.f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5.0f* xSpriteSize, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(6.0f* xSpriteSize, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(7.0f* xSpriteSize, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(8.0f* xSpriteSize, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(9.0f* xSpriteSize, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	inverse = inv;
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT) {
			sprite->changeAnimation(MOVE_LEFT);
			lookAtRight = false;
		}
			
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, sizePlayer))
		{
			posPlayer.x += 2;
			//sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT) {
			sprite->changeAnimation(MOVE_RIGHT);
			lookAtRight = true;
		}
		posPlayer.x += 2;
		if (map->collisionMoveRight(posPlayer, sizePlayer))
		{
			posPlayer.x -= 2;
			//sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		/*
		* 
		if (sprite->animation() == STAND_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == STAND_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
		*/
		

	}

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;


		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			if(inverse)
			{
				posPlayer.y = int(startY + 96 * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90)
					bJumping = !map->collisionMoveUp(posPlayer, sizePlayer, &posPlayer.y);
				else
				{
					if (map->collisionMoveDown(posPlayer, sizePlayer, &posPlayer.y))
						bJumping = false;
				}
			}
			else 
			{
				posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90)
					bJumping = !map->collisionMoveDown(posPlayer, sizePlayer, &posPlayer.y);
				else
				{
					if (map->collisionMoveUp(posPlayer, sizePlayer, &posPlayer.y))
						bJumping = false;
				}
			}
		}
	}
	else
	{
		if (inverse)
		{
			posPlayer.y -= FALL_STEP;

			if (map->collisionMoveUp(posPlayer, sizePlayer, &posPlayer.y))
			{
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
		}
		else
		{
			posPlayer.y += FALL_STEP;
			if (map->collisionMoveDown(posPlayer, sizePlayer, &posPlayer.y))
			{
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{

	if (lookAtRight){
		sprite->render();
		}
	else {
		sprite->render_inv_x();
	}
	//lookAtRight = !lookAtRight;
}

void Player::render_inv_y()
{

	if (lookAtRight) {
		sprite->render_inv_y();
		
	}
	else {
		sprite->render_inv_xy();
	}
	//lookAtRight = !lookAtRight;
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}
glm::vec2 Player::getPosition()
{
	return posPlayer;
}
