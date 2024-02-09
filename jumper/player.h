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
	/// @brief Checks if the player is on the bottom of the window
	/// @return True if the player is on the bottom of the window
	bool on_floor();
	/// @brief Add acceleration force to the player
	/// @param force Vector2 of for x and y velocity
	void add_force(Vector2 force);
	/// @brief Makes the player jump
	void jump();
	/// @brief General movement that needs to run every update
	/// @param deltaTime
	void movement(float deltaTime);
	/// @brief Resets the acceleration to circumvent clipping
	void reset_movement();
	/// @brief Sets the player on the bottom of the window
	void set_on_floor();

private:
};

#endif /* PLAYER_H */
