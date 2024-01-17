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
	void drawSpikeHitbox(int posx, int posy);

private:
	/* add your private declarations */
};

#endif /* OBSTACLE_H */
