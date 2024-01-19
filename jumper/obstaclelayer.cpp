// obstaclelayer.cpp

#include "obstaclelayer.h"

ObstacleLayer::ObstacleLayer() : Entity()
{
	this->originalPosition = this->position.x;
}

ObstacleLayer::~ObstacleLayer()
{
}

void ObstacleLayer::update(float deltaTime)
{
	this->position += Vector2(MOVEMENT_SPEED, 0) * deltaTime;
}

void ObstacleLayer::resetPosition()
{
	this->position.x = this->originalPosition;
}