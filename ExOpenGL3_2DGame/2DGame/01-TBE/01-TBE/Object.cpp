#include "Object.h"
void Object::setPosition(glm::vec2 p)
{
	position = p;
}
glm::vec2 Object::getPosition()
{
	return position;
}
void Object::setSize(glm::vec2 s)
{
	size = s;
}
glm::vec2 Object::getSize()
{
	return size;
}
void Object::setTilemap(TileMap* t)
{
	til = t;
}