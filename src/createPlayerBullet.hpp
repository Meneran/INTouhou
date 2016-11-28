#pragma once
#include "system.hpp"

class World;

class CreatePlayerBullet : public System {
 private:
  int mLastTime;
 public:
  CreatePlayerBullet();
  void run(World &world);
};

