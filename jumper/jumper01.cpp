/**
 * This class describes Jumper01 behavior.
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

	std::vector<int> level_layout{
			0b00000000,
			0b00000000,
			0b10000001,
			0b10000001,
			0b00000001,
			0b10000001,
			0b01000011,
			0b00010010,
			0b00010010,
			0b01000011,
			0b10000001,
			0b10000001,
			0b10000001,
			0b00000001,
			0b00100000,
			0b01010100,
			0b00100000,
			0b00000000,
			0b10000011,
			0b10000000,
			0b00000011,
			0b10000001,
			0b10000001,
			0b00000111,
			0b10000001,
			0b10000001,
			0b00001111,
			0b10000001,
			0b10000001,
			0b00011111,
			0b10000001,
			0b10000001,
			0b00111111,
			0b10000001,
			0b10000001,
			0b01111111,
			0b01100011,
			0b00110011,
			0b00011011,
			0b00001111,
			0b00000111,
			0b00000011,
			0b00000001,
			0b00000000,
			0b00000000,
			0b10000001,
			0b10000001,
			0b00000001,
			0b00000001,
			0b10000111,
			0b00000011,
			0b00000010,
			0b00000010,
			0b00000011,
			0b10000001,
			0b10000001,
			0b10000001,
	};

	for (int item : level_layout)
	{
		std::cout << (int)item << ", ";
	}
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
	for (uint8_t i = 8; i > 0; --i)
	{
		if (0x80 & chunk && i < 8)
			obstacles.push_back(new Obstacle(Vector2(distance, 752 - (64 * i)), hostile));
		chunk = chunk << 1;
	}
}

void Jumper01::level_creator(std::vector<int> bytearray)
{
	for (int chunk : bytearray)
	{
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

void Jumper01::update(float deltaTime)
{
	handleMiscKeyEvents();

	// addforce
	player->addForce(this->gravity);

	// movement 101
	player->movement(deltaTime);

	player->overlapping = false;

	// loop over all obstacles to check for collision with the player
	for (auto const &obstacle : obstacles)
	{
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
