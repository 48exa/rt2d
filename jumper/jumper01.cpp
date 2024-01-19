/**
 * This class describes JMPR01 behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <iostream>

#include "jumper01.h"

Jumper01::Jumper01() : Scene()
{
	// start the timer.
	t.start();
	layer = new ObstacleLayer();

	// initialise the gravity
	this->gravity = Vector2(0.0, GRAVITY);

	// initialise the list of all obstacles
	obstacles = std::vector<Obstacle *>();

	// create a single instance of Player in the middle of the screen.
	// the Sprite is added in Constructor of Player.
	player = new Player();
	player->position = Vector2(SWIDTH / 2, SHEIGHT / 2);

	// create the scene 'tree'
	// add player to this Scene as a child.
	this->addChild(player);

	initLevel();
}

Jumper01::~Jumper01()
{
	// deconstruct and delete the Tree
	this->removeChild(player);

	// delete player from the heap (there was a 'new' in the constructor)
	delete player;
	delete layer;
}

void Jumper01::initLevel()
{
	// initiate all obstacles
	obstacles.push_back(new Obstacle(Vector2(900, GROUND_PLAYER_OFFSET), true));

	obstacles.push_back(new Obstacle(Vector2(1100, GROUND_PLAYER_OFFSET), false));
	obstacles.push_back(new Obstacle(Vector2(1100, GROUND_PLAYER_OFFSET - 64), false));

	obstacles.push_back(new Obstacle(Vector2(1270, GROUND_PLAYER_OFFSET), false));
	obstacles.push_back(new Obstacle(Vector2(1334, GROUND_PLAYER_OFFSET), false));

	for (size_t i = 0; i < 4; i++)
	{
		obstacles.push_back(new Obstacle(Vector2(1280, (GROUND_PLAYER_OFFSET - 128) - 64 * i), false));
	}
	for (size_t i = 0; i < 3; i++)
	{
		obstacles.push_back(new Obstacle(Vector2(1460, GROUND_PLAYER_OFFSET - (64 * i)), false));
	}

	obstacles.push_back(new Obstacle(Vector2(1524, GROUND_PLAYER_OFFSET), true));
	obstacles.push_back(new Obstacle(Vector2(1588, GROUND_PLAYER_OFFSET), true));

	for (const auto obstacle : obstacles)
	{
		layer->addChild(obstacle);
	}

	this->addChild(layer);
}

bool Jumper01::AABB(Obstacle *obstacle)
{
	return (player->position.x < obstacle->position.x + obstacle->sprite()->size.x + layer->position.x &&
					player->position.x - player->sprite()->size.x - layer->position.x > obstacle->position.x - obstacle->sprite()->size.x * 2 &&
					player->position.y < obstacle->position.y + obstacle->sprite()->size.y - layer->position.y &&
					player->position.y + player->sprite()->size.y + layer->position.y > obstacle->position.y);
}

bool Jumper01::landingCollision(Obstacle *obstacle)
{
	return (player->position.x < (obstacle->position.x + obstacle->sprite()->size.x / 2) - layer->position.x &&
					player->position.x + (player->sprite()->size.x / 2) > (obstacle->position.x - obstacle->sprite()->size.x / 2) + layer->position.x &&
					player->position.y < obstacle->position.y - obstacle->sprite()->size.y / 2);
}

bool Jumper01::circleAABB(Obstacle *obstacle)
{
	float DeltaX = obstacle->position.x + layer->position.x + (obstacle->sprite()->size.x / 2) - std::max(player->position.x, std::min(obstacle->position.x + layer->position.x + (obstacle->sprite()->size.x / 2), player->position.x + player->sprite()->size.x));
	float DeltaY = obstacle->position.y + layer->position.y + SPIKE_HITBOX_Y_OFFSET - std::max(player->position.y, std::min(obstacle->position.y + layer->position.y + SPIKE_HITBOX_Y_OFFSET, player->position.y + player->sprite()->size.y));
	return (DeltaX * DeltaX + DeltaY * DeltaY) < (SPIKE_HITBOX_RADIUS_SQUARED);
}

void Jumper01::handleMiscKeyEvents()
{
	if (input()->getKeyUp(KeyCode::Escape))
	{
		this->stop();
	}

	if (input()->getKey(KeyCode::Space))
	{
		if (player->onFloor() || player->overlapping)
		{
			player->jump();
		}
	}

	if (input()->getKeyDown(KeyCode::A))
	{
		obstacles.push_back(new Obstacle(Vector2(1000 - layer->position.x, GROUND_PLAYER_OFFSET), false));
		layer->addChild(obstacles.back());
	}

	if (input()->getKeyDown(KeyCode::R))
	{
		layer->resetPosition();
	}
}

void Jumper01::update(float deltaTime)
{
	player->sprite()->color = WHITE;
	handleMiscKeyEvents();

	// addforce
	player->addForce(this->gravity);

	// movement 101
	player->movement(deltaTime);

	player->overlapping = false;
	for (const auto obstacle : obstacles)
	{
		if (obstacle->hostile)
		{
			if (circleAABB(obstacle))
			{
				layer->resetPosition();
			}
			continue;
		}

		if (!AABB(obstacle))
		{
			continue;
		}

		if (landingCollision(obstacle))
		{
			// set the player ontop of the obstacle
			player->position.y = obstacle->position.y - obstacle->sprite()->size.y;
			player->overlapping = true;
			player->resetMovement();
		}
		else
		{
			layer->resetPosition();
		}
	}
}
