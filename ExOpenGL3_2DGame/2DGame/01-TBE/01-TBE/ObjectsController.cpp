#include "ObjectsController.h"
ObjectsController::ObjectsController()
	: sceneObjects(std::vector<Object*>(0))
{
}
void ObjectsController::update(float deltaTime)
{
	int numObjecs = sceneObjects.size();
	for (int i = 0; i < numObjecs; i++) sceneObjects[i]->update(deltaTime);
}
void ObjectsController::render() const
{
	int numObjecs = sceneObjects.size();
	for (int i = 0; i < numObjecs; i++) sceneObjects[i]->render();
}
void ObjectsController::addObject(Object* ob)
{
	sceneObjects.push_back(ob);
}
Object* ObjectsController::getObject(int index)
{
	return sceneObjects[index];
}
int ObjectsController::getObjectSize()
{
	return sceneObjects.size();
}
void ObjectsController::setTileSize(int size)
{
	tileSize = size;
}
// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool ObjectsController::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = pos.x;
	y0 = pos.y;
	y1 = (pos.y + size.y - 1);
	bool collided = false;
	for (int y = y0; y <= y1; y++)
	{
		int objSize = sceneObjects.size();
		for (int i = 0; i < objSize; ++i)
		{
			auto posObj = sceneObjects[i]->getPosition();

			if (posObj.x == x && posObj.y == y)
			{

				collided = collided || sceneObjects[i]->collided();

			}
		}
	}

	return collided;
}

bool ObjectsController::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = pos.x  ;
	y0 = pos.y;
	y1 = (pos.y + size.y - 1);
	bool collided = false;
	for (int y = y0; y <= y1; y++)
	{
		int objSize = sceneObjects.size();
		for (int i = 0; i < objSize; ++i)
		{
			auto posObj = sceneObjects[i]->getPosition();
			if (posObj.x == x && posObj.y == y)
			{

				collided = collided || sceneObjects[i]->collided();

			}
		}
	}
	return collided;
}

bool ObjectsController::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x ;
	x1 = (pos.x + size.x - 1);
	y = (pos.y + size.y - 1);
	bool collided = false;

	for (int x = x0; x <= x1; x++)
	{
		int objSize = sceneObjects.size();
		for (int i = 0; i < objSize; ++i)
		{
			auto posObj = sceneObjects[i]->getPosition();
			if (posObj.x == x && posObj.y == y)
			{
				collided = collided || sceneObjects[i]->collided();

			}
		}
		if (collided && *posY - tileSize * y + size.y <= 6)
		{
			*posY = tileSize * y - size.y;
		}
	}
	return collided;
}

bool ObjectsController::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x;
	x1 = (pos.x + size.x - 1);
	y = pos.y;
	bool collided = false;
	for (int x = x0; x <= x1; x++)
	{
		int objSize = sceneObjects.size();
		for (int i = 0; i < objSize; ++i)
		{
			auto posObj = sceneObjects[i]->getPosition();
			if (posObj.x == x && posObj.y == y)
			{
				collided = collided || sceneObjects[i]->collided();
				
			}
		}
		if (collided && *posY - tileSize * y - size.y <= 6)
		{
			*posY = tileSize * y + size.y;

		}
	}
	return collided;
}