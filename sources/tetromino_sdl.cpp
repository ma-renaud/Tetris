#include "tetromino_sdl.h"

TetrominoSDL::TetrominoSDL(std::unique_ptr<Tetromino> _tetromino) : tetromino(std::move(_tetromino)) {

}

void TetrominoSDL::set_unit_size(int unit_size) {
  this->unit_size = unit_size;
}

void TetrominoSDL::draw(SDL_Renderer *renderer) {
  SDL_Rect rect = {tetromino->xpos()*unit_size, tetromino->ypos()*unit_size, unit_size, unit_size};



  for (int i = 0; i < tetromino->matrix_size(); i++) {
    for (int j = 0; j < tetromino->matrix_size(); j++) {
      if(tetromino->is_present(i, j)) {
        rect.x = (tetromino->xpos()+j)*unit_size;
        rect.y = (tetromino->ypos()+i)*unit_size;
        draw_rect(renderer, &rect);
      }
    }
  }
}

void TetrominoSDL::draw_rect(SDL_Renderer *renderer, SDL_Rect *rect) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // the rect color (solid blue)
  SDL_RenderFillRect(renderer, rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect color (solid black)
  SDL_RenderDrawRect(renderer, rect);
}
