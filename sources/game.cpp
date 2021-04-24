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

  int menu_width = 330;
  int menu_height = 200;
  pause_menu = std::make_unique<MenuPause>((width - menu_width) / 2,
                                           (height - menu_height) / 2 - 75,
                                           menu_width,
                                           menu_height,
                                           &unpause_command,
                                           &restart_command,
                                           &title_screen_command,
                                           &exit_game_command);

  options_menu = std::make_unique<MenuOptions>((width - menu_width) / 2,
                                               (height - menu_height) / 2 - 75,
                                               menu_width,
                                               menu_height,
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

  menu_stack.emplace_front(title_screen.get());
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
  if (!menu_stack.empty())
    menu_stack.front()->handle_key(key);
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

  for(auto const &menu : menu_stack) {
    drawer->draw(menu);
  }

  if (!menu_stack.empty())
    drawer->draw(menu_stack.front());

  if (tetris->game_over())
    drawer->draw_game_over();

  drawer->render();
}

void Game::clean() {
  engine->clean();
  std::cout << "Tetris Cleaned!" << std::endl;
}

void Game::pause() {
  tetris->pause();
  menu_stack.emplace_front(pause_menu.get());
}

void Game::unpause() {
  menu_stack.pop_front();
  tetris->unpause();
}

void Game::close_menu() {
  menu_stack.pop_front();
}

void Game::restart() {
  tetris->restart();
  if (!menu_stack.empty())
    menu_stack.pop_front();
}

void Game::show_title_screen() {
  tetris->restart();
  tetris->pause();
  menu_stack.pop_front();
  menu_stack.emplace_front(title_screen.get());
}

void Game::show_options() {
  menu_stack.emplace_front(options_menu.get());
}

void Game::save_options() {
  game_options = options_menu->get_game_options();
}
