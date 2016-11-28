#pragma once
#include <SFML/Graphics.hpp>
#include "system.hpp"
#include "event.hpp"

class World;

class KeyController : public System {
 private:
  sf::RenderWindow &mWindow;
  sf::Event event;

 public:
  KeyController(sf::RenderWindow &window);
  void run(World &world);
};
