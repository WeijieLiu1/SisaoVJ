#include "Sky.h"

Sky::Sky(const glm::ivec2& pos,glm::vec2 size, ShaderProgram& shaderProgram, bool inv)
{
	spritesheet.loadFromFile("images/sky.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(INT_MAX, size.y), glm::vec2(INT_MAX /319, 1), &spritesheet, &shaderProgram);
	//sprite = Sprite::createSprite(size, glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(pos.x,pos.y));


	inverse = inv;
}
void Sky::update(float deltaTime)
{
	sprite->update(deltaTime);
}
void Sky::render()
{
	if (inverse) sprite->render_inv_y();
	else sprite->render();
}