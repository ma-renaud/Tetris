#include <SDL.h>
#include "tetris.h"

int main(int argc, char*argv[]) {
  Tetris game;
  game.init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720 / 2 + 300, 720, false); // NOLINT

  const int FPS = 60;
  const int FRAME_DELAY = 1000 / FPS;
  uint32_t frame_start;
  uint32_t frame_time;

  while (game.running()) {
    frame_start = SDL_GetTicks();

    game.handle_events();
    game.update();
    game.render();

    frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time)
      SDL_Delay(FRAME_DELAY - frame_time);
  }

  game.clean();

  return 0;
}
