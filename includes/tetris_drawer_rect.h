#ifndef TETRIS_TETRISDRAWERRECT_H
#define TETRIS_TETRISDRAWERRECT_H

#include "tetris_drawer.h"
#include <SDL_ttf.h>
#include "texture.h"
#include "SDL_engine.h"

class TetrisDrawerRect : public TetrisDrawer {
 public:
  explicit TetrisDrawerRect(SDL_engine *engine, MenuPause *menu);
  ~TetrisDrawerRect() override = default;

  void clear() override;
  void render() override;
  void draw(Tetromino *tetromino) override;
  void draw(Well *well) override;
  void draw(ScoreLvl *score) override;
  void draw(Bag *bag) override;
  void draw(MenuPause *menu) override;
  void draw(Tetromino *tetromino, int xpos, int ypos);
  void draw_game_over() override;

  SDL_Color get_tetromino_color(int tile);

 private:
  static constexpr int unit_size = 26;
  static constexpr SDL_Color textColor = {0, 0, 0, 255};
  TTF_Font *font;
  SDL_Renderer *renderer;
  SDL_engine *engine;
  Texture game_over;
  Texture score_header;
  Texture level_header;
  Texture score;
  Texture level;
  Texture menu_arrow;
  Texture menu_title;
  std::vector<Texture> menu_options;
  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color color);
  void draw_right_zone(int xpos, int ypos, int width, int height);
};

#endif //TETRIS_TETRISDRAWERRECT_H
