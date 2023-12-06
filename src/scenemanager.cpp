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

	// initialise the list of all obstacles
	obstacles = std::vector<Obstacle *>();

	// create a single instance of Player in the middle of the screen.
	// the Sprite is added in Constructor of Player.
	player = new Player();
	player->position = Point2(SWIDTH / 2, SHEIGHT / 2);

	// initiate the floor
	floor = new Floor();
	floor->position = Point2(SWIDTH / 2, SHEIGHT);

	// initiate all obstacles
	square = new Obstacle(Point2(SWIDTH, 600), false, "assets/gdcube.tga");
	square2 = new Obstacle(Point2(SWIDTH - 256, 600), false, "assets/gdcube.tga");

	// create the scene 'tree'
	// add player to this Scene as a child.
	this->addChild(square);
	this->addChild(square2);
	this->addChild(player);
	this->addChild(floor);

	// initialise the gravity
	this->gravity = Point2(0.0, 6000);

	// add all obstacles to the list
	obstacles.push_back(square);
	obstacles.push_back(square2);

	std::cout << "floor" << floor->position.y - floor->sprite()->size.y << std::endl;
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

	if (player->onFloor(floor))
	{
		player->position.y = floor->position.y - floor->sprite()->size.y;
		player->velocity *= 0;
	}

	if (input()->getKeyDown(KeyCode::Space))
	{
		if (player->onFloor(floor))
		{
			std::cout << "floor " << floor->position.y - floor->sprite()->size.y << std::endl;
			player->jump();
		}
	}

	for (const auto obstacle : this->obstacles)
	{
		obstacle->position += Point3(-100, 0, 0) * deltaTime;
	}
}

// velocity is constantly being decreased by gravity
// gravity is exponentional so it needs to somehow speed up while
// the cube is in the air
// when you jump you boost the velocity by a big number and then gravity
// will slowly take over and slow the cube down, until it starts falling down again