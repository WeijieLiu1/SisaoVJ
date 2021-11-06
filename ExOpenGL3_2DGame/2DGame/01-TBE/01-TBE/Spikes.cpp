#include "Spikes.h"

Spikes::Spikes(const glm::ivec2& pos, ShaderProgram& shaderProgram, int or)
{
	orientation = or;
	spritesheet.loadFromFile("images/ObjectsUsed.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.2), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	glm::vec2 truePos;
	glm::vec2 trueSize;
	if (or== 0)
	{
		truePos = glm::vec2(pos.x, pos.y + 8);
		trueSize = glm::vec2(32, 24);
		sprite->addKeyframe(0, glm::vec2(0.2f, 0.f));
	}
	else if (or== 1) //Facing right
	{
		truePos = glm::vec2(pos.x, pos.y);
		trueSize = glm::vec2(24, 32);
		sprite->addKeyframe(0, glm::vec2(0.4f, 0.f));
	}
	else if (or== 2) //Facing left
	{
		truePos = glm::vec2(pos.x +8, pos.y);
		trueSize = glm::vec2(24, 32);
		sprite->addKeyframe(0, glm::vec2(0.4f, 0.f));
	}
	else if (or== 3)//Facing downwards
	{
		truePos = glm::vec2(pos.x, pos.y);
		trueSize = glm::vec2(32, 24);
		sprite->addKeyframe(0, glm::vec2(0.2f, 0.f));
	}

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(truePos.x), float(pos.y)));

	setPosition(truePos);
	setSize(trueSize);
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
	if(orientation == 0) sprite->render();
	else if(orientation == 1) sprite->render();
	else if(orientation == 2) sprite->render_inv_x();
	else if(orientation == 3) sprite->render_inv_y();
}
bool Spikes::collided(glm::ivec2 source, glm::ivec2 size)
{
	if (!haveCollided && soundEngine != NULL)
	{
		soundEngine->setAllSoundsPaused();
		soundEngine->play2D("sounds/SFXSpike.wav", false);
	}
	haveCollided = true;
	return true;
}
void Spikes::setSoundEngine(irrklang::ISoundEngine* se)
{
	soundEngine = se;
}

