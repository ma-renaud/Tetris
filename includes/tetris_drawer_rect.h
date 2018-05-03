#ifndef TETRIS_TETRISDRAWERRECT_H
#define TETRIS_TETRISDRAWERRECT_H

#include "tetris_drawer.h"

class TetrisDrawerRect: public TetrisDrawer{
public:
  TetrisDrawerRect() = default;
  ~TetrisDrawerRect() override = default;

  void draw(SDL_Renderer *renderer, Tetromino* tetromino) override;
  void draw(SDL_Renderer *renderer, Well* well) override;

private:
  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};

#endif //TETRIS_TETRISDRAWERRECT_H
