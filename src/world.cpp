#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstddef>
#include <string>
#include <cassert>
#include "sound.hpp"

World::World() :
  mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "INTouhou"),
  mDisplay(mWindow),
  mKeyController(mWindow),
  mScore(10000),
  mGameState(PLAYING) {
  Sound::play("../sounds/music.wav");
  mWindow.setKeyRepeatEnabled(false);
  mWindow.setFramerateLimit(60);
  // entity number 0 is player
  for (int i = 0; i < COMPONENTNUMBER; ++i)
    mBitset.push_back(std::vector<bool>());
}

void World::run() {
  createPlayer();
  createEnemy();

  mClock.restart();
  while (mWindow.isOpen()) {
    while (mWindow.isOpen() && mGameState == PLAYING) {
      mScore -= 0.5;
      changeGameState();
      mKeyController.run(*this);
      mCreatePlayerBullet.run(*this);
      mCreateEnemyBullet.run(*this);
      mBulletMove.run(*this);
      mEnemyMove.run(*this);
      mPlayerMove.run(*this);
      mCollide.run(*this);
      mDisplay.run(*this);
    }
    changeGameState();
    mKeyController.run(*this);
    mDisplay.run(*this);
  }
}

void World::createPlayer() {
  int i = getNextUnusedIndex();

  mBitset[EVENT][i] = true;
  mBitset[LIFE][i] = true;
  mBitset[POSITION][i] = true;
  mBitset[SPRITE][i] = true;
  mBitset[HITBOX][i] = true;

  mEvent[i].EmptyDirection();
  mLife[i].setLife(5);
  mPosition[i].setX(WINDOW_WIDTH/2 - 40);
  mPosition[i].setY(5*WINDOW_HEIGHT/6);
  mSprite[i].set("../sprite/vaisseau.png");
  TargetType tt = NOTARGET;
  mTarget[i].setTarget(tt);
  mEntityType[i] = PLAYERSHIP;
  mHitbox[i].setSize(mSprite[i].getSizeX(), mSprite[i].getSizeY());
  mHitbox[i].setShift(55, 55);
}

void World::createEnemy() {
  int i = getNextUnusedIndex();

  mBitset[HITBOX][i] = true;
  mBitset[LIFE][i] = true;
  mBitset[POSITION][i] = true;
  mBitset[SHOOT][i] = true;
  mBitset[SPRITE][i] = true;

  mEvent[i].EmptyDirection();
  mLife[i].setLife(200);
  mPosition[i].setX(0);
  mPosition[i].setY(0);
  mSprite[i].set("../sprite/enemyShip.png");
  TargetType tt = NOTARGET;
  mTarget[i].setTarget(tt);
  mEntityType[i] = ENEMYSHIP;
  mHitbox[i].setSize(mSprite[i].getSizeX(), mSprite[i].getSizeY());
  mHitbox[i].setShift(50, 50);
}

// the position pos is the center of the bullet
void World::createBullet(Position& pos, std::string spritePath,
                         TargetType type, PatternType pattern) {
  int i = getNextUnusedIndex();

  mBitset[DYNAMICS][i] = true;
  mBitset[HITBOX][i] = true;
  mBitset[POSITION][i] = true;
  mBitset[SPRITE][i] = true;
  mBitset[TARGET][i] = true;

  mEvent[i].EmptyDirection();
  mLife[i].setLife(5);
  mSprite[i].set(spritePath);
  float X = pos.x() - mSprite[i].getSizeX()/2;
  float Y = pos.y() - mSprite[i].getSizeY()/2;
  mPosition[i].setX(X);
  mPosition[i].setY(Y);
  TargetType tt = type;
  mTarget[i].setTarget(tt);
  mEntityType[i] = BULLET;
  mHitbox[i].setSize(mSprite[i].getSizeX(), mSprite[i].getSizeY());
  mDynamics[i].genPattern(mPosition[i], mPosition[0], pattern);
  // if the bullet is a player's bullet, the pattern dosen't matter

  if (spritePath == "../sprite/bulletEnemy.png")
    mHitbox[i].setShift(100, 100);
  else
    mHitbox[i].setShift(0, 0);
}

std::vector<bool>& World::getBitset(ComponentType type) {
  return mBitset[type];
}

Sprite& World::getSprite(int ind) {
  return mSprite[ind];
}

Position& World::getPosition(int ind) {
  return mPosition[ind];
}

Event& World::getEvent(int ind) {
  return mEvent[ind];
}

Dynamics& World::getDynamic(int ind) {
  return mDynamics[ind];
}

// what happens after 600 hours of play ?
int World::getTime() {
  return mClock.getElapsedTime().asMilliseconds();
}

EntityType& World::getEntityType(int ind) {
  return mEntityType[ind];
}

void World::removeEntity(int ind) {
  for (int i = 0; i < COMPONENTNUMBER; ++i)
    getBitset((ComponentType)i)[ind] = false;

  getEntityType(ind) = NOTDEFINED;
}

int World::getNextUnusedIndex() {
  for (int i = 0; i < COMPONENTNUMBER; ++i)
    assert(mEntityType.size() == mBitset[(ComponentType)i].size());

  if (mEntityType.size() != 0) {
    for (size_t i = 0; i < mEntityType.size(); ++i)
      if (mEntityType[i] == NOTDEFINED)
        return i;
  }

  for (int i = 0; i < COMPONENTNUMBER; ++i)
    mBitset[(ComponentType)i].push_back(false);

  /* These values are fake, they are changed in the entity constructor */
  mDynamics.push_back(Dynamics());
  mEvent.push_back(Event());
  mLife.push_back(Life(1000));
  mPosition.push_back(Position(0, 0));
  mSprite.push_back(Sprite());
  mSprite.back().set("../sprite/bulletPlayer.png");
  TargetType target = NOTARGET;
  mTarget.push_back(target);
  mEntityType.push_back(NOTDEFINED);
  mHitbox.push_back(Hitbox());

  return (mEntityType.size() - 1);
}

Target& World::getTarget(int ind) {
  return mTarget[ind];
}

Life& World::getLife(int ind) {
  return mLife[ind];
}

Hitbox& World::getHitbox(int ind) {
  return mHitbox[ind];
}

int World::getScore() {
  return mScore;
}

void World::modifyScore(int score) {
  mScore += score;
}

GameState World::getGameState() {
  return mGameState;
}

void World::changeGameState() {
  if (mGameState == TRIGGERWIN) {
    mGameState = WIN;
    Sound::stop();
    Sound::play("../sounds/win.wav");
  } else if (mGameState == TRIGGERLOSE) {
    mGameState = LOSE;
    Sound::stop();
    Sound::play("../sounds/gameOver.wav");
  } else if (mLife[0].getLife() < 1 && mGameState == PLAYING) {
      mGameState = TRIGGERLOSE;
    } else {
    bool enemy = false;
    for (size_t i = 1; i < mEntityType.size(); ++i)
      if (mEntityType[i] == ENEMYSHIP)
        enemy = true;
    if (!enemy && mGameState == PLAYING)
         mGameState = TRIGGERWIN;
  }
}

void World::setEnd() {
  mEnd = true;
}

void World::setRetry() {
  mRetry = true;
  Sound::stop();
}

bool World::getRetry() {
  return mRetry;
}

bool World::getEnd() {
  return mEnd;
}
