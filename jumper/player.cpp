// player.cpp

#include "player.h"

Player::Player() : Entity()
{
	this->addSprite("assets/gdcube.tga");
	this->sprite()->color = WHITE;
	this->rotationSpeed = 0;
	this->quarter_pi = HALF_PI / 2;
}

Player::~Player()
{
	delete this;
}

void Player::update(float deltaTime)
{
	if (onFloor() || this->overlapping)
	{
		this->rotation.z *= 0;
	}
	else
	{
		if (this->rotation.z > TWO_PI)
		{
			this->rotation.z -= TWO_PI;
		}
		this->rotation.z += TWO_PI * deltaTime;
	}
}

void Player::addForce(Vector2 force)
{
	this->acceleration += force;
}

bool Player::onFloor()
{
	return this->position.y < GROUND_PLAYER_OFFSET ? false : true;
}

void Player::jump()
{
	this->velocity -= Vector2(0.0, 1350);
}

void Player::movement(float deltaTime)

{
	this->velocity += this->acceleration * deltaTime;
	this->position += this->velocity * deltaTime;
	this->acceleration *= 0;
}

void Player::resetMovement()
{
	this->velocity *= 0;
}

void Player::setOnFloor()
{
	this->position.y = GROUND_PLAYER_OFFSET;
}