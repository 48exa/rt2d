// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>
#include "floor.h"

class Player : public Entity
{
public:
	Point2 velocity;
	Point2 acceleration;

	Player();
	virtual ~Player();

	virtual void update(float deltaTime);
	bool onFloor(Floor* ground);
	void addForce(Point2 force);
	void jump();

private:
	/* add your private declarations */
};

#endif /* PLAYER_H */
