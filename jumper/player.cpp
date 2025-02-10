// player.cpp

#include "player.h"

Player::Player() : Entity()
{
	this->addSprite("assets/gdsquare.tga");
	this->sprite()->color = WHITE;
}

Player::~Player()
{
	delete this;
}

void Player::update(float deltaTime)
{
	// rotate the player if the player is in the air
	if (on_floor() || this->overlapping)
		this->rotation.z *= 0;
	else
	{
		if (this->rotation.z > TWO_PI)
			this->rotation.z -= TWO_PI;
		this->rotation.z += TWO_PI * deltaTime;
	}

	if (this->on_floor())
	{
		this->set_on_floor();
		this->reset_movement();
	}
}

const void Player::add_force(const Vector2 force)
{
	this->acceleration += force;
}

const bool Player::on_floor() const
{
	return this->position.y < GROUND_PLAYER_OFFSET ? false : true;
}

const void Player::jump()
{
	this->velocity -= Vector2(0.0, JUMP_VALUE);
}

const void Player::movement(const float deltaTime)

{
	this->velocity += this->acceleration * deltaTime;
	this->position += this->velocity * deltaTime;
	this->acceleration *= 0;
}

const void Player::reset_movement()
{
	this->velocity *= 0;
}

const void Player::set_on_floor()
{
	this->position.y = GROUND_PLAYER_OFFSET;
}
