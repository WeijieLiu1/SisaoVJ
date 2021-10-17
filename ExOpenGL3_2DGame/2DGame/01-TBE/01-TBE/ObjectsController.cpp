#include "ObjectsController.h"
ObjectsController::ObjectsController(TileMap* scene)
	: currentScene(scene), sceneObjects(std::vector<Object*>(0))
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