#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include "game.h"
#include "engine.h"

class Menu {
  static constexpr int NB_OPTIONS = 3;

 public:
  Menu(int xpos, int ypos, int width, int height, Game *game);
  ~Menu() = default;

  int get_xpos() { return xpos; }
  int get_ypos() { return ypos; }
  int get_width() { return width; }
  int get_height() { return height; }
  int get_selected_option_index() { return selected_index; }
  void handle_keys(EngineWrapper::Key key);

 private:
  int xpos = 0;
  int ypos = 0;
  int width = 0;
  int height = 0;
  int selected_index = 0;
  Game *game = nullptr;

  void exec_option();

};

#endif //TETRIS_MENU_H
