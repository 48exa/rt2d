// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>

#define GROUND_PLAYER_OFFSET (688)
#define JUMP_VALUE (1350)

class Player : public Entity
{
public:
	Vector2 velocity;
	Vector2 acceleration;
	bool overlapping;

	Player();
	virtual ~Player();

	virtual void update(float deltaTime);
	bool onFloor();
	void addForce(Vector2 force);
	void jump();
	void movement(float deltaTime);
	void resetMovement();
	void setOnFloor();

private:
	int rotationSpeed;
	double quarter_pi;
};

#endif /* PLAYER_H */
