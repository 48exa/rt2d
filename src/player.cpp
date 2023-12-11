// player.cpp

#include "player.h"

Player::Player() : Entity()
{
	this->addSprite("assets/gdcube.tga");
	this->sprite()->color = WHITE;
}

Player::~Player()
{
	delete this;
}

void Player::update(float deltaTime)
{
}

void Player::addForce(Point2 force)
{
	this->acceleration += force;
}

bool Player::onFloor()
{
	return this->position.y < SHEIGHT - 32 ? false : true;
}

void Player::jump()
{
	this->velocity -= Point2(0.0, 1350);
	// this->addForce(Point2(0.0, 5500 * 100000000));
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
	this->position.y = SHEIGHT - 32;
}