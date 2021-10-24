#include "Object.h"
void Object::setPosition(glm::vec2 p)
{
	position = p;
}
glm::vec2 Object::getPosition()
{
	return position;
}