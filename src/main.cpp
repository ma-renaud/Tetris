#include <SDL.h>
#include "game.h"

int main(int /*argc*/, char */*argv*/[]) {
  Game game;
  game.init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720/2, 720, false);

  while(game.running()) {
    game.handleEvents();
    game.update();
    game.render();
  }

  game.clean();

  return 0;
}
