#pragma once
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800


class Position {
 private:
  float mX;
  float mY;
 public:
  Position();
  Position(float x, float y);
  void move(float x, float y);
  void setX(float x);
  void setY(float y);
  float x();
  float y();
};
