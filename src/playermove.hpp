#pragma once
#include "system.hpp"

class World;

class PlayerMove : public System{
 public:
  PlayerMove();
  void run(World &world);
};

