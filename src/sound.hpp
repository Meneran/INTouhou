#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <map>

class Sound {
 private:
  static std::map<std::string, sf::SoundBuffer> mPoolBuffer;
  static std::map<std::string, sf::Sound> mPoolSound;
  sf::Sound *mSound;

 public:
  Sound();
  Sound(const std::string &snd);
  void set(const std::string &snd);
  static void play(const std::string &snd);
  static void stop();

 private:
  static void doSet(const std::string &snd);
};

