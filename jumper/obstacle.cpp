// obstacle.cpp

#include "obstacle.h"

Obstacle::Obstacle(Vector2 pos, bool hostile) : Entity()
{
  this->position = pos;
  this->hostile = hostile;
  if (this->hostile)
  {
    this->addSprite("assets/spike.tga");
  }
  else
  {
    this->addSprite("assets/gdsquare.tga");
  }
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(float deltaTime)
{
}

