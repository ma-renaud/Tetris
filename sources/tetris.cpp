#include <iostream>
#include <tetris.h>

void Tetris::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

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
      font = TTF_OpenFont("../assets/LVDC_Game_Over.ttf", 16);
      if (font == nullptr) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
      }
    }

    load_text();

    is_running = true;
  } else {
    is_running = false;
  }

  menu = std::make_unique<Menu>((width - Menu::get_width()) / 2,
                                (height - Menu::get_height()) / 2 - 75,
                                font,
                                renderer,
                                this);

  load_a_tetromino();
  drawer = std::make_unique<TetrisDrawerRect>();
  drawer->set_unit_size(unit_size);
}

void Tetris::handle_events() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT: {
      quit();
      break;
    }
    case SDL_KEYDOWN: {
      if (!is_game_over)
        handle_keys(event.key.keysym.sym);
      else {
        restart();
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

void Tetris::handle_keys(SDL_Keycode key) {
  if (is_paused)
    menu->handle_keys(key);
  else {
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
      case SDLK_ESCAPE: {
        pause();
      }
      default:break;
    }
  }
  pressed_key = key;
}

void Tetris::update() {
  if (!is_game_over && !is_paused && ((SDL_GetTicks() > drop_time))) {
    drop_time += 1000;
    check_drop();
  }
}

void Tetris::render() {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);

  drawer->draw(renderer, &well);
  drawer->draw(renderer, tetromino.get());

  if (is_paused)
    menu->render();

  if (is_game_over)
    game_over.render(renderer, (width - game_over.get_width()) / 2, (height - game_over.get_height() - 10));

  SDL_RenderPresent(renderer);
}

void Tetris::clean() {
  //Free global font
  TTF_CloseFont(font);
  font = nullptr;

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Tetris Cleaned!" << std::endl;
}

void Tetris::restart() {
  well.clear();
  tetromino = bag.next();
  drop_time = SDL_GetTicks() + 1000;
  is_game_over = false;
  is_paused = false;
}

bool Tetris::running() {
  return is_running;
}

void Tetris::load_text() {
  if (font != nullptr) {
    //Render game_over
    SDL_Color textColor = {0, 0, 0};
    if (!game_over.loadFromRenderedText(renderer, font, "Game Over!", textColor)) {
      printf("Failed to render game_over texture!\n");
    }
  }
}

void Tetris::check_drop() {
  std::unique_ptr<Tetromino> copy = tetromino->clone();
  copy->move(0, 1);
  if (!well.is_collision(copy.get()))
    tetromino = std::move(copy);
  else {
    well.add_to_well(tetromino.get());
    update_score(well.clear_lines());
    load_a_tetromino();
  }
}

void Tetris::update_score(int nb_lines) {
  if (nb_lines > 0) {
    score += line_points[nb_lines - 1] * (level + 1);
    update_level(nb_lines);
  }
}

void Tetris::update_level(int nb_lines) {
  line_cleared += line_awards[nb_lines-1];
  if(line_cleared >= (level+1)*5){
    line_cleared = 0;
    level++;
  }
}

void Tetris::check_game_over() {
  is_game_over = (tetromino->ypos() == 0);
}

void Tetris::load_a_tetromino() {
  tetromino = bag.next();
  while (!is_game_over && well.is_collision(tetromino.get())) {
    tetromino->move(0, -1);
    check_game_over();
  }
}
