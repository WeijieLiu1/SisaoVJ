#include "CollisionEngine.h"


CollisionEngine::CollisionEngine()
{

}
void CollisionEngine::update(float deltaTime)
{

}

void CollisionEngine::setTileMap(TileMap* tl)
{
	tilemap = tl;
}
TileMap* CollisionEngine::getTilemap()
{
	return tilemap;
}
void CollisionEngine::setObjectsController(ObjectsController* oc)
{
	objectscontroller = oc;
}
ObjectsController* CollisionEngine::getObjectsController()
{
	return objectscontroller;
}
bool CollisionEngine::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	bool a =  tilemap->collisionMoveLeft(pos, size);
	bool b = objectscontroller->collisionMoveLeft(pos, size);
	return a || b;
}
bool CollisionEngine::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	bool a = tilemap->collisionMoveRight(pos, size);
	bool b = objectscontroller->collisionMoveRight(pos, size);
	return a || b;
}
bool CollisionEngine::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	bool a = tilemap->collisionMoveDown(pos, size, posY);
	bool b = objectscontroller->collisionMoveDown(pos, size, posY);
	return a || b;
}
bool CollisionEngine::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	bool a = tilemap->collisionMoveUp(pos, size, posY);
	bool b = objectscontroller->collisionMoveUp(pos, size, posY);
	return a || b;
}