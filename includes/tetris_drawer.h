#ifndef TETRIS_TETRIS_DRAWER_H
#define TETRIS_TETRIS_DRAWER_H

#include <SDL_system.h>
#include "well.h"
#include "tetromino.h"
#include "score_lvl.h"
#include "bag.h"
#include "title_screen.h"

class TetrisDrawer {
 public:
  TetrisDrawer() = default;
  virtual ~TetrisDrawer() = default;

  virtual void clear() = 0;
  virtual void render() = 0;
  virtual void draw(Tetromino *tetromino) = 0;
  virtual void draw(Well *well) = 0;
  virtual void draw(ScoreLvl *score) = 0;
  virtual void draw(Bag *bag) = 0;
  virtual void draw_game_over() = 0;
  virtual void draw(Menu *menu) = 0;

 protected:
  static constexpr int TOP_OFFSET = 2;
};

#endif //TETRIS_TETRIS_DRAWER_H
