#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "CollisionEngine.h"
#include "EventQueue.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, bool inv = false);
	EventQueue update(int deltaTime);
	void render();
	void render_inv_y();

	void setCollEngine(CollisionEngine* colis);
	void setPosition(const glm::vec2& pos);
	void kill();
	glm::vec2 getPosition();
private:
	bool lookAtRight = true;
	bool inverse;
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer, sizePlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	CollisionEngine* col;
	bool alive = true;
	float deathAnimTimer = 0;
};


#endif // _PLAYER_INCLUDE
