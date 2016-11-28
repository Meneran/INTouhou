#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class Sprite {
 private:
  static std::map<std::string, sf::Texture> mPoolTexture;
  static std::map<std::string, sf::Sprite> mPoolSprite;
  sf::Sprite *mSprite;

 public:
  Sprite();
  Sprite(const std::string &img);
  sf::Sprite& getSprite(float x, float y);
  int getSizeX();
  int getSizeY();
  void set(const std::string &img);
};

