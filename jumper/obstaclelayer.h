// obstaclelayer.h

#ifndef OBSTACLELAYER_H
#define OBSTACLELAYER_H

#include <entity.h>

class ObstacleLayer : public Entity
{
public:
	ObstacleLayer();
	virtual ~ObstacleLayer();

	void update(float deltaTime);
	void resetPosition();

private:
	float originalPosition;
};

#endif /* OBSTACLELAYER_H */
