// player.cpp

#include "player.h"

Player::Player() : Entity()
{
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

bool Player::onFloor(Floor *ground)
{
	if (this->position.y < ground->position.y - ground->sprite()->size.y)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Player::jump()
{
	this->velocity -= Point2(0.0, 1750);
}