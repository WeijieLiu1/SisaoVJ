#ifndef _EVQ_INCLUDE
#define _EVQ_INCLUDE
#include <queue>
class EventQueue
{
public:
	enum eventType {playerDead,RestartLevel, levelCompleted, invertedStarOver, StarOver};
	std::queue<eventType> queue;
};
#endif