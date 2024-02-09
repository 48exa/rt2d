/**
 * Copyright 2024 D. Westerdijk <westerdijk@protonmail.com>
 *
 * @file jumper.h
 *
 * @brief Core of the Jumper game.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include "player.h"
#include "obstacle.h"
#include "obstaclelayer.h"

#define GRAVITY (5500)
#define PLAYER_HITBOX_SIZE (32)
#define SPIKE_HITBOX_SIZE (16)

class Jumper : public Scene
{
public:
	Jumper();
	virtual ~Jumper();
	virtual void update(float deltaTime);

private:
	/// @brief Specialized version of AABB() that checks if the player is landing ontop of an obstacle
	/// @param obstacle Obstacle that could collide with the player
	/// @return true if the type of collision is landing
	const bool landing_collision(const Player *p, const Obstacle *obs) const;
	/// @brief Handles miscellaneous
	const void handle_misc_key_events();
	/// @brief Creates the level by reading in a bytearray that dictates the position and type of obstacle
	/// @param bytearray Int vector containing 8 bit signed integers
	const void level_creator(const std::vector<unsigned short> *bytearray);
	/// @brief Places the obstacles based on info from the level creator
	/// @param chunk Byte from a bytearray
	/// @param _hostile Boolean that dictates if the obstacle is a spike or a square
	const void place_obstacle(unsigned short chunk, const bool _hostile);
	/// @brief Checks in a circle around the player if there are any obstacles, used for making sure
	/// @brief that we only do collision checks for obstacles near the player
	/// @param obstacle Obstacle to collide with
	/// @return Bool if there are any obstacles to collide with
	const bool in_collision_range(const Obstacle *obstacle) const;
	/// @brief Collision detection for the circular player hitbox and a square
	/// @param p Player
	/// @param obs Obstacle
	/// @return True if there is collision
	const bool player_square_collision(const Player *p, Obstacle *obs) const;
	/// @brief Collision detection for the circular player and spike hitbox
	/// @param p Player
	/// @param obs Obstacle
	/// @return True if there is collision
	const bool player_spike_collision(const Player *p, const Obstacle *obs) const;

	/// @brief Distance to spawn objects
	unsigned int _distance;
	/// @brief Vector of all obstacles
	std::vector<Obstacle *> obstacles;
	/// @brief Vector2 of the gravity used for the add_force method
	Vector2 gravity;
	std::vector<unsigned short> level_layout;

	ObstacleLayer *layer;
	Player *player;
	Timer t;
};

#endif /* SCENE00_H */
