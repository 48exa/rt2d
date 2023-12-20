// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>

class Player : public Entity
{
public:
	Point2 velocity;
	Point2 acceleration;
	bool overlapping;

	Player();
	virtual ~Player();

	virtual void update(float deltaTime);
	bool onFloor();
	void addForce(Point2 force);
	void jump();
	void movement(float deltaTime);
	void resetMovement();
	void setOnFloor();

private:
	int rotationSpeed;
	double quarter_pi;
};

#endif /* PLAYER_H */
