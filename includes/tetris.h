#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "engine.h"
#include <memory>
#include "tetromino.h"
#include "well.h"
#include "bag.h"
#include "texture.h"
#include "menu_pause.h"
#include "score_lvl.h"
#include "tetris_drawer.h"

class Tetris {
public:
  Tetris(int fps, EngineWrapper::Engine *engine);
  ~Tetris() = default;

  void handle_keys(EngineWrapper::Key key);
  void update();
  void render(TetrisDrawer *drawer);
  void restart();
  void pause() { is_pause = true; }
  void unpause() { is_pause = false; drop_time = SDL_GetTicks() + 500; }

  bool game_over() { return is_game_over; }

private:
  int fps = 0;
  bool is_game_over = false;
  bool is_pause = true;
  uint32_t drop_time = 0;
  std::unique_ptr<Tetromino> tetromino;

  Well well;
  Bag bag;
  ScoreLvl score;
  EngineWrapper::Engine *engine;

  static constexpr int frame_per_row[ScoreLvl::MAX_SPEED_LEVEL] =
      {53, 49, 45, 41, 37, 33, 28, 22, 17, 11, 10, 9, 8, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1};

  void check_drop();
  void check_game_over();
  void load_a_tetromino();
  int get_speed_ms();
};

#endif //TETRIS_GAME_H
