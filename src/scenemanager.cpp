/**
 * This class describes SceneManager behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <iostream>

#include "scenemanager.h"

SceneManager::SceneManager() : Scene()
{
	// start the timer.
	t.start();

	// create a single instance of Player in the middle of the screen.
	// the Sprite is added in Constructor of Player.
	player = new Player();
	player->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	floor = new Floor();
	floor->position = Point2(SWIDTH / 2, SHEIGHT);

	// create the scene 'tree'
	// add player to this Scene as a child.
	this->addChild(player);
	this->addChild(floor);

	this->gravity = Point2(0.0, 2000);
}

SceneManager::~SceneManager()
{
	// deconstruct and delete the Tree
	this->removeChild(player);

	// delete player from the heap (there was a 'new' in the constructor)
	delete player;
}

void SceneManager::update(float deltaTime)
{
	if (input()->getKeyUp(KeyCode::Escape))
	{
		this->stop();
	}

	// addforce
	player->addForce(this->gravity);

	// movement 101
	player->velocity += player->acceleration * deltaTime;
	player->position += player->velocity * deltaTime;
	player->acceleration *= 0;

	if (player->onFloor(floor->position.y - floor->sprite()->size.y))
	{
		player->position.y = floor->position.y - floor->sprite()->size.y;
		player->velocity *= 0;
	}

	if (input()->getKeyUp(KeyCode::Space))
	{
		if (player->onFloor(floor->position.y - floor->sprite()->size.y))
		{
			player->acceleration -= Point2(0.0, (0.8 * pow(10, 6)));
		}
	}
	std::cout << "cube velocity: " << player->velocity << std::endl;
}

// velocity is constantly being decreased by gravity
// gravity is exponentional so it needs to somehow speed up while
// the cube is in the air
// when you jump you boost the velocity by a big number and then gravity
// will slowly take over and slow the cube down, until it starts falling down again