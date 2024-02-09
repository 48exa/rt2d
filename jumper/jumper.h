/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of Jumper behavior.
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

	/// @brief Specialized version of AABB() that checks if the player is landing ontop of an obstacle
	/// @param obstacle Obstacle that could collide with the player
	/// @return true if the type of collision is landing
	bool landing_collision(Player *p, Obstacle *obs);
	/// @brief Handles miscellaneous
	void handle_misc_key_events();
	/// @brief Creates the level by reading in a bytearray that dictates the position and type of obstacle
	/// @param bytearray Int vector containing 8 bit signed integers
	void level_creator(std::vector<unsigned short> bytearray);
	/// @brief Places the obstacles based on info from the level creator
	/// @param chunk Byte from a bytearray
	/// @param hostile Boolean that dictates if the obstacle is a spike or a square
	void place_obstacle(unsigned short chunk, bool hostile);
	/// @brief Checks in a circle around the player if there are any obstacles, used for making sure
	/// @brief that we only do collision checks for obstacles near the player
	/// @param obstacle Obstacle to collide with
	/// @return Bool if there are any obstacles to collide with
	bool in_collision_range(Obstacle *obstacle);
	/// @brief Collision detection for the circular player hitbox and a square
	/// @param p Player
	/// @param obs Obstacle
	/// @return True if there is collision
	bool player_square_collision(Player *p, Obstacle *obs);
	/// @brief Collision detection for the circular player and spike hitbox
	/// @param p Player
	/// @param obs Obstacle
	/// @return True if there is collision
	bool player_spike_collision(Player *p, Obstacle *obs);

private:
	unsigned int _distance;
	std::vector<Obstacle *> obstacles;
	Vector2 gravity;

	ObstacleLayer *layer;
	Player *player;
	Timer t;
};

#endif /* SCENE00_H */
