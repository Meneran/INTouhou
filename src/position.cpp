#include "position.hpp"

Position::Position() {}

Position::Position(float x, float y) : mX(x), mY(y) {}

float Position::x() { return mX; }

float Position::y() { return mY; }

/**
 * Relative move
 */
void Position::move(float x, float y) {
  mX += x;
  mY += y;
}

void Position::setX(float x) {
  mX = x;
}

void Position::setY(float y) {
  mY = y;
}
