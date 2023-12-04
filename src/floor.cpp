// floor.cpp

#include "floor.h"
#include <iostream>

Floor::Floor() : Entity()
{
  this->addSprite("assets/gdfloor.tga");
  this->sprite()->color = WHITE;
}

Floor::~Floor()
{

}



void Floor::update(float deltaTime) {

}
