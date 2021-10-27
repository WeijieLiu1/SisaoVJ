#include "Sea.h"
Sea::Sea(const glm::ivec2& pos, ShaderProgram& shaderProgram)
{
	setPosition(pos);
	setSize(glm::vec2(INT_MAX, 0));
}

EventQueue Sea::update(float deltaTime)
{
	EventQueue ret;
	if (haveCollided) ret.queue.push(ret.playerDead);

	return ret;
}
void Sea::render()
{

}
bool Sea::collided()
{
	haveCollided = true;
	return true; //Is solid
}