#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "system.hpp"
#include "sprite.hpp"

/**
 * Display a window with 2 views, one for the game, the second for the score
 */
class Display : public System {
 private:
  sf::RenderWindow &mWindow;
  sf::View mViewScore;
  sf::View mViewGame;
  Sprite mSpriteBackground;
  Sprite mVaisseau;

  std::map<std::string, sf::Sprite> mSprites;
  sf::Texture textureShip;

  sf::Text mScoreText;
  sf::Text mLifeText;
  sf::Font f;


 public:
  Display(sf::RenderWindow &w);
  void run(World &world) override;
};
