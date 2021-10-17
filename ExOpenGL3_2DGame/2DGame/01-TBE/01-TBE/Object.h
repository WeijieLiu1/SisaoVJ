#pragma once
class Object
{

public:
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual void collided();
};

