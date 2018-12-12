#ifndef TETRIS_TETRISDRAWERRECT_H
#define TETRIS_TETRISDRAWERRECT_H

#include "tetris_drawer.h"
#include "color.h"
#include <SDL_ttf.h>
#include "texture.h"

class TetrisDrawerRect : public TetrisDrawer {
 public:
  TetrisDrawerRect(TTF_Font *font, SDL_Renderer *renderer);
  ~TetrisDrawerRect() override = default;

  void draw(Tetromino *tetromino) override;
  void draw(Well *well) override;
  void draw(ScoreLvl *score) override;

  Color get_tetromino_color(int tile);

 private:
  static constexpr SDL_Color textColor = {0, 0, 0};
  TTF_Font *font;
  SDL_Renderer *renderer;
  Texture score_header;
  Texture level_header;
  Texture score;
  Texture level;
  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, Color color);
};

#endif //TETRIS_TETRISDRAWERRECT_H
