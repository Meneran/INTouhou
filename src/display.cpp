#include "display.hpp"
#include <sstream>
#include <vector>
#include <cstddef>
#include "component.hpp"
#include "event.hpp"
#include "life.hpp"
#include "position.hpp"
#include "world.hpp"

Display::Display(sf::RenderWindow &w) :
  mWindow(w),
  mSpriteBackground("../sprite/background.png"),
  mVaisseau("../sprite/vaisseau.png") {
  int width = mWindow.getSize().x;
  int height = mWindow.getSize().y;
  float proportion = 0.1;

  mViewScore.reset(sf::FloatRect(0, 0, width, height * proportion));
  mViewScore.setViewport(sf::FloatRect(0.f, 0.9f, 1.f, 0.1f));

  mViewGame.reset(sf::FloatRect(0, 0, width, height));
  mViewGame.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f - proportion));

  f.loadFromFile("../sprite/arial.ttf");
  mScoreText.setFont(f);
  mScoreText.setPosition(sf::Vector2f(10, 20));
  mScoreText.setColor(sf::Color::Cyan);

  mLifeText.setFont(f);
  mLifeText.setPosition(sf::Vector2f(500, 20));
  mLifeText.setColor(sf::Color::Cyan);
}

/**
 * Display 2 views. One for the score and the life of the player.
 * The other one for the game. It displays a background sprite and
 * each entity's sprite
 */
void Display::run(World &world) {
  if (world.getEvent(0).getMove()[BOMB]) {
    sf::RectangleShape a(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    a.setFillColor(sf::Color(255, 255, 255, 255));
    mWindow.draw(a);
    mWindow.display();
    world.getEvent(0).popDirection(BOMB);
  } else {
  mWindow.clear(sf::Color::Black);
  mWindow.setView(mViewScore);
  std::ostringstream tmpScore;
  std::ostringstream tmpLife;
  tmpScore << "Score: " << world.getScore();
  mScoreText.setString(tmpScore.str());
  mWindow.draw(mScoreText);
  tmpLife << "Life: " << world.getLife(0).getLife();
  mLifeText.setString(tmpLife.str());
  mWindow.draw(mLifeText);
  mWindow.setView(mViewGame);
  mWindow.draw(mSpriteBackground.getSprite(0.0, 0.0));
  for (size_t i = 0; i < world.getBitset(SPRITE).size(); ++i) {
    if (world.getBitset(SPRITE)[i]) {
      float X = world.getPosition(i).x();
      float Y = world.getPosition(i).y();
      mWindow.draw(world.getSprite(i).getSprite(X, Y));
    }
  }
  if (world.getGameState() == LOSE) {
    sf::Text loseText("\t  YOU LOSE !\n\n"
                      "Press Enter to retry\n\n"
                      "Press Escape to quit", f);
    loseText.setPosition(150, 300);
    loseText.setColor(sf::Color::Red);
    mWindow.draw(loseText);
  } else if (world.getGameState() == WIN) {
    sf::Text winText("\tCongratulation !\n\n\t\t  YOU WIN\n\n "
                     " Press Enter to retry\n\n"
                     " Press Escape to quit", f);
    winText.setPosition(150, 300);
    winText.setColor(sf::Color::White);
    mWindow.draw(winText);
  }
  mWindow.display();
  }
}
