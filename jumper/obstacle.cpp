// obstacle.cpp

#include "obstacle.h"

Obstacle::Obstacle(const Vector2 pos, const bool hostile) : Entity()
{
  this->position = pos;
  this->_hostile = hostile;

  if (this->_hostile)
    this->addSprite("assets/spike.tga");
  else
    this->addSprite("assets/gdsquare.tga");
}

Obstacle::~Obstacle()
{
  delete this;
}

void Obstacle::update(float deltaTime)
{
}

const bool Obstacle::is_hostile() const
{
  return this->_hostile;
}