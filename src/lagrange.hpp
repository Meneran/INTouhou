#pragma once
#include <boost/math/tools/polynomial.hpp>
#include <vector>

class Lagrange {
 private:
  boost::math::tools::polynomial<float> mPol;

 public:
  void genPol(std::vector<float> x, std::vector<float> y);
  float evaluate(float x);
};

