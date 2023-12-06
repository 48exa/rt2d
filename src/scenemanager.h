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
#include "floor.h"
#include "obstacle.h"

class SceneManager : public Scene
{
public:
	SceneManager();
	virtual ~SceneManager();

	virtual void update(float deltaTime);

private:
	std::vector<Obstacle*> obstacles;
	Point2 gravity;

	Obstacle *square;
	Obstacle *square2;
	Player *player;
	Floor *floor;
	Timer t;
};

#endif /* SCENE00_H */
