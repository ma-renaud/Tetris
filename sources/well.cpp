#include <numeric>
#include "well.h"

Well::Well() {
  init();
}

void Well::init() {
  empty_line = {42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42};
  clear();
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
  int row, col;
  for (int i = 0; i < tetromino->matrix_size(); i++) {
    for (int j = 0; j < tetromino->matrix_size(); j++) {
      col = j + tetromino->xpos();
      row = i + tetromino->ypos();
      if (tetromino->is_present(i, j) && is_block(row, col)) {
        return true;
      }
    }
  }
  return false;
}

void Well::add_to_well(Tetromino *tetromino) {
  int row, col;
  uint8_t tile;
  for (int i = 0; i < tetromino->matrix_size(); i++) {
    for (int j = 0; j < tetromino->matrix_size(); j++) {
      col = j + tetromino->xpos();
      row = i + tetromino->ypos();
      tile = tetromino->get_tile(i, j);
      if (tile > 0 && row < well.size() && col < well.at(static_cast<unsigned long>(row)).size()) {
        well[row][col] = tile;
      }
    }
  }
}

int Well::clear_lines() {
  int nb_lines = 0;
  bool full_line;
  for (int i = HEIGHT - 2; i >= 0; i--) {
    if (well[i] != empty_line) {
      full_line = true;
      for (int j = 1; j < WIDTH-1; j++) {
        if (!is_block(i, j)){
          full_line = false;
          break;
        }
      }
      if (full_line) {
        clear_line(i);
        nb_lines++;
        ++i;
      }
    }
  }
  return nb_lines;
}

void Well::clear_line(int line_index) {
  for (int i = line_index; i > 0; i--) {
    well[i] = well[i-1];
  }
}

void Well::clear() {
  for (int i = 0; i < HEIGHT - 1; i++) {
    well[i] = empty_line;
  }
  well[HEIGHT - 1] = {42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
}
