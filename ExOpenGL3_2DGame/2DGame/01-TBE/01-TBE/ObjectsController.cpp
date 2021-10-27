#include "ObjectsController.h"

bool ObjectsController::checkCollidedx(const glm::vec2 pos1, const glm::vec2 size1, const glm::vec2 pos2, const glm::vec2 size2) const
{

	bool collisionX = pos1.x + size1.x >= pos2.x && pos2.x + size2.x >= pos1.x;
	// collision y-axis?
	bool collisionY = pos1.y + size1.y > pos2.y && pos2.y + size2.y > pos1.y;
	// collision only if on both axes
	return collisionX && collisionY;
}

bool ObjectsController::checkCollidedy(const glm::vec2 pos1, const glm::vec2 size1, const glm::vec2 pos2, const glm::vec2 size2) const
{
	// collision x-axis?
	bool collisionX = pos1.x + size1.x >= pos2.x && pos2.x + size2.x >= pos1.x;
	// collision y-axis?
	bool collisionY = pos1.y + size1.y >= pos2.y && pos2.y + size2.y >= pos1.y;
	// collision only if on both axes
	return collisionX && collisionY;
}

ObjectsController::ObjectsController()
	: sceneObjects(std::vector<Object*>(0))
{
}
ObjectsController::~ObjectsController()
{
	for (int i = 0; i < sceneObjects.size(); i++) delete sceneObjects[i];
}
EventQueue ObjectsController::update(float deltaTime)
{
	int numObjecs = sceneObjects.size();
	EventQueue ret;
	bool starDetected = false;
	bool invStarDetected = false;
	for (int i = 0; i < numObjecs; i++)
	{
		EventQueue aux = sceneObjects[i]->update(deltaTime);
		while (!aux.queue.empty())
		{
			if (aux.queue.front() == EventQueue::StarOver)
			{
				starDetected = true;
				if (invStarDetected) 
					ret.queue.push(EventQueue::levelCompleted);
			}
			else if (aux.queue.front() == EventQueue::invertedStarOver)
			{
				invStarDetected = true;
				if (starDetected) 
					ret.queue.push(EventQueue::levelCompleted);
			}
			else 
			{
				ret.queue.push(aux.queue.front());
			}
			aux.queue.pop();
		}
		
	}
	return ret;
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
			glm::vec2 posObj = sceneObjects[i]->getPosition();
			glm::vec2 sizObj = sceneObjects[i]->getSize();
			if (checkCollidedx(pos, size, posObj, sizObj))
			{
				bool aux = sceneObjects[i]->collided(); //This must be here to ensure that the method gets called
				collided = collided || aux;

			}
		}
	}

	return collided;
}

bool ObjectsController::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = pos.x  + size.x;
	y0 = pos.y;
	y1 = (pos.y + size.y - 1);
	bool collided = false;
	for (int y = y0; y <= y1; y++)
	{
		int objSize = sceneObjects.size();
		for (int i = 0; i < objSize; ++i)
		{
			auto posObj = sceneObjects[i]->getPosition();
			glm::vec2 sizObj = sceneObjects[i]->getSize();
			if (checkCollidedx(pos, size, posObj, sizObj))
			{
				bool aux = sceneObjects[i]->collided(); //This must be here to ensure that the method gets called
				collided = collided || aux;
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
		int newY = 0;
		int objSize = sceneObjects.size();
		for (int i = 0; i < objSize; ++i)
		{
			auto posObj = sceneObjects[i]->getPosition();
			glm::vec2 sizObj = sceneObjects[i]->getSize();
			if (checkCollidedy(pos, size, posObj, sizObj))
			{
				bool aux = sceneObjects[i]->collided(); //This must be here to ensure that the method gets called
				if (aux && posObj.y - sizObj.y > newY) newY = posObj.y - (sizObj.y);
				collided = collided || aux;
			}
		}
		if (collided && *posY - tileSize * y + size.y <= 6)
		{
			*posY = newY;
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
		int newY = 0;
		int objSize = sceneObjects.size();
		for (int i = 0; i < objSize; ++i)
		{
			auto posObj = sceneObjects[i]->getPosition();
			glm::vec2 sizObj = sceneObjects[i]->getSize();
			if (checkCollidedy(pos, size, posObj, sizObj))
			{
				bool aux = sceneObjects[i]->collided(); //This must be here to ensure that the method gets called
				if (aux && posObj.y + sizObj.y > newY) newY = posObj.y + (sizObj.y);
				collided = collided || aux;
			}
		}
		if (collided && *posY - tileSize * y - size.y <= 6)
		{
			*posY = newY;
		}
	}
	return collided;
}