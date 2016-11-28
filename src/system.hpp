#pragma once

class World;

/**
 * Abstract class
 * Each system runs continuously and perform global actions on every Entity
 */
class System {
 public:
  virtual void run(World &world) = 0;
  virtual ~System() {}
};
