#include "keycontroller.hpp"
#include "SFML/Graphics.hpp"
#include "event.hpp"
#include "component.hpp"
#include "world.hpp"

KeyController::KeyController(sf::RenderWindow &window) : mWindow(window) {
}

/**
 * Manage the events from the keyboard
 * When a key is pressed, the event component of the player is modified
 * You can press multiple keys at the same time
 */
void KeyController::run(World &world) {
    while (mWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        mWindow.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          mWindow.close();
          world.setEnd();
        }
        if (event.key.code == sf::Keyboard::Return &&
            world.getGameState() != PLAYING) {
          world.setRetry();
          mWindow.close();
        }

        if (event.key.code == sf::Keyboard::Up)
          world.getEvent(0).pushDirection(UP);
        if (event.key.code == sf::Keyboard::Down)
          world.getEvent(0).pushDirection(DOWN);
        if (event.key.code == sf::Keyboard::Left)
          world.getEvent(0).pushDirection(LEFT);
        if (event.key.code == sf::Keyboard::Right)
          world.getEvent(0).pushDirection(RIGHT);
        if (event.key.code == sf::Keyboard::Space) {
          world.getEvent(0).pushDirection(BOMB);
          world.modifyScore(-1000);
        }
      }

      if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up)
          world.getEvent(0).popDirection(UP);
        if (event.key.code == sf::Keyboard::Down)
          world.getEvent(0).popDirection(DOWN);
        if (event.key.code == sf::Keyboard::Left)
          world.getEvent(0).popDirection(LEFT);
        if (event.key.code == sf::Keyboard::Right)
          world.getEvent(0).popDirection(RIGHT);
        /* The bomb is poped automatically */
      }
  }
}
