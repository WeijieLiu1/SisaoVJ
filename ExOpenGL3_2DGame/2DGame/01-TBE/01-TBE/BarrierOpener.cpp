#include "BarrierOpener.h"

BarrierOpener::BarrierOpener(const glm::ivec2& pos, ShaderProgram& shaderProgram, Barrier* bTO)
{
	barrierToOpen = bTO;
	spritesheet.loadFromFile("images/ObjectsUsed.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 0.2), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.4f, 0.2f));
	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.6f, 0.2f));
	sprite->changeAnimation(0);
	sprite->setPosition(pos);

	setPosition(pos);
	setSize(glm::vec2(32, 63));
}
EventQueue BarrierOpener::update(float deltaTime)
{
	sprite->update(deltaTime);
	EventQueue ret;
	return ret;
}
void BarrierOpener::render()
{
	sprite->render();
}
bool BarrierOpener::collided(glm::ivec2 source, glm::ivec2 size)
{

	if (!opened)
	{

		barrierToOpen->open();
		sprite->changeAnimation(1);
		if (soundEngine != NULL)
		{
		//	soundEngine->stopAllSounds();
			soundEngine->play2D("sounds/SFXDoor.wav", false);
		}
	}
	opened = true;
	return false; //Is not a solid
}
void BarrierOpener::setSoundEngine(irrklang::ISoundEngine* se)
{
	soundEngine = se;
}

