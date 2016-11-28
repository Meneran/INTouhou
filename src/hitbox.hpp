#pragma once
#include <SFML/Graphics.hpp>

class Position;

class Hitbox {
 private:
  sf::RectangleShape mHitbox;
  float mX;
  float mY;
 public:
  Hitbox();
  void setSize(float w, float h);
  void setPosition(Position pos);
  void setShift(float x, float y);
  float x();
  float y();
  float w();
  float h();
  sf::RectangleShape& getHitbox();
};
