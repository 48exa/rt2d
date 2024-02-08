/**
 * This class describes Jumper01 behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <iostream>

#include "jumper01.h"

#define COLLIDER_DEBUG true

Jumper01::Jumper01() : Scene()
{
	// start the timer.
	t.start();
	layer = new ObstacleLayer();

	this->distance = 900;

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

	// The level in 8 bit signed ints
	std::vector<int> level_layout{
			0, 0, 129, 129, 1, 129, 67, 18, 18, 67,
			129, 129, 129, 1, 32, 84, 32, 0, 131, 128,
			3, 129, 129, 7, 129, 129, 15, 129, 129, 31,
			129, 129, 63, 129, 129, 127, 99, 51, 27, 15,
			7, 3, 1, 0, 0, 129, 129, 1, 1, 135,
			3, 2, 2, 3, 129, 129, 129, 0, 0, 0,
			60, 36, 44, 0, 60, 36, 44, 0, 52, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 255,
			255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

	level_creator(level_layout);
}

Jumper01::~Jumper01()
{
	// deconstruct and delete the Tree
	this->removeChild(layer);
	this->removeChild(player);
	for (auto const &obstacle : obstacles)
	{
		layer->removeChild(obstacle);
		delete obstacle;
	}

	// delete player from the heap (there was a 'new' in the constructor)
	delete player;
	delete layer;
}

void Jumper01::place_obstacle(int chunk, bool hostile)
{
	// Make a decrementing for loop that runs 8 times
	for (uint8_t i = 8; i > 0; --i)
	{
		// Use bitwise AND to compare the chunk and 128 in hex, if the binary representation of the
		// chunk contains a 1 on any of the first 7 spots we will place an obstacle
		// (most significant bit is used to determine obstacle type, 0 for square, 1 for spike)
		if (0x80 & chunk && i < 8)
			obstacles.push_back(new Obstacle(Vector2(distance, 752 - (64 * i)), hostile));
		// Bitshift to the left by one
		chunk = chunk << 1;
	}
}

void Jumper01::level_creator(std::vector<int> bytearray)
{
	// Loop over every number in the vector of ints
	for (int chunk : bytearray)
	{
		// If the number is bigger than 128 (0b10000000) it places a spike
		if (chunk >= 128)
			place_obstacle(chunk, true);
		else
			place_obstacle(chunk, false);
		distance += 64;

		// add all obstacles to the vector
		for (auto const &obstacle : obstacles)
		{
			layer->addChild(obstacle);
		}
		// add the layer to the scene
		this->addChild(layer);
	}
	std::cout << "obstacles: " << obstacles.size() << std::endl;
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

// https://yal.cc/rectangle-circle-intersection-test/
bool Jumper01::circleAABB(Obstacle *obstacle)
{
	float CircleX = obstacle->position.x + layer->position.x + 32;
	float CircleY = obstacle->position.y + layer->position.y + 32;
	float RectX = player->position.x;
	float RectY = player->position.y;
	float RectWidth = player->sprite()->size.x;
	float RectHeight = player->sprite()->size.y;

	float DeltaX = CircleX - std::max(RectX, std::min(CircleX, RectX + RectWidth));
	float DeltaY = CircleY - std::max(RectY, std::min(CircleY, RectY + RectHeight));
	return (DeltaX * DeltaX + DeltaY * DeltaY) < (16 * 16);
}

void Jumper01::handleMiscKeyEvents()
{
	if (input()->getKeyUp(KeyCode::Escape))
		this->stop();

	if (input()->getKey(KeyCode::Space))
		if (player->onFloor() || player->overlapping)
			player->jump();

	if (input()->getKeyDown(KeyCode::A))
	{
		// add a new obstacle to 1000 pixels from the current layer position
		obstacles.push_back(new Obstacle(Vector2(1000 - layer->position.x, GROUND_PLAYER_OFFSET), false));
		layer->addChild(obstacles.back());
	}

	if (input()->getKeyDown(KeyCode::R))
		layer->resetPosition();
}

bool Jumper01::in_collision_range(Obstacle *obstacle)
{
	return obstacle->position.x + layer->position.x > player->position.x - 64 &&
				 obstacle->position.x + layer->position.x < player->position.x + 128 &&
				 obstacle->position.y > player->position.y - 128 &&
				 obstacle->position.y < player->position.y + 128;
}

void Jumper01::update(float deltaTime)
{
	handleMiscKeyEvents();

	// addforce
	player->addForce(this->gravity);

	// movement 101
	player->movement(deltaTime);

	player->overlapping = false;

	// loop over all obstacles to check for collision with the player
	for (const auto &obstacle : obstacles)
	{
#if COLLIDER_DEBUG true
		obstacle->sprite()->color = RED;
#endif
		if (in_collision_range(obstacle))
		{
#if COLLIDER_DEBUG true
			obstacle->sprite()->color = GREEN;
#endif
			if (obstacle->isHostile())
			{
				if (circleAABB(obstacle))
					layer->resetPosition();
				continue;
			}

			// if the player is not colliding go back to the top
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
				layer->resetPosition();
		}
	}
}
