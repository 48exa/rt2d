// obstaclelayer.cpp

#include "obstaclelayer.h"

ObstacleLayer::ObstacleLayer() : Entity()
{
}

ObstacleLayer::~ObstacleLayer()
{
}

void ObstacleLayer::update(float deltaTime)
{
	this->position += Point2(-100, 0) * deltaTime;
}