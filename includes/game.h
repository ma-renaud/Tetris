#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <memory>
#include "tetromino.h"
#include "well.h"
#include "tetris_drawer_rect.h"

class Game {
public:
  Game() = default;
  ~Game() = default;

  void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

  void handle_events();
  void handle_keys(SDL_Keycode key);
  void update();
  void render();
  void clean();

  bool running();

private:
  static constexpr int unit_size = 26;
  bool is_running = false;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  std::unique_ptr<Tetromino> tetromino;
  std::unique_ptr<Well> well;
  std::unique_ptr<TetrisDrawer> drawer;
};

#endif //TETRIS_GAME_H
