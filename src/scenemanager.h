/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of SceneManager behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include "player.h"
#include "obstacle.h"
#include "obstaclelayer.h"

#define GRAVITY (5500)

class SceneManager : public Scene
{
public:
	SceneManager();
	virtual ~SceneManager();

	virtual void update(float deltaTime);
	bool AABB(Obstacle *obstacle);
	bool landingCollision(Obstacle *obstacle);

private:
	bool overlapping;
	std::vector<Obstacle *> obstacles;
	uint16_t gravityVal;
	Point2 gravity;

	ObstacleLayer *layer;
	Player *player;
	Timer t;
};

#endif /* SCENE00_H */
