// obstacle.cpp

#include "obstacle.h"

Obstacle::Obstacle(Point2 pos, bool hostile, std::string spritePath) : Entity()
{
  this->position = pos;
  this->hostile = hostile;
  this->addSprite(spritePath);
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(float deltaTime)
{
}