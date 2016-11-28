#include "target.hpp"

Target::Target(TargetType& tt) : mTargetType(tt) {
}

TargetType Target::getTarget() {
  return mTargetType;
}

void Target::setTarget(TargetType& tt) {
  mTargetType = tt;
}

