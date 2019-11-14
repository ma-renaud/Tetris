#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include "game.h"
#include "engine.h"
#include <string>
#include <vector>

class Menu {

 public:
  Menu(int xpos, int ypos, int width, int height, Game *game);
  ~Menu() = default;

  int get_xpos() { return xpos; }
  int get_ypos() { return ypos; }
  int get_width() { return width; }
  int get_height() { return height; }
  int get_nb_options() { return options.size(); }
  int get_selected_option_index() { return selected_index; }
  std::vector<std::string> get_options() { return options; }
  void handle_keys(EngineWrapper::Key key);

 private:
  int xpos = 0;
  int ypos = 0;
  int width = 0;
  int height = 0;
  int selected_index = 0;
  Game *game = nullptr;

  std::vector<std::string> options = {"Resume", "Restart", "Title Screen", "Exit"};

  void exec_option();

};

#endif //TETRIS_MENU_H
