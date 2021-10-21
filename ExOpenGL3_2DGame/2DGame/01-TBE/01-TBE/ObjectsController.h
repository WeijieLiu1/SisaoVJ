#pragma once
#include "Tilemap.h"
#include "Object.h"
#include <vector>
class ObjectsController
{
	std::vector<Object*> sceneObjects;
//	TileMap* currentScene;
public:
	//ObjectsController(TileMap* scene);
	void update(float deltaTime);
	void render() const;
	void addObject(Object* ob);
	Object* getObject(int index);
};

