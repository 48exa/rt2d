/**
 * This class describes Jumper behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>
#include <iostream>

#include "jumper.h"

#define COLLIDER_DEBUG false

Jumper::Jumper() : Scene()
{
	// start the timer.
	t.start();
	layer = new ObstacleLayer();

	this->_distance = 900;

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
	std::vector<unsigned short> level_layout{
			0, 0, 129, 129, 1, 129, 67, 18, 18, 67,
			129, 129, 129, 1, 32, 84, 32, 0, 131, 128,
			3, 129, 129, 7, 129, 129, 15, 129, 129, 31,
			129, 129, 63, 129, 129, 127, 99, 51, 27, 15,
			7, 3, 1, 0, 0, 129, 129, 1, 1, 135,
			3, 2, 2, 3, 129, 129, 129, 0, 0, 0,
			60, 36, 44, 0, 60, 36, 44, 0, 52, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 127};

	level_creator(level_layout);
}

Jumper::~Jumper()
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

void Jumper::place_obstacle(unsigned short chunk, bool hostile)
{
	// Make a decrementing for loop that runs 8 times
	for (unsigned char i = 8; i > 0; --i)
	{
		// Use bitwise AND to compare the chunk and 128 in hex, if the binary representation of the
		// chunk contains a 1 on any of the first 7 spots we will place an obstacle
		// (most significant bit is used to determine obstacle type, 0 for square, 1 for spike)
		if (0x80 & chunk && i < 8)
			obstacles.push_back(new Obstacle(Vector2(_distance, 752 - (64 * i)), hostile));
		// Bitshift to the left by one
		chunk = chunk << 1;
	}
}

void Jumper::level_creator(std::vector<unsigned short> bytearray)
{
	// Loop over every number in the vector of ints
	for (unsigned short chunk : bytearray)
	{
		// If the number is bigger than 128 (0b10000000) it places a spike
		if (chunk >= 128)
			place_obstacle(chunk, true);
		else
			place_obstacle(chunk, false);
		_distance += 64;

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

bool Jumper::player_square_collision(Player *p, Obstacle *obs)
{
	float CircleX = p->position.x + 32;
	float CircleY = p->position.y + 32;
	float RectX = obs->position.x + layer->position.x;
	float RectY = obs->position.y + layer->position.y;
	short RectWidth = obs->sprite()->size.x;
	short RectHeight = obs->sprite()->size.y;

	float DeltaX = CircleX - std::max(RectX, std::min(CircleX, RectX + RectWidth));
	float DeltaY = CircleY - std::max(RectY, std::min(CircleY, RectY + RectHeight));

	return (DeltaX * DeltaX + DeltaY * DeltaY) < (PLAYER_HITBOX_SIZE * PLAYER_HITBOX_SIZE);
}

bool Jumper::player_spike_collision(Player *p, Obstacle *obs)
{
	float dx = p->position.x - (obs->position.x + layer->position.x);
	float dy = p->position.y - (obs->position.y + 8);
	short radii = PLAYER_HITBOX_SIZE + SPIKE_HITBOX_SIZE;

	return (dx * dx + dy * dy) < (radii * radii);
}

bool Jumper::landing_collision(Player *p, Obstacle *obs)
{
	unsigned short obj_size = 32;

	return (p->position.x < (obs->position.x + obj_size) - layer->position.x &&
					p->position.x + obj_size > (obs->position.x - obj_size) + layer->position.x &&
					p->position.y < obs->position.y - obj_size);
}

void Jumper::handle_misc_key_events()
{
	if (input()->getKeyUp(KeyCode::Escape))
		this->stop();

	if (input()->getKey(KeyCode::Space))
		if (player->on_floor() || player->overlapping)
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

bool Jumper::in_collision_range(Obstacle *obstacle)
{
	short single_sprite_size = 64;
	short one_half_sprite_size = 96;

	return obstacle->position.x + layer->position.x > player->position.x - single_sprite_size &&
				 obstacle->position.x + layer->position.x < player->position.x + one_half_sprite_size &&
				 obstacle->position.y > player->position.y - one_half_sprite_size &&
				 obstacle->position.y < player->position.y + one_half_sprite_size;
}

void Jumper::update(float deltaTime)
{
#if COLLIDER_DEBUG
	ddClear();
	ddCircle((player->position.x + 32) - 32, (player->position.y + 32) - 32, 32, BLUE);
#endif

	// ddCircle(player->position.x, player->position.y, 32, RED);
	handle_misc_key_events();

	// addforce
	player->add_force(this->gravity);

	// movement 101
	player->movement(deltaTime);

	player->overlapping = false;

	// loop over all obstacles to check for collision with the player
	for (const auto &obstacle : obstacles)
	{
		obstacle->sprite()->color = WHITE;

#if COLLIDER_DEBUG
		if (obstacle->isHostile())
			ddCircle((obstacle->position.x + layer->position.x), obstacle->position.y + 8, 16, RED);
		else
			obstacle->sprite()->color = RED;
#endif

		if (in_collision_range(obstacle))
		{

#if COLLIDER_DEBUG
			obstacle->sprite()->color = GREEN;
#endif

			if (obstacle->isHostile())
			{
				if (player_spike_collision(player, obstacle))
					layer->resetPosition();
				continue;
			}

			// if the player is not colliding go back to the top
			if (!player_square_collision(player, obstacle))
			{
				continue;
			}

			if (landing_collision(player, obstacle))
			{
				// set the player ontop of the obstacle
				player->position.y = obstacle->position.y - obstacle->sprite()->size.y;
				player->overlapping = true;
				player->reset_movement();
			}
			else
				layer->resetPosition();
		}
	}
}
