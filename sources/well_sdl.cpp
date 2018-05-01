#include <bits/unique_ptr.h>
#include "well_sdl.h"

WellSDL::WellSDL(std::unique_ptr<Well> _well) : well(std::move(_well)) {

}

void WellSDL::set_unit_size(int unit_size) {
  this->unit_size = unit_size;
}

void WellSDL::draw(SDL_Renderer *renderer) {
  SDL_Rect rect = {0, 0, unit_size, unit_size};

  for (int i = TOP_OFFSET; i < well->HEIGHT; i++) {
    for (int j = 0; j < well->WIDTH; j++) {
      if (well->get_tile(i, j) > 0) {
        rect.x = (j) * unit_size;
        rect.y = (i-TOP_OFFSET) * unit_size;
        draw_rect(renderer, &rect);
      }
    }
  }
}

void WellSDL::draw_rect(SDL_Renderer *renderer, SDL_Rect *rect) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // the rect color (solid red)
  SDL_RenderFillRect(renderer, rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect color (solid black)
  SDL_RenderDrawRect(renderer, rect);
}
