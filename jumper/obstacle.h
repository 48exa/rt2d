/**
 * Copyright 2024 D. Westerdijk <westerdijk@protonmail.com>
 *
 * @file obstacle.h
 *
 * @brief Behaviour of the obstacles
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <entity.h>

class Obstacle : public Entity
{
public:
	Obstacle(const Vector2 pos, const bool hostile);
	virtual ~Obstacle();
	virtual void update(float deltaTime);

	/// @brief getter for private boolean hostile
	/// @return hostile boolean
	const bool is_hostile() const;

private:
	bool _hostile;
};

#endif
