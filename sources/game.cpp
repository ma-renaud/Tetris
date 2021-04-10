#include "game.h"
#include "SDL_engine.h"
#include "tetris_drawer_rect.h"

Game::Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, int fps)
    : width(width), height(height), fps(fps) {
  engine = std::make_unique<SDL_engine>();
  is_running = engine->init(title, xpos, ypos, width, height, fullscreen);
  drawer = std::make_unique<TetrisDrawerRect>(dynamic_cast<SDL_engine *>(engine.get()), pause_menu.get());

  int menu_width = 300;
  int menu_height = 200;
  pause_menu = std::make_unique<MenuPause>((width - menu_width) / 2,
                                           (height - menu_height) / 2 - 75,
                                           menu_width,
                                           menu_height);
}

void Game::handle_events() {
  EngineWrapper::Event event;
  while (engine->poll_event(event) != 0) {
    switch (event.type) {
    case EngineWrapper::EventType::QUIT: {
      quit();
      break;
    }
    default:break;
    }
  }
}

void Game::handle_keys(EngineWrapper::Key key) {
  std::unique_ptr<Tetromino> copy;
  switch (key) {
  case EngineWrapper::Key::ESCAPE: {
    pause();
  }
  default:break;
  }
}

void Game::update() {
  static int last_level = -1;
  static int delay;
  if (last_level != score.get_level()) {
    last_level = score.get_level();
    delay = get_speed_ms();
  }

  if (!is_game_over && menu_stack.empty() && ((engine->get_ticks() > drop_time))) {
    drop_time += delay;
    check_drop();
  }
}

void Game::render() {
  drawer->clear();

  drawer->draw(&well);
  drawer->draw(tetromino.get());
  drawer->draw(&score);
  drawer->draw(&bag);

  if (!menu_stack.empty())
    drawer->draw(dynamic_cast<MenuPause *>(menu_stack.top()));

  if (is_game_over)
    drawer->draw_game_over();

  drawer->render();
}

void Tetris::clean() {
  engine->clean();
  std::cout << "Tetris Cleaned!" << std::endl;
}