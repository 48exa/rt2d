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

	// initiate all obstacles
	obstacles.push_back(new Obstacle(Vector2(900, SHEIGHT - 32), true));

	obstacles.push_back(new Obstacle(Vector2(1100, SHEIGHT - 32), false));
	obstacles.push_back(new Obstacle(Vector2(1100, SHEIGHT - 32 - 64), false));

	obstacles.push_back(new Obstacle(Vector2(1270, SHEIGHT - 32), false));
	obstacles.push_back(new Obstacle(Vector2(1270 + 64, SHEIGHT - 32), false));

	for (size_t i = 0; i < 4; i++)
	{
		obstacles.push_back(new Obstacle(Vector2(1280, SHEIGHT - 32 - 64 * 2 - 64 * i), false));
	}
	for (size_t i = 0; i < 3; i++)
	{
		obstacles.push_back(new Obstacle(Vector2(1280 + 180, SHEIGHT - 32 - (64 * i)), false));
	}

	obstacles.push_back(new Obstacle(Vector2(1460 + 64, SHEIGHT - 32), true));
	obstacles.push_back(new Obstacle(Vector2(1460 + 64 * 2, SHEIGHT - 32), true));
	// create the scene 'tree'
	// add player to this Scene as a child.
	this->addChild(player);

	for (const auto obstacle : obstacles)
	{
		layer->addChild(obstacle);
	}

	this->addChild(layer);
}

Jumper01::~Jumper01()
{
	// deconstruct and delete the Tree
	this->removeChild(player);

	// delete player from the heap (there was a 'new' in the constructor)
	delete player;
	delete layer;
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
	// int CircleRadius = 19;
	// float CircleX = obstacle->position.x + layer->position.x + 32;
	// float CircleY = obstacle->position.y + layer->position.y + 12;
	// float RectX = player->position.x;
	// float RectY = player->position.y;
	// float RectWidth = player->sprite()->size.x;
	// float RectHeight = player->sprite()->size.y;

	// float DeltaX = CircleX - std::max(RectX, std::min(CircleX, RectX + RectWidth));
	// float DeltaY = CircleY - std::max(RectY, std::min(CircleY, RectY + RectHeight));
	// return (DeltaX * DeltaX + DeltaY * DeltaY) < (CircleRadius * CircleRadius);

	float DeltaX = obstacle->position.x + layer->position.x + 32 - std::max(player->position.x, std::min(obstacle->position.x + layer->position.x + 32, player->position.x + player->sprite()->size.x));
	float DeltaY = obstacle->position.y + layer->position.y + 12 - std::max(player->position.y, std::min(obstacle->position.y + layer->position.y + 12, player->position.y + player->sprite()->size.y));
	return (DeltaX * DeltaX + DeltaY * DeltaY) < (19 * 19);
}

void Jumper01::update(float deltaTime)
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

	if (player->onFloor())
	{
		player->setOnFloor();
		player->resetMovement();
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
		obstacles.push_back(new Obstacle(Vector2(1000 - layer->position.x, SHEIGHT - 32), false));
		layer->addChild(obstacles.back());
	}

	if (input()->getKeyDown(KeyCode::R))
	{
		layer->resetPosition();
	}
}
