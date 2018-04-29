#ifndef TETRIS_TETROMINOSDL_H
#define TETRIS_TETROMINOSDL_H

#include <bits/unique_ptr.h>
#include <SDL.h>
#include "tetromino.h"

class TetrominoSDL {
public:
  explicit TetrominoSDL(std::unique_ptr<Tetromino> _tetromino);
  ~TetrominoSDL() = default;

  void set_unit_size(int unit_size);
  void draw(SDL_Renderer *renderer);

private:
  std::unique_ptr<Tetromino> tetromino;
  int unit_size = 0;

  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect);
};

#endif //TETRIS_TETROMINOSDL_H
