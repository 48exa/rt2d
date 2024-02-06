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

	/// @brief Rectangle to rectangle collision detection
	/// @param obstacle Obstacle that could collide with the player
	/// @return true if collision is happening
	bool AABB(Obstacle *obstacle);
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
	void level_creator(std::vector<int> bytearray);
	void place_obstacle(int chunk, bool hostile);

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
