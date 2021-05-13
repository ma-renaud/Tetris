#ifndef TETRIS_TETRISDRAWERRECT_H
#define TETRIS_TETRISDRAWERRECT_H

#include "tetris_renderer.h"
#include <SDL_ttf.h>
#include "texture.h"
#include "SDL_engine.h"
#include "menu_pause.h"
#include "menu_options.h"
#include "title_screen.h"

class TetrisRendererRect : public TetrisRenderer {
public:
  explicit TetrisRendererRect(SDL_engine *engine);
  ~TetrisRendererRect() override = default;

  void clear() override;
  void render() override;
  void draw(Tetromino *tetromino) override;
  void draw(Well *well) override;
  void draw(ScoreLvl *score) override;
  void draw(Bag *bag) override;
  void draw(Tetromino *tetromino, int xpos, int ypos);
  void draw_game_over() override;
  void draw(MenuPause *menu) override;
  void draw(MenuOptions *menu) override;
  void draw(TitleScreen *menu) override;

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
  Texture pause_title;
  Texture options_title;
  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color color);
  void draw_right_zone(int xpos, int ypos, int width, int height);
  int generate_menu_texture(std::vector<Texture> &menu_options, Menu *menu);
  int generate_menu_options(std::vector<Texture> &game_options_textures,
                            std::vector<uint8_t> &game_options_indexes,
                            std::vector<Texture> &displays_textures,
                            const Options::GameOptions &game_options);
  void load_text_texture(Texture &texture, const std::string &text);
};

#endif //TETRIS_TETRISDRAWERRECT_H
