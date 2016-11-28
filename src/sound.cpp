#include "sound.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>
#include <string>
#include <utility>

std::map<std::string, sf::SoundBuffer> Sound::mPoolBuffer;
std::map<std::string, sf::Sound> Sound::mPoolSound;

Sound::Sound() {
  mSound = NULL;
}

Sound::Sound(const std::string &snd) {
  set(snd);
}

void Sound::set(const std::string &snd) {
  doSet(snd);
  mSound = &(mPoolSound[snd]);
}

/* You can play multiple sounds at the same time
 * But you can only play the same song once at the same time */
void Sound::play(const std::string &snd) {
  doSet(snd);
  mPoolSound[snd].play();
}

void Sound::stop() {
  for (auto &n : mPoolSound)
    n.second.stop();
}

void Sound::doSet(const std::string &snd) {
  if (mPoolBuffer.insert(std::make_pair(snd, sf::SoundBuffer())).second) {
    if (!mPoolBuffer[snd].loadFromFile(snd))
      std::cout << "erreur" << std::endl;
    mPoolSound.insert(std::make_pair(snd, sf::Sound()));
    mPoolSound[snd].setBuffer(mPoolBuffer[snd]);
  }
}

