#ifndef TETRIS_TETRIS_DRAWER_H
#define TETRIS_TETRIS_DRAWER_H

#include <SDL_system.h>
#include "well.h"
#include "tetromino.h"

class TetrisDrawer {
public:
  TetrisDrawer() = default;
  virtual ~TetrisDrawer() = default;

  virtual void draw(SDL_Renderer *renderer, Tetromino* tetromino) = 0;
  virtual void draw(SDL_Renderer *renderer, Well* well) = 0;
  void set_unit_size(int unit_size) { this->unit_size = unit_size; }

protected:
  static constexpr int TOP_OFFSET = 2;
  int unit_size = 0;
};

#endif //TETRIS_TETRIS_DRAWER_H
