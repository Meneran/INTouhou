#include "world.hpp"

int main() {
  bool end = false;
  while (!end) {
    bool retry = true;
    while (retry) {
      World w;
      w.run();
      retry = w.getRetry();
      end = w.getEnd();
    }
  }
  return 0;
}
