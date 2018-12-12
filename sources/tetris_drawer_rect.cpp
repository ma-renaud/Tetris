
#include <tetris_drawer_rect.h>

#include "tetris_drawer_rect.h"

void TetrisDrawerRect::draw(SDL_Renderer *renderer, Tetromino* tetromino) {
  SDL_Rect rect = {tetromino->xpos()*unit_size, tetromino->ypos()*unit_size, unit_size, unit_size};

  for (int i = 0; i < tetromino->matrix_size(); i++) {
    for (int j = 0; j < tetromino->matrix_size(); j++) {
      if(tetromino->is_present(i, j)) {
        rect.x = (tetromino->xpos()+j)*unit_size;
        rect.y = (tetromino->ypos()+i-TOP_OFFSET)*unit_size;
        draw_rect(renderer, &rect,get_tetromino_color(tetromino->get_tile(i, j)));
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
        draw_rect(renderer, &rect, get_tetromino_color(well->get_tile(i, j)));
      }
    }
  }
}

void TetrisDrawerRect::draw(SDL_Renderer *renderer, ScoreLvl *score) {

}

Color TetrisDrawerRect::get_tetromino_color(int tile) {
  switch (tile) {
  case 1:
  case 2:
  case 3        :return {49, 199, 239};
  case 4        :return {247, 211, 8};
  case 5        :return {173, 77, 156};
  case 6        :return {66, 182, 66};
  case 7        :return {239, 32, 41};
  case 8        :return {90, 101, 173};
  case 9        :return {239, 121, 33};
  case 42       :return {127, 64, 20};
  default       :return {255, 255, 255, 0};
  }
}

void TetrisDrawerRect::draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, Color color) {
  SDL_SetRenderDrawColor(renderer, color.red(), color.green(), color.blue(), color.alpha());
  SDL_RenderFillRect(renderer, rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect border color (solid black)
  SDL_RenderDrawRect(renderer, rect);
}
