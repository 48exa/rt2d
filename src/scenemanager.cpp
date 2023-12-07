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
	layer = new ObstacleLayer();

	// initialise the gravity
	this->gravity = Point2(0.0, GRAVITY);

	// initialise the list of all obstacles
	obstacles = std::vector<Obstacle *>();

	// create a single instance of Player in the middle of the screen.
	// the Sprite is added in Constructor of Player.
	player = new Player();
	player->position = Point2(SWIDTH / 2, SHEIGHT / 2);

	// initiate all obstacles
	obstacles.push_back(new Obstacle(Point2(SWIDTH / 1.5, SHEIGHT - 32), false, "assets/gdsquare.tga"));
	obstacles.push_back(new Obstacle(Point2(SWIDTH / 1.3, SHEIGHT - 32), false, "assets/gdsquare.tga"));
	// obstacles.push_back(new Obstacle(Point2(SWIDTH - 64, SHEIGHT - 32), false, "assets/gdsquare.tga"));

	// create the scene 'tree'
	// add player to this Scene as a child.
	this->addChild(player);

	for (const auto obstacle : obstacles)
	{
		layer->addChild(obstacle);
	}

	this->addChild(layer);
}

SceneManager::~SceneManager()
{
	// deconstruct and delete the Tree
	this->removeChild(player);

	// delete player from the heap (there was a 'new' in the constructor)
	delete player;
}

bool SceneManager::AABB(Obstacle *obstacle)
{
	return (player->position.x < obstacle->position.x + obstacle->sprite()->size.x + layer->position.x &&
					player->position.x - player->sprite()->size.x - layer->position.x > obstacle->position.x - obstacle->sprite()->size.x * 2 &&
					player->position.y < obstacle->position.y + obstacle->sprite()->size.y - layer->position.y &&
					player->position.y + player->sprite()->size.y + layer->position.y > obstacle->position.y);
}

void SceneManager::update(float deltaTime)
{
	player->sprite()->color = WHITE;

	if (input()->getKeyUp(KeyCode::Escape))
	{
		this->stop();
	}

	// addforce
	player->addForce(this->gravity);

	// movement 101
	player->movement(deltaTime);

	for (const auto obs : obstacles)
	{
		if (AABB(obs))
		{
			player->sprite()->color = RED;
		}
	}

	if (player->onFloor())
	{
		player->position.y = SHEIGHT - 32;
		player->velocity *= 0;
	}

	if (input()->getKeyDown(KeyCode::Space))
	{
		if (player->onFloor())
		{
			player->jump();
		}
	}
}
