#ifndef TETRIS_WELL_H
#define TETRIS_WELL_H

#include <array>
#include "tetromino.h"

class Well {
public:
  Well();
  ~Well() = default;

  static constexpr uint8_t WIDTH = 12;
  static constexpr uint8_t HEIGHT = 22;

  uint8_t get_tile(int x, int y);
  bool is_block(int x, int y);
  bool is_collision(Tetromino* tetromino);
  void add_to_well(Tetromino* tetromino);
  int clear_lines();
  void clear();

protected:
  std::array<std::array<uint8_t, WIDTH>, HEIGHT> well;

private:
  int xpos = 0;
  int ypos = 0;

  std::array<uint8_t, WIDTH> empty_line;

  void init();
  void clear_line(int line_index);
};

#endif //TETRIS_WELL_H
