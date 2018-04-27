#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <SDL.h>
#include <iostream>

class Game {
public:
  Game();
  ~Game();

  void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

  void handleEvents();
  void update();
  void render();
  void clean();

  bool running();

private:
  bool is_running;
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif //TETRIS_GAME_H
