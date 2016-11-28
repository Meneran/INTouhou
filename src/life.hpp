#pragma once

class Life {
 private:
  int mLife;

 public:
  Life();
  Life(int initLife);
  void increaseLife();
  void decreaseLife();
  int getLife();
  void setLife(int l);
};
