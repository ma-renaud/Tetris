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
  if (x < well.size() && y < well.at(static_cast<unsigned long>(x)).size())
    return well.at(static_cast<unsigned long>(x)).at(static_cast<unsigned long>(y));
  else
    return 0;
}

bool Well::is_block(int x, int y) {
  return get_tile(x, y) > 0;
}

bool Well::is_collision(Tetromino *tetromino) {
  bool res = false;
  for (int i = 0; i < tetromino->matrix_size(); i++) {
    for (int j = 0; j < tetromino->matrix_size(); j++) {
      if (tetromino->is_present(i, j) && is_block(i + tetromino->ypos(), j + tetromino->xpos())) {
        res = true;
      }
    }
  }
  return res;
}
