#ifndef TETRIS_INCLUDES_MENU_H
#define TETRIS_INCLUDES_MENU_H

#include <vector>
#include <string>
#include "engine.h"

class Menu {
public:
  Menu(int width, int height) : width(width), height(height) {}
  virtual ~Menu() = default;

  virtual void render() = 0;
  int get_xpos() const { return xpos; }
  int get_ypos() const { return ypos; }
  void set_xpos(int pos) { xpos = pos; }
  void set_ypos(int pos) { ypos = pos; }
  int get_width() { return width; }
  int get_height() { return height; }
  void set_width(int width) { this->width = width; }
  void set_height(int height) { this->height = height; }
  virtual int get_nb_options() = 0;
  virtual int get_selected_option_index() = 0;
  virtual std::vector<std::string> get_options() = 0;

  virtual void handle_key(EngineWrapper::Key key) {
    static EngineWrapper::Key pressed_key = EngineWrapper::Key::UNKNOWN;
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
      if (key != pressed_key)
        exec_option();
      break;
    }
    default:break;
    }
    pressed_key = key;
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
