#include <iostream>
#include "game.h"

int unit_size = 26;
SDL_Rect wellRect = {unit_size, unit_size*2, unit_size*10, unit_size*22};


void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

  Uint32 flags = 0;
  if (fullscreen)
    flags = SDL_WINDOW_FULLSCREEN;

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystems Initialised!..." << std::endl;
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window)
      std::cout << "Window created!" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
      std::cout << "Renderer created!" << std::endl;
    }

    is_running = true;
  } else {
    is_running = false;
  }

  tetromino = std::make_unique<TetrominoSDL>(std::make_unique<L>());
  tetromino->set_unit_size(unit_size);

  well = std::make_unique<Well>();
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:is_running = false;
    break;
  default:break;
  }
}

void Game::update() {

}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // the rect color (solid blue)
  SDL_RenderDrawRect(renderer, &wellRect);

  tetromino->draw(renderer);

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned!" << std::endl;
}

bool Game::running() {
  return is_running;
}
