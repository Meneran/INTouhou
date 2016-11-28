#include "event.hpp"
#include <vector>
#include <cstddef>
#include "component.hpp"

/**
 * The player's ship can move in multiple directions at the same time
 */
Event::Event() {
  mMove = std::vector<bool>(5, false);
}

void Event::pushDirection(Direction dir) {
  mMove[dir] = true;
}

void Event::popDirection(Direction dir) {
  mMove[dir] = false;
}

std::vector<bool> Event::getMove() {
  return mMove;
}

void Event::EmptyDirection() {
  for (size_t i = 0; i < mMove.size(); ++i)
    mMove[i] = false;
}
