#include "game.h"
#include "SDL_engine.h"
#include "tetromino.h"
#include "tetris_renderer_rect.h"

//for testing purpose
#include <iostream>

Game::Game(const char *title, int fps)
    : fps(fps), unpause_command(this), restart_command(this), close_menu_command(this),
      title_screen_command(this), exit_game_command(this), show_options_command(this), save_options_command(this) {
  engine = std::make_unique<SDL_engine>();

  is_running = engine->init(title, 0, 0, width, height, game_options.display_mode == Options::DisplayMode::FULLSCREEN);

  center_game_window();

  renderer = std::make_unique<TetrisRendererRect>(dynamic_cast<SDL_engine *>(engine.get()));

  static int pause_width = 330;
  static int pause_height = 200;
  pause_menu = std::make_unique<MenuPause>(pause_width,
                                           pause_height,
                                           renderer.get(),
                                           &unpause_command,
                                           &restart_command,
                                           &title_screen_command,
                                           &exit_game_command);

  int options_width = 430;
  int options_height = 300;
  options_menu = std::make_unique<MenuOptions>(options_width,
                                               options_height,
                                               engine->get_nb_displays(),
                                               renderer.get(),
                                               &save_options_command,
                                               &close_menu_command);

  title_screen = std::make_unique<TitleScreen>(width,
                                               height,
                                               renderer.get(),
                                               &unpause_command,
                                               &show_options_command,
                                               &exit_game_command);

  tetris = std::make_unique<Tetris>(fps, engine.get());
  update_dimentions_from_options(game_options.resolution);
  update_menus_pos();
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
  renderer->clear();

  tetris->render(renderer.get());

  draw_menus();

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
  popup_menu(pause_menu.get());
}

void Game::unpause() {
  close_menu();
  tetris->unpause();
}

void Game::popup_menu(Menu *menu) {
  menu_stack.emplace_back(menu);
}

void Game::close_menu() {
  menu_stack.pop_back();
}

void Game::close_all_menus() {
  menu_stack.clear();
}

Menu *Game::topmost_menu() const {
  return menu_stack.empty() ? nullptr : menu_stack.back();
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
  options_menu->set_options(game_options);
  popup_menu(options_menu.get());
}

void Game::save_options() {
  Options::GameOptions new_options = options_menu->get_game_options();
  if (game_options.display_mode != new_options.display_mode)
    apply_display_mode(new_options.display_mode);
  if (game_options.resolution != new_options.resolution)
    apply_resolution(new_options.resolution);

  game_options = new_options;
  center_game_window();
}

void Game::draw_menus() {
  for (auto const &menu : menu_stack) {
    menu->render();
  }
}

void Game::apply_display_mode(Options::DisplayMode mode) {
  if (mode == Options::DisplayMode::FULLSCREEN)
    engine->fullscreen_mode();
  else
    engine->window_mode();
}

void Game::apply_resolution(Options::Resolution res) {
  update_dimentions_from_options(res);
  update_menus_pos();
}

void Game::update_menus_pos() {
  pause_menu->set_xpos((width - pause_menu->get_width()) / 2);
  pause_menu->set_ypos((height - pause_menu->get_height()) / 2 - 75);
  options_menu->set_xpos((width - options_menu->get_width()) / 2);
  options_menu->set_ypos((height - options_menu->get_height()) / 2 - 75);
}

void Game::update_dimentions_from_options(Options::Resolution res) {
  auto res_size = Options::get_pair_from_resolution(res);
  engine->set_resolution(res_size.first, res_size.second);
  width = res_size.first;
  height = res_size.second;
  title_screen->set_width(width);
  title_screen->set_height(height);
}

void Game::center_game_window() {
  EngineWrapper::Display current_display = engine->display_info(game_options.selected_display);
  auto res_size = Options::get_pair_from_resolution(game_options.resolution);
  int xpos = current_display.width/2 - res_size.first/2 + current_display.x;
  int ypos = current_display.height/2 - res_size.second/2 + + current_display.y;
  engine->set_window_position(xpos, ypos);
}
