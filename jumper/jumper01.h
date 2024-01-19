/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of JMPR01 behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include "player.h"
#include "obstacle.h"
#include "obstaclelayer.h"

#define GRAVITY (5500)
#define SPIKE_HITBOX_RADIUS (19)
#define SPIKE_HITBOX_RADIUS_SQUARED (361)
#define SPIKE_HITBOX_Y_OFFSET (12)

class Jumper01 : public Scene
{
public:
	Jumper01();
	virtual ~Jumper01();

	virtual void update(float deltaTime);
	bool AABB(Obstacle *obstacle);
	bool landingCollision(Obstacle *obstacle);
	bool circleAABB(Obstacle *obstacle);

private:
	std::vector<Obstacle *> obstacles;
	uint16_t gravityVal;
	Vector2 gravity;

	ObstacleLayer *layer;
	Player *player;
	Timer t;
};

#endif /* SCENE00_H */
