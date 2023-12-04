// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>

class Player : public Entity
{
public:
	float rotationSpeed;
	Point2 velocity;
	Point2 acceleration;
	Player();
	virtual ~Player();

	virtual void update(float deltaTime);
	bool onFloor(float ground);
	void addForce(Point2 force);

private:
	/* add your private declarations */
};

#endif /* PLAYER_H */
