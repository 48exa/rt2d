/**
 * Copyright 2024 D. Westerdijk <westerdijk@protonmail.com>
 *
 * @file obstaclelayer.h
 *
 * @brief Behaviour of the obstaclelayer
 */

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
	const void resetPosition();

private:
	/// @brief Original position of the obstacle layer
	float original_position;
};

#endif
