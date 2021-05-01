#ifndef GAME_H
#define GAME_H

#include <memory>
#include <deque>
#include "tetris.h"
#include "engine.h"
#include "menu_pause.h"
#include "menu_options.h"
#include "tetris_renderer.h"
#include "title_screen.h"
#include "menu_commands.h"
#include "options.h"

class Game {
public:
  Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, int fps);
  ~Game() = default;

  void handle_events();
  void handle_keys(EngineWrapper::Key key);
  void update();
  void render();
  void clean();

  void pause();
  void unpause();
  void close_menu();
  void restart();
  void quit() { is_running = false; }
  void show_title_screen();
  void show_options();
  void save_options();
  bool running() const { return is_running; }

private:
  int fps = 0;
  int width = 0;
  int height = 0;
  bool is_running;
  std::deque<Menu *> menu_stack;
  std::unique_ptr<EngineWrapper::Engine> engine {};
  std::unique_ptr<MenuPause> pause_menu {};
  std::unique_ptr<MenuOptions> options_menu {};
  std::unique_ptr<TitleScreen> title_screen {};
  std::unique_ptr<TetrisRenderer> renderer {};
  std::unique_ptr<Tetris> tetris {};
  MenuCommandUnpause unpause_command;
  MenuCommandRestart restart_command;
  MenuCommandCloseMenu close_menu_command;
  MenuCommandTitleScreen title_screen_command;
  MenuCommandExitGame exit_game_command;
  MenuCommandShowOptions show_options_command;
  MenuCommandSaveOptions save_options_command;
  Options::GameOptions game_options;
};

#endif //GAME_H
