#ifndef TETRIS_TETRISDRAWERRECT_H
#define TETRIS_TETRISDRAWERRECT_H

#include "tetris_drawer.h"
#include "color.h"

class TetrisDrawerRect: public TetrisDrawer{
public:
  TetrisDrawerRect() = default;
  ~TetrisDrawerRect() override = default;

  void draw(SDL_Renderer *renderer, Tetromino* tetromino) override;
  void draw(SDL_Renderer *renderer, Well* well) override;
  void draw(SDL_Renderer *renderer, ScoreLvl* score) override;

  Color get_tetromino_color(int tile);

private:
  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, Color color);
};

#endif //TETRIS_TETRISDRAWERRECT_H
