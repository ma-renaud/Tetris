#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "tetromino_sdl.h"

class Game {
public:
  Game() = default;
  ~Game() = default;

  void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

  void handleEvents();
  void update();
  void render();
  void clean();

  bool running();

private:
  bool is_running = false;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  std::unique_ptr<TetrominoSDL> tetromino;
};

#endif //TETRIS_GAME_H
