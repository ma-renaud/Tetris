#include <iostream>
#include "game.h"

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

  drop_time = SDL_GetTicks();

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

  well = std::make_unique<Well>();
  tetromino = std::make_unique<L>();
  drawer = std::make_unique<TetrisDrawerRect>();
  drawer->set_unit_size(unit_size);
}

void Game::handle_events() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT: {
    is_running = false;
    break;
  }
  case SDL_KEYDOWN: {
    handle_keys(event.key.keysym.sym);
    break;
  }
  case SDL_KEYUP: {
    pressed_key = SDLK_UNKNOWN;
    break;
  }
  default:break;
  }
}

void Game::handle_keys(SDL_Keycode key) {
  std::unique_ptr<Tetromino> copy;
  switch (key) {
  case SDLK_DOWN: {
    copy = tetromino->clone();
    copy->move(0, 1);
    if (!well->is_collision(copy.get()))
      tetromino = std::move(copy);
    break;
  }
  case SDLK_RIGHT: {
    copy = tetromino->clone();
    copy->move(1, 0);
    if (!well->is_collision(copy.get()))
      tetromino = std::move(copy);
    break;
  }
  case SDLK_LEFT: {
    copy = tetromino->clone();
    copy->move(-1, 0);
    if (!well->is_collision(copy.get()))
      tetromino = std::move(copy);
    break;
  }
  case SDLK_UP: {
    if (key != pressed_key) {
      copy = tetromino->clone();
      copy->rotate(Rotation::CCW);
      if (!well->is_collision(copy.get()))
        tetromino = std::move(copy);
    }
    break;
  }
  default:break;
  }
  pressed_key = key;
}

void Game::update() {
  if (SDL_GetTicks() > drop_time) {
    drop_time += 1000;
    check_drop();
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);

  drawer->draw(renderer, well.get());
  drawer->draw(renderer, tetromino.get());

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned!" << std::endl;
}

void Game::check_drop() {
  std::unique_ptr<Tetromino> copy = tetromino->clone();
  copy->move(0, 1);
  if (!well->is_collision(copy.get()))
    tetromino = std::move(copy);
  else {
    well->add_to_well(tetromino.get());
    well->clear_lines();
    tetromino = std::make_unique<L>();
  }
}

bool Game::running() {
  return is_running;
}
