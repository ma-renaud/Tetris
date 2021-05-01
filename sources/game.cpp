#include "game.h"
#include "SDL_engine.h"
#include "tetromino.h"
#include "tetris_renderer_rect.h"

//for testing purpose
#include <iostream>

Game::Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, int fps)
    : fps(fps), width(width), height(height), unpause_command(this), restart_command(this), close_menu_command(this),
      title_screen_command(this), exit_game_command(this), show_options_command(this), save_options_command(this) {
  engine = std::make_unique<SDL_engine>();
  is_running = engine->init(title, xpos, ypos, width, height, fullscreen);

  renderer = std::make_unique<TetrisRendererRect>(dynamic_cast<SDL_engine *>(engine.get()));

  int pause_width = 330;
  int pause_height = 200;
  pause_menu = std::make_unique<MenuPause>((width - pause_width) / 2,
                                           (height - pause_height) / 2 - 75,
                                           pause_width,
                                           pause_height,
                                           renderer.get(),
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
                                               renderer.get(),
                                               &save_options_command,
                                               &close_menu_command);

  title_screen = std::make_unique<TitleScreen>(xpos,
                                               ypos,
                                               width,
                                               height,
                                               renderer.get(),
                                               &unpause_command,
                                               &show_options_command,
                                               &exit_game_command);

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
  renderer->clear();

  tetris->render(renderer.get());

  for(auto const &menu : menu_stack) {
    menu->render();
  }

  if (!menu_stack.empty())
    menu_stack.front()->render();

  if (tetris->game_over())
    renderer->draw_game_over();

  renderer->render();
}

void Game::clean() {
  engine->clean();
  std::cout << "Game Cleaned!" << std::endl;
}

void Game::pause() {
  tetris->pause();
  menu_stack.emplace_front(pause_menu.get());
}

void Game::unpause() {
  close_menu();
  tetris->unpause();
}

void Game::close_menu() {
  if (!menu_stack.empty())
    menu_stack.pop_front();
}

void Game::restart() {
  tetris->restart();
  close_menu(); //close pause menu
}

void Game::show_title_screen() {
  tetris->restart();
  tetris->pause();
  close_menu(); //close pause menu
  menu_stack.emplace_front(title_screen.get());
}

void Game::show_options() {
  menu_stack.emplace_front(options_menu.get());
}

void Game::save_options() {
  game_options = options_menu->get_game_options();
}
