#include "hitbox.hpp"
#include "position.hpp"

Hitbox::Hitbox() {
}

void Hitbox::setPosition(Position pos) {
  mHitbox.setPosition(pos.x(), pos.y());
}

sf::RectangleShape &Hitbox::getHitbox() {
  return mHitbox;
}

void Hitbox::setSize(float w, float h) {
  mHitbox.setSize(sf::Vector2f(w, h));
}

void Hitbox::setShift(float x, float y) {
  mX = x;
  mY = y;
}

float Hitbox::x() {
  return mHitbox.getPosition().x + mX/2;
}

float Hitbox::y() {
  return mHitbox.getPosition().y + mY/2;
}

float Hitbox::w() {
  return mHitbox.getSize().x - mX;
}

float Hitbox::h() {
  return mHitbox.getSize().y - mY;
}
