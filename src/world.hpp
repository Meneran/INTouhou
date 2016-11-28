#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include "component.hpp"
#include "life.hpp"
#include "sprite.hpp"
#include "position.hpp"
#include "display.hpp"
#include "event.hpp"
#include "playermove.hpp"
#include "keycontroller.hpp"
#include "bulletmove.hpp"
#include "target.hpp"
#include "dynamics.hpp"
#include "createPlayerBullet.hpp"
#include "createenemybullet.hpp"
#include "enemymove.hpp"
#include "collide.hpp"
#include "hitbox.hpp"

typedef enum {
  PLAYING,
  LOSE,
  TRIGGERLOSE,
  WIN,
  TRIGGERWIN,
} GameState;


class World {
 private:
  sf::RenderWindow mWindow;
  // systems
  Display mDisplay;
  PlayerMove mPlayerMove;
  KeyController mKeyController;
  BulletMove mBulletMove;
  CreatePlayerBullet mCreatePlayerBullet;
  CreateEnemyBullet mCreateEnemyBullet;
  EnemyMove mEnemyMove;
  Collide mCollide;

  std::vector<Dynamics> mDynamics;
  std::vector<Event> mEvent;
  std::vector<Hitbox> mHitbox;
  std::vector<Life> mLife;
  std::vector<Position> mPosition;
  std::vector<Sprite> mSprite;
  std::vector<Target> mTarget;

  std::vector<EntityType> mEntityType;  //  Not defined in the mBitset vector

  std::vector<std::vector<bool>> mBitset;

  sf::Clock mClock;

  float mScore;
  GameState mGameState;
  bool mRetry = false;
  bool mEnd = false;


 public:
  World();
  void createBullet(Position &pos, std::string spritePath, TargetType type,
                    PatternType pattern = PATTERN1);
  void createEnemy();
  void createPlayer();
  void run();

  std::vector<bool>& getBitset(ComponentType type);
  Sprite& getSprite(int ind);
  Position& getPosition(int ind);
  Event& getEvent(int ind);
  Dynamics& getDynamic(int ind);
  int getTime();
  EntityType& getEntityType(int ind);
  void removeEntity(int ind);
  Target& getTarget(int ind);
  Life& getLife(int ind);
  Hitbox& getHitbox(int ind);
  int getScore();
  void modifyScore(int score);
  GameState getGameState();
  void setEnd();
  void setRetry();
  bool getRetry();
  bool getEnd();

 private:
  int getNextUnusedIndex();
  void changeGameState();
};
