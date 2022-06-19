#ifndef _BOX_INCLUDE
#define _BOX_INCLUDE

#include "Object.h"

class Box : public Object
{
private:
	Texture spritesheet;
	Sprite* sprite;
	bool haveCollided = false;
	bool inverse;
	std::vector<Object*> obToCollide;
	glm::vec2 boxSize = glm::vec2(32, 32);
public:
	Box(const glm::ivec2& pos, ShaderProgram& shaderProgram, bool in = false);
	bool checkCollidedy(const glm::vec2 pos1, const glm::vec2 size1, const glm::vec2 pos2, const glm::vec2 size2) const;
	EventQueue update(float deltaTime) override;
	void render() override;
	bool collided(glm::ivec2 source, glm::ivec2 size) override;
	void setObjectsToCollide(std::vector<Object*> oc);
};

#endif
