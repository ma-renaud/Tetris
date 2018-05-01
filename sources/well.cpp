#include "well.h"

Well::Well() {
  init();
}

void Well::init() {
  for (int i = 0; i < HEIGHT - 1; i++) {
    well[i] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  }
  well[HEIGHT - 1] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
}

uint8_t Well::get_tile(int x, int y) {
  return well.at(static_cast<unsigned long>(x)).at(static_cast<unsigned long>(y));
}
