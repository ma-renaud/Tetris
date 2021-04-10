#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "engine.h"
#include <memory>
#include <stack>
#include "tetromino.h"
#include "well.h"
#include "bag.h"
#include "texture.h"
#include "menu_pause.h"
#include "game.h"
#include "score_lvl.h"

class Tetris {
 public:
  Tetris(int xpos, int ypos, int width, int height);
  ~Tetris() = default;

  void handle_events();
  void handle_keys(EngineWrapper::Key key);
  void update();
  void render();
  void clean();
  void pause();
  void unpause();
  void restart();
  void title_screen();

  bool running();

 private:
  int width = 0;
  int height = 0;
  bool is_running = false;
  bool is_game_over = false;
  uint32_t drop_time = 0;
  EngineWrapper::Key pressed_key = EngineWrapper::Key::UNKNOWN;
  std::unique_ptr<Tetromino> tetromino;
  std::unique_ptr<TetrisDrawer> drawer;
  std::unique_ptr<MenuPause> pause_menu;
  std::stack<Menu *> menu_stack;
  Well well;
  Bag bag;
  ScoreLvl score;
  std::unique_ptr<EngineWrapper::Engine> engine;

  static constexpr int frame_per_row[ScoreLvl::MAX_SPEED_LEVEL] = {53,49,45,41,37,33,28,22,17,11,10,9,8,7,6,6,5,5,4,4,3,3,2,2,1};

  void check_drop();
  void check_game_over();
  void load_a_tetromino();
  int get_speed_ms();
};

#endif //TETRIS_GAME_H
