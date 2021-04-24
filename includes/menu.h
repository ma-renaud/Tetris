#ifndef TETRIS_INCLUDES_MENU_H
#define TETRIS_INCLUDES_MENU_H

#include <vector>
#include <string>
#include "engine.h"

class Menu {
public:
  Menu(int xpos, int ypos, int width, int height) : xpos(xpos), ypos(ypos), width(width), height(height) {}
  virtual ~Menu() = default;

  virtual int get_xpos() = 0;
  virtual int get_ypos() = 0;
  virtual int get_width() = 0;
  virtual int get_height() = 0;
  virtual int get_nb_options() = 0;
  virtual int get_selected_option_index() = 0;
  virtual std::vector<std::string> get_options() = 0;

  virtual void handle_key(EngineWrapper::Key key) {
    switch (key) {
    case EngineWrapper::Key::DOWN: {
      if (!options.empty())
        selected_index = std::min(selected_index + 1, (static_cast<int>(options.size()) - 1));
      break;
    }
    case EngineWrapper::Key::UP: {
      if (!options.empty())
        selected_index = std::max(selected_index - 1, 0);
      break;
    }
    case EngineWrapper::Key::RETURN: {
      exec_option();
      break;
    }
    default:break;
    }
  }

protected:
  int xpos = 0;
  int ypos = 0;
  int width = 0;
  int height = 0;
  int selected_index = 0;
  std::vector<std::string> options{};

  virtual void exec_option() = 0;
};

#endif //TETRIS_INCLUDES_MENU_H
