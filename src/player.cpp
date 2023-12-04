// player.cpp

#include "player.h"

Player::Player() : Entity()
{
	this->rotationSpeed = 0;
	this->addSprite("assets/gdcube.tga");
	this->sprite()->color = WHITE;
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
}

void Player::addForce(Point2 force)
{
	this->acceleration += force;
}

bool Player::onFloor(float ground)
{
	if (this->position.y < ground)
	{
		return false;
	}
	else
	{
		return true;
	}
}