/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of Jumper01 behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include "player.h"
#include "obstacle.h"
#include "obstaclelayer.h"

#define GRAVITY (5500)
#define SPIKE_HITBOX_RADIUS (19)

#define SPIKE_HITBOX_Y_OFFSET (12)

class Jumper01 : public Scene
{
public:
	Jumper01();
	virtual ~Jumper01();
	virtual void update(float deltaTime);

	/// @brief Specialized version of AABB() that checks if the player is landing ontop of an obstacle
	/// @param obstacle Obstacle that could collide with the player
	/// @return true if the type of collision is landing
	bool landingCollision(Obstacle *obstacle);
	/// @brief Circle to rectangle collision
	/// https://yal.cc/rectangle-circle-intersection-test/
	/// @param obstacle Obstacle that could collide with the player
	/// @return true if collision is happening
	bool circleAABB(Obstacle *obstacle);
	/// @brief Handles miscellaneous
	void handleMiscKeyEvents();
	/// @brief Creates the level by reading in a bytearray that dictates the position and type of obstacle
	/// @param bytearray Int vector containing 8 bit signed integers
	void level_creator(std::vector<int> bytearray);
	/// @brief Places the obstacles based on info from the level creator
	/// @param chunk Byte from a bytearray
	/// @param hostile Boolean that dictates if the obstacle is a spike or a square
	void place_obstacle(int chunk, bool hostile);
	bool in_collision_range(Obstacle *obstacle);
	bool player_square_collision(Player *p, Obstacle *obs);
	bool player_spike_collision(Player *p, Obstacle *obs);

private:
	int distance;
	std::vector<Obstacle *> obstacles;
	uint16_t gravityVal;
	Vector2 gravity;

	ObstacleLayer *layer;
	Player *player;
	Timer t;
};

#endif /* SCENE00_H */
