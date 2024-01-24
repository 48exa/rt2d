// obstacle.h

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <entity.h>

class Obstacle : public Entity
{
public:
	bool hostile;
	Obstacle(Vector2 pos, bool hostile);
	virtual ~Obstacle();

	virtual void update(float deltaTime);
	/// @brief getter for private boolean hostile
	/// @return hostile boolean
	bool isHostile();

private:
	/* add your private declarations */
};

#endif /* OBSTACLE_H */
