#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE

class Object
{

public:
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual void collided() = 0;
};
#endif

