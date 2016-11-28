#pragma once
#include "system.hpp"

class World;

class Collide : public System {
 public:
  Collide();
  void run(World &world);
};
