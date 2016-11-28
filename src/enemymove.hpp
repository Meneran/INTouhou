#pragma once

#include "system.hpp"

class World;

class EnemyMove : public System {
 public:
  EnemyMove();
  void run(World &world);
};
