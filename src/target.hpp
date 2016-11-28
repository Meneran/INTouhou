#pragma once

#include "component.hpp"

class Target {
 private:
  TargetType mTargetType;

 public:
  Target(TargetType &tt);
  TargetType getTarget();
  void setTarget(TargetType& tt);
};

