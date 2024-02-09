// obstaclelayer.cpp

#include "obstaclelayer.h"

ObstacleLayer::ObstacleLayer() : Entity()
{
	this->original_position = this->position.x;
}

ObstacleLayer::~ObstacleLayer()
{
	delete this;
}

void ObstacleLayer::update(float deltaTime)
{
	// move the object layer at a consistent speed to simulate the player moving
	this->position += Vector2(MOVEMENT_SPEED, 0) * deltaTime;
}

void ObstacleLayer::resetPosition()
{
	this->position.x = this->original_position;
}
