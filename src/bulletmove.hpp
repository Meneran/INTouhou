#pragma once
#include "system.hpp"

class World;

class BulletMove : public System {
 public:
  BulletMove();
  void run(World &world);
};

