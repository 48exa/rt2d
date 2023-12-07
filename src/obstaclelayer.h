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

private:
	/* add your private declarations */
};

#endif /* OBSTACLELAYER_H */
