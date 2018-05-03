#include "tetris_drawer_rect.h"

void TetrisDrawerRect::draw(SDL_Renderer *renderer, Tetromino* tetromino) {
  SDL_Rect rect = {tetromino->xpos()*unit_size, tetromino->ypos()*unit_size, unit_size, unit_size};

  for (int i = 0; i < tetromino->matrix_size(); i++) {
    for (int j = 0; j < tetromino->matrix_size(); j++) {
      if(tetromino->is_present(i, j)) {
        rect.x = (tetromino->xpos()+j)*unit_size;
        rect.y = (tetromino->ypos()+i-TOP_OFFSET)*unit_size;
        draw_rect(renderer, &rect, 0, 0, 255, 255);
      }
    }
  }
}

void TetrisDrawerRect::draw(SDL_Renderer *renderer, Well *well) {
  SDL_Rect rect = {0, 0, unit_size, unit_size};

  for (int i = TOP_OFFSET; i < Well::HEIGHT; i++) {
    for (int j = 0; j < Well::WIDTH; j++) {
      if (well->get_tile(i, j) > 0) {
        rect.x = (j) * unit_size;
        rect.y = (i-TOP_OFFSET) * unit_size;
        draw_rect(renderer, &rect, 255, 0, 0, 255);
      }
    }
  }
}

void TetrisDrawerRect::draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a); // the rect color (solid blue)
  SDL_RenderFillRect(renderer, rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect color (solid black)
  SDL_RenderDrawRect(renderer, rect);
}
