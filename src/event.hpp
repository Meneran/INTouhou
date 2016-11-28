#pragma once
#include <vector>
#include "component.hpp"

class Event {
 private:
  std::vector<bool> mMove;

 public:
  Event();
  void pushDirection(Direction dir);
  void popDirection(Direction dir);
  void EmptyDirection();
  std::vector<bool> getMove();
};
