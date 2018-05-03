#include <SDL.h>
#include "game.h"

int main(int /*argc*/, char */*argv*/[]) {
  Game game;
  game.init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720/2, 720, false); // NOLINT

  while(game.running()) {
    game.handle_events();
    game.update();
    game.render();
  }

  game.clean();

  return 0;
}
