#include "playermove.hpp"
#include <vector>
#include <cstddef>
#include "component.hpp"
#include "event.hpp"
#include "position.hpp"
#include "sprite.hpp"
#include "world.hpp"

PlayerMove::PlayerMove() {
}

/**
 * Take the events of the player and move the player's ship
 */
void PlayerMove::run(World &world) {
  int speed = 5;
  for (size_t i = 0; i < world.getBitset(EVENT).size(); ++i) {
    if (world.getBitset(EVENT)[i]) {
      auto LIMIT_WIDTH = WINDOW_WIDTH - world.getSprite(i).getSizeX();
      auto LIMIT_HEIGHT = WINDOW_HEIGHT - world.getSprite(i).getSizeY();
      auto move = world.getEvent(i).getMove();
      auto &pos = world.getPosition(i);
      if (move[LEFT]) {
        if (pos.x() - speed < 0)
         pos.setX(0);
        else
          pos.move(-speed, 0);
      }
      if (move[RIGHT]) {
        if (pos.x() + speed > LIMIT_WIDTH)
          pos.setX(LIMIT_WIDTH);
        else
          pos.move(speed, 0);
      }
      if (move[UP]) {
        if (pos.y() - speed < 0)
          pos.setY(0);
        else
          pos.move(0, -speed);
      }
      if (move[DOWN]) {
        if (pos.y() + speed > LIMIT_HEIGHT)
          pos.setY(LIMIT_HEIGHT);
        else
          pos.move(0, speed);
      }
      if (move[BOMB]) {
        for (size_t j = 0; j < world.getBitset(TARGET).size(); ++j) {
          if (world.getEntityType(j) == BULLET)
            world.removeEntity(j);
        }
      }
    }
  }
}
