#ifndef TETRIS_INCLUDES_MENU_H
#define TETRIS_INCLUDES_MENU_H

#include <vector>
#include <string>
#include "engine.h"
#include "game.h"

class Menu {
public:
  Menu(int xpos, int ypos, int width, int height, Game *game) : xpos(xpos), ypos(ypos), width(width), height(height), game(game) {}
  virtual ~Menu() = default;

  virtual int get_xpos() = 0;
  virtual int get_ypos() = 0;
  virtual int get_width() = 0;
  virtual int get_height() = 0;
  virtual int get_nb_options() = 0;
  virtual int get_selected_option_index() = 0;
  virtual std::vector<std::string> get_options() = 0;
  virtual void handle_keys(EngineWrapper::Key key) = 0;

protected:
  int xpos = 0;
  int ypos = 0;
  int width = 0;
  int height = 0;
  int selected_index = 0;
  Game *game = nullptr;
};

#endif //TETRIS_INCLUDES_MENU_H
