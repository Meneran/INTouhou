#include "lagrange.hpp"
#include <vector>
#include <cstddef>
#include <cassert>

/**
 * Evaluate the Lagrange polynomial in a point
 *
 * return value : y = P(x)
 *
 * Lagrange::genPol needs to be called before
 * this function can have a meaningful return value
 *
 */
float Lagrange::evaluate(float x) {
  float y = 0;
  for (size_t i = 0; i < mPol.size(); ++i) {
    float add = 1;
    for (size_t j = 0; j < i; ++j)
      add *= x;
    y += mPol[i]*add;
  }
  return y;
}

/**
 * Generate a Lagrange polynomial from a set of points
 *
 * It is the only polynomial P that satisfies :
 * P(x) = y for each point (x, y)
 * deg(P) = number of points
 *
 */
void Lagrange::genPol(std::vector<float> x, std::vector<float> y) {
  // or static_assert ?
  assert(x.size() == y.size());
  assert(x.size() > 1);
  auto size = x.size();

  // empirically X can't be set in constructor
  float seed = 0;
  // segfault if default constructor
  boost::math::tools::polynomial<float> X(&seed, 1);
  X[0] = 0;
  X[1] = 1;

  boost::math::tools::polynomial<float> unit(X);
  unit[0] = 1;
  unit[1] = 0;

  std::vector<boost::math::tools::polynomial<float>> ll(size, unit);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i !=j)
        ll[i] *= (X-x[j]) * (1 / (x[i]-x[j]));
    }
  }

  auto ans(unit);
  ans -= unit;

  for (int i = 0; i < size; ++i)
    ans += y[i]*ll[i];

  mPol = ans;
}

