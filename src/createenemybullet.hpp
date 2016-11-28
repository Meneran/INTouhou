#pragma once

class World;

class CreateEnemyBullet {
 private:
  int mLastTime;
  int mTimeBetweenBullet;
 public:
  CreateEnemyBullet();
  void run(World &world);
};
