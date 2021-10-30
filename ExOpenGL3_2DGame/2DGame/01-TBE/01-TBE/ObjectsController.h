#ifndef _OBJECTSCTRL_INCLUDE
#define _OBJECTSCTRL_INCLUDE

#include "Object.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
class ObjectsController
{
	std::vector<Object*> sceneObjects;
	int tileSize = 0;
	//TileMap *currentScene;
	bool checkCollidedx(const glm::vec2 pos1, const glm::vec2 size1, const glm::vec2 pos2, const glm::vec2 size2) const;
	bool checkCollidedy(const glm::vec2 pos1, const glm::vec2 size1, const glm::vec2 pos2, const glm::vec2 size2) const;
public:
	ObjectsController(/*TileMap* scene*/);
	~ObjectsController(/*TileMap* scene*/);
	EventQueue update(float deltaTime);
	void render() const;
	void addObject(Object* ob);
	Object* getObject(int index);
	int getObjectSize();
	void setTileSize(int size);

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
};

#endif

