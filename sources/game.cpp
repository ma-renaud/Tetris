#include "game.h"
#include "SDL_engine.h"
#include "tetromino.h"
#include "tetris_drawer_rect.h"

//for testing purpose
#include <iostream>

Game::Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, int fps)
    : fps(fps), width(width), height(height), unpause_command(this) {
  engine = std::make_unique<SDL_engine>();
  is_running = engine->init(title, xpos, ypos, width, height, fullscreen);

  int menu_width = 330;
  int menu_height = 200;
  pause_menu = std::make_unique<MenuPause>((width - menu_width) / 2,
                                           (height - menu_height) / 2 - 75,
                                           menu_width,
                                           menu_height,
                                           &unpause_command);

  title_screen = std::make_unique<TitleScreen>(xpos, ypos, width, height, this);

  drawer = std::make_unique<TetrisDrawerRect>(dynamic_cast<SDL_engine *>(engine.get()));
  tetris = std::make_unique<Tetris>(fps, engine.get());

  menu_stack.push(title_screen.get());
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
    menu_stack.top()->handle_key(key);
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

  if (!menu_stack.empty())
    drawer->draw(menu_stack.top());

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
  menu_stack.push(pause_menu.get());
}

void Game::unpause() {
  menu_stack.pop();
  tetris->unpause();
}

void Game::close_menu() {
  menu_stack.pop();
}

void Game::restart() {
  tetris->restart();
  menu_stack.pop();
}

void Game::show_title_screen() {
  tetris->restart();
  tetris->pause();
  menu_stack.pop();
  menu_stack.push(title_screen.get());
}