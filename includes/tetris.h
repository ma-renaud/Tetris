#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "SDLEngine.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <memory>
#include "tetromino.h"
#include "well.h"
#include "tetris_drawer_rect.h"
#include "bag.h"
#include "texture.h"
#include "menu.h"
#include "game.h"
#include "score_lvl.h"

class Tetris : public Game {
 public:
  Tetris() = default;
  ~Tetris() = default;

  void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, int fps);

  void handle_events();
  void handle_keys(EngineWrapper::Key key);
  void update();
  void render();
  void clean();
  void pause() override { is_paused = true; }
  void unpause() override {
    is_paused = false;
    drop_time = SDL_GetTicks() + 500;
  }
  void quit() override { is_running = false; }
  void restart() override;

  bool running();

 private:
  int fps = 0;
  int width = 0;
  int height = 0;
  bool is_running = false;
  bool is_game_over = false;
  bool is_paused = false;
  static constexpr int unit_size = 26;
  uint32_t drop_time = 0;
  EngineWrapper::Key pressed_key = EngineWrapper::Key::UNKNOWN;
  std::unique_ptr<Tetromino> tetromino;
  std::unique_ptr<TetrisDrawer> drawer;
  std::unique_ptr<Menu> menu;
  Well well;
  Bag bag;
  Texture game_over;
  ScoreLvl score;
  std::unique_ptr<EngineWrapper::Engine> engine;

  static constexpr int frame_per_row[ScoreLvl::MAX_SPEED_LEVEL] = {53,49,45,41,37,33,28,22,17,11,10,9,8,7,6,6,5,5,4,4,3,3,2,2,1};

  void load_text();
  void check_drop();
  void check_game_over();
  void load_a_tetromino();
  int get_speed_ms();
};

#endif //TETRIS_GAME_H
