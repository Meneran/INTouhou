#pragma once

typedef enum {
  PATTERN1,
  PATTERN2,
  PATTERN3,
  PATTERN4,
  PATTERNUMBER,
} PatternType;

typedef enum {
  ANIMATION,
  DYNAMICS,
  EVENT,
  HITBOX,
  LIFE,
  POSITION,
  SHOOT,
  SPRITE,
  TARGET,
  COMPONENTNUMBER,
} ComponentType;

typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  BOMB,
  NONE,
} Direction;

typedef enum {
  PLAYER,
  ENEMY,
  NOTARGET,
} TargetType;

typedef enum {
  PLAYERSHIP,
  ENEMYSHIP,
  BULLET,
  NOTDEFINED,
} EntityType;

class Component {
 public:
 private:
};

