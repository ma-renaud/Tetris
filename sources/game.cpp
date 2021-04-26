#include "game.h"
#include "SDL_engine.h"
#include "tetromino.h"
#include "tetris_drawer_rect.h"

//for testing purpose
#include <iostream>

Game::Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, int fps)
    : fps(fps), width(width), height(height), unpause_command(this), restart_command(this), close_menu_command(this),
      title_screen_command(this), exit_game_command(this), show_options_command(this), save_options_command(this) {
  engine = std::make_unique<SDL_engine>();
  is_running = engine->init(title, xpos, ypos, width, height, fullscreen);

  int pause_width = 330;
  int pause_height = 200;
  pause_menu = std::make_unique<MenuPause>((width - pause_width) / 2,
                                           (height - pause_height) / 2 - 75,
                                           pause_width,
                                           pause_height,
                                           &unpause_command,
                                           &restart_command,
                                           &title_screen_command,
                                           &exit_game_command);

  int options_width = 430;
  int options_height = 300;
  options_menu = std::make_unique<MenuOptions>((width - options_width) / 2,
                                               (height - options_height) / 2 - 75,
                                               options_width,
                                               options_height,
                                               &save_options_command,
                                               &close_menu_command);

  title_screen = std::make_unique<TitleScreen>(xpos,
                                               ypos,
                                               width,
                                               height,
                                               &unpause_command,
                                               &show_options_command,
                                               &exit_game_command);

  drawer = std::make_unique<TetrisDrawerRect>(dynamic_cast<SDL_engine *>(engine.get()));
  tetris = std::make_unique<Tetris>(fps, engine.get());

  show_title_screen();
}

void Game::handle_events() {
  EngineWrapper::Event event;
  while (engine->poll_event(event) != 0) {
    switch (event.type) {
    case EngineWrapper::EventType::QUIT: {
      quit();
      break;
    }
    case EngineWrapper::EventType::KEYDOWN: {
      if (!tetris->game_over())
        handle_keys(event.key);
      else {
        restart();
      }
      break;
    }
    case EngineWrapper::EventType::KEYUP: {
      handle_keys(EngineWrapper::Key::UNKNOWN);
      break;
    }
    default:break;
    }
  }
}

void Game::handle_keys(EngineWrapper::Key key) {
  if (auto *top = topmost_menu(); top != nullptr)
    top->handle_key(key);
  else if (key == EngineWrapper::Key::ESCAPE)
    pause();
  else
    tetris->handle_keys(key);
}

void Game::update() {
  tetris->update();
}

void Game::render() {
  drawer->clear();

  tetris->render(drawer.get());

  draw_menus();

  if (auto *top = topmost_menu(); top != nullptr)
    drawer->draw(top);

  if (tetris->game_over())
    drawer->draw_game_over();

  drawer->render();
}

void Game::clean() {
  engine->clean();
  std::cout << "Game Cleaned!" << std::endl;
}

void Game::pause() {
  tetris->pause();
  popup_menu(pause_menu.get());
}

void Game::unpause() {
  close_menu();
  tetris->unpause();
}

void Game::popup_menu(Menu *menu) {
  menu_stack.emplace_front(menu);
}

void Game::close_menu() {
  if (!menu_stack.empty())
    menu_stack.pop_front();
}

void Game::close_all_menus() {
  menu_stack.clear();
}

Menu *Game::topmost_menu() const {
  return menu_stack.empty()? nullptr : menu_stack.front();
}

void Game::restart() {
  tetris->restart();
  close_all_menus();
}

void Game::show_title_screen() {
  tetris->restart();
  tetris->pause();
  close_all_menus();
  popup_menu(title_screen.get());
}

void Game::show_options() {
  popup_menu(options_menu.get());
}

void Game::save_options() {
  game_options = options_menu->get_game_options();
}

void Game::draw_menus() {
  for(auto const &menu : menu_stack) {
    drawer->draw(menu);
  }
}
