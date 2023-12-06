// floor.h
#ifndef FLOOR_H
#define FLOOR_H
#include <entity.h>
class Floor : public Entity
{
public:
  Floor();
  virtual ~Floor();
  virtual void update(float deltaTime);

private:
  /* add your private declarations */
};
#endif /* FLOOR_H */