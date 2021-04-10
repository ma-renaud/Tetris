#ifndef GAME_H
#define GAME_H

#include <memory>
#include "engine.h"
#include "menu_pause.h"

class Game {
public:
  Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, int fps);
  ~Game() = default;

  void handle_events();
  void handle_keys(EngineWrapper::Key key);
  void update();
  void render();

  bool running() { return is_running; }
  void quit() { is_running = false; }

private:
  int fps = 0;
  int width = 0;
  int height = 0;
  bool is_running;
  std::unique_ptr<EngineWrapper::Engine> engine;
  std::unique_ptr<MenuPause> pause_menu;
  std::unique_ptr<TetrisDrawer> drawer;
};

#endif //GAME_H
