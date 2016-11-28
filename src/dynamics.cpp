#include "dynamics.hpp"
#include <vector>
#include "position.hpp"
#include "lagrange.hpp"
#include "component.hpp"

Dynamics::Dynamics() : mSpeedBulletPlayer(10), mSpeedEnemy(1) {
}

void Dynamics::genPol(std::vector<float> x, std::vector<float> y) {
  mLagrange.genPol(x, y);
}

void Dynamics::moveV(Position& pos) {
  pos.move(0, -mSpeedBulletPlayer);
}

/**
 * Move according to the pattern specified
 */
void Dynamics::movePattern(Position& pos) {
  pos.move(0, mSpeedEnemy*3);
  pos.setX(mLagrange.evaluate(pos.y()));
}

void Dynamics::moveH(Position& pos, bool right) {
  if (right)
    pos.move(mSpeedEnemy, 0);
  else
    pos.move(-mSpeedEnemy, 0);
}

void Dynamics::genPattern(Position &from, Position &to, PatternType pt) {
  std::vector<float> x;
  std::vector<float> y;
  switch (pt) {
    case PATTERN1:
        x = {from.x(), 3*WINDOW_WIDTH/4, to.x()};
        y = {from.y(), WINDOW_HEIGHT/2, to.y()};
      break;
    case PATTERN2:
      x = {from.x(), WINDOW_WIDTH/4, to.x()};
      y = {from.y(), WINDOW_HEIGHT/2, to.y()};
      break;
    case PATTERN3:
      x = {from.x(), from.x() + 50, from.x() - 50, from.x() - 50, 0};
      y = {from.y(), WINDOW_HEIGHT/4, WINDOW_HEIGHT/2,
           3*WINDOW_HEIGHT/4, WINDOW_HEIGHT};
      break;
    case PATTERN4:
      x = {from.x(), from.x() - 50, from.x() + 50, from.x() +50, WINDOW_WIDTH};
      y = {from.y(), WINDOW_HEIGHT/4, WINDOW_HEIGHT/2,
           3*WINDOW_HEIGHT/4, WINDOW_HEIGHT};
      break;
    default:
      break;
  }
  genPol(y, x);
}

