#include <iostream>
#include "game.h"

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

  drop_time = SDL_GetTicks();

  this->width = width;
  this->height = height;

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

    if (TTF_Init() == -1) {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
      font = TTF_OpenFont("LVDC_Game_Over.ttf", 16);
      if (font == nullptr) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
      }
    }

    load_text();

    is_running = true;
  } else {
    is_running = false;
  }

  menu = std::make_unique<Menu>((width - Menu::get_width()) / 2, (height - Menu::get_height()) / 2 - 75);

  load_a_tetromino();
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
    if (!is_game_over)
      handle_keys(event.key.keysym.sym);
    else {
      well.clear();
      tetromino = bag.next();
      drop_time += 1000;
      is_game_over = false;
    }
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
    if (!well.is_collision(copy.get()))
      tetromino = std::move(copy);
    break;
  }
  case SDLK_RIGHT: {
    copy = tetromino->clone();
    copy->move(1, 0);
    if (!well.is_collision(copy.get()))
      tetromino = std::move(copy);
    break;
  }
  case SDLK_LEFT: {
    copy = tetromino->clone();
    copy->move(-1, 0);
    if (!well.is_collision(copy.get()))
      tetromino = std::move(copy);
    break;
  }
  case SDLK_UP: {
    if (key != pressed_key) {
      copy = tetromino->clone();
      copy->rotate(Rotation::CCW);
      if (!well.is_collision(copy.get()))
        tetromino = std::move(copy);
    }
    break;
  }
  default:break;
  }
  pressed_key = key;
}

void Game::update() {
//  if (!is_game_over and ((SDL_GetTicks() > drop_time))) {
//    drop_time += 1000;
//    check_drop();
//  }
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);

  drawer->draw(renderer, &well);
  drawer->draw(renderer, tetromino.get());

  menu->render(renderer);

  if (is_game_over)
    game_over.render(renderer, (width - game_over.get_width()) / 2, (height - game_over.get_height() - 10));

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  //Free global font
  TTF_CloseFont(font);
  font = nullptr;

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned!" << std::endl;
}

bool Game::running() {
  return is_running;
}

void Game::load_text() {
  if (font != nullptr) {
    //Render game_over
    SDL_Color textColor = {0, 0, 0};
    if (!game_over.loadFromRenderedText(renderer, font, "Game Over!", textColor)) {
      printf("Failed to render game_over texture!\n");
    }
  }
}

void Game::check_drop() {
  std::unique_ptr<Tetromino> copy = tetromino->clone();
  copy->move(0, 1);
  if (!well.is_collision(copy.get()))
    tetromino = std::move(copy);
  else {
    well.add_to_well(tetromino.get());
    well.clear_lines();
    load_a_tetromino();
  }
}

void Game::check_game_over() {
  is_game_over = (tetromino->ypos() == 0);
}

void Game::load_a_tetromino() {
  tetromino = bag.next();
  while (!is_game_over and well.is_collision(tetromino.get())) {
    tetromino->move(0, -1);
    check_game_over();
  }
}
