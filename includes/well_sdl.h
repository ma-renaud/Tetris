#ifndef TETRIS_WELLSDL_H
#define TETRIS_WELLSDL_H

#include <bits/unique_ptr.h>
#include <SDL.h>
#include "well.h"

class WellSDL {
public:
  explicit WellSDL(std::unique_ptr<Well> _well);

  void set_unit_size(int unit_size);
  void draw(SDL_Renderer *renderer);

private:
  static constexpr int TOP_OFFSET = 2;
  std::unique_ptr<Well> well;
  int unit_size = 0;

  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect);
};

#endif //TETRIS_WELLSDL_H
