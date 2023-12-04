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

class SceneManager : public Scene
{
public:
	SceneManager();
	virtual ~SceneManager();

	virtual void update(float deltaTime);

private:
	Point2 gravity;
	Player *player;
	Floor *floor;
	Timer t;
};

#endif /* SCENE00_H */
