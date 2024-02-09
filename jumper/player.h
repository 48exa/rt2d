/**
 * Copyright 2024 D. Westerdijk <westerdijk@protonmail.com>
 *
 * @file player.h
 *
 * @brief Behaviour of the player
 */

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

	/// @brief Checks if the player is on the bottom of the window
	/// @return True if the player is on the bottom of the window
	const bool on_floor() const;
	/// @brief Makes the player jump
	const void jump();
	/// @brief Add acceleration force to the player
	/// @param force Vector2 of for x and y velocity
	const void add_force(const Vector2 force);
	/// @brief General movement that needs to run every update
	/// @param deltaTime
	const void movement(const float deltaTime);
	/// @brief Resets the acceleration to circumvent clipping
	const void reset_movement();

private:
	/// @brief Sets the player on the bottom of the window
	const void set_on_floor();
};

#endif
