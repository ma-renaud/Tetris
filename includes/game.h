#ifndef GAME_H
#define GAME_H

#include <memory>
#include <stack>
#include "igame.h"
#include "tetris.h"
#include "engine.h"
#include "menu_pause.h"
#include "tetris_drawer.h"
#include "title_screen.h"

class Game : public IGame{
public:
  Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen, int fps);
  ~Game() = default;

  void handle_events();
  void handle_keys(EngineWrapper::Key key);
  void update();
  void render();
  void clean();

  void pause() override;
  void close_menu() override;
  void restart() override;
  void quit() override { is_running = false; }
  void show_title_screen() override;
  bool running() const { return is_running; }

private:
  int fps = 0;
  int width = 0;
  int height = 0;
  bool is_running;
  std::stack<Menu *> menu_stack;
  std::unique_ptr<EngineWrapper::Engine> engine {};
  std::unique_ptr<MenuPause> pause_menu {};
  std::unique_ptr<TitleScreen> title_screen {};
  std::unique_ptr<TetrisDrawer> drawer {};
  std::unique_ptr<Tetris> tetris {};
};

#endif //GAME_H
