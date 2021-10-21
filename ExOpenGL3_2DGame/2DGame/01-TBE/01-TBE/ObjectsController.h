#ifndef _OBJECTSCTRL_INCLUDE
#define _OBJECTSCTRL_INCLUDE

#include "TileMap.h"
#include "Object.h"
#include <vector>
class ObjectsController
{
	std::vector<Object*> sceneObjects;
	int k;
	TileMap *currentScene;
public:
	ObjectsController(TileMap* scene);
	void update(float deltaTime);
	void render() const;
	void addObject(Object* ob);
	Object* getObject(int index);
};

#endif

