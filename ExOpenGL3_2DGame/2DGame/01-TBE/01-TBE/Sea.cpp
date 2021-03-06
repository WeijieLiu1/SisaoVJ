#include "Sea.h"
Sea::Sea(const glm::ivec2& pos, ShaderProgram* shaderProgram)
{
	setPosition(pos);
	setSize(glm::ivec2(INT_MAX, 0));

	spritesheet.loadFromFile("images/sea.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setWrapS(GL_REPEAT);
	spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
	sprite = Sprite::createSprite(glm::ivec2(INT_MAX, 450), glm::vec2(INT_MAX/480, 10), &spritesheet, shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::ivec2(pos.x,pos.y-16));

	this->shaderProgram = shaderProgram;
}

EventQueue Sea::update(float deltaTime)
{
	timerMov1 += deltaTime;
	if (timerMov1 > 3200) timerMov1 = 0;
	sprite->setPosition(glm::ivec2(position.x + timerMov1 / 100, position.y - 16));

	EventQueue ret;
	if (haveCollided) ret.queue.push(ret.playerDead);

	return ret;
}
void Sea::render()
{
}
void Sea::lateRender()
{
	shaderProgram->setUniform2f("seaPosition", position.x, position.y);
	shaderProgram->setUniform1i("seaAnim", timerMov1);
	sprite->render();
}
bool Sea::collided(glm::ivec2 source, glm::ivec2 size)
{
	if (!haveCollided && soundEngine != NULL)
	{
		soundEngine->setAllSoundsPaused();
		irrklang::ISound* snd = soundEngine->play2D("sounds/SFXSea.wav", false, false, true);
		snd->setVolume(2.5f);
	}
	haveCollided = true;

	return true; //Is solid
}
void Sea::setSoundEngine(irrklang::ISoundEngine* se)
{
	soundEngine = se;
}