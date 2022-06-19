#ifndef _COLLENGINE_INCLUDE
#define _COLLENGINE_INCLUDE

#include "TileMap.h"
#include "ObjectsController.h"
#include "EventQueue.h"

class CollisionEngine {
	TileMap* tilemap;
	ObjectsController* objectscontroller;
public:
	CollisionEngine();
	void update(float deltaTime);
	void setTileMap(TileMap* tl);
	TileMap* getTilemap();
	void setObjectsController(ObjectsController* oc);
	ObjectsController* getObjectsController();
	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
};
#endif