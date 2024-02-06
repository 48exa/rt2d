// obstaclelayer.h

#ifndef OBSTACLELAYER_H
#define OBSTACLELAYER_H

#include <entity.h>
#define MOVEMENT_SPEED (-400)
class ObstacleLayer : public Entity
{
public:
	ObstacleLayer();
	virtual ~ObstacleLayer();

	void update(float deltaTime);
	/// @brief Resets the objectLayer back to its original position, giving the illusion the level has restarted
	void resetPosition();

private:
	float originalPosition;
};

#endif /* OBSTACLELAYER_H */
