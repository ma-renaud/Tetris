#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include "game.h"
#include "engine.h"
#include "menu.h"

class MenuPause : public Menu {

 public:
  MenuPause(int xpos, int ypos, int width, int height, Game *game);
  ~MenuPause() override = default;

  int get_xpos() override { return xpos; }
  int get_ypos() override { return ypos; }
  int get_width() override { return width; }
  int get_height() override { return height; }
  int get_nb_options() override { return options.size(); }
  int get_selected_option_index() override { return selected_index; }
  std::vector<std::string> get_options() override { return options; }
  void handle_keys(EngineWrapper::Key key) override;

 private:
  std::vector<std::string> options = {"Resume", "Restart", "Title Screen", "Exit"};
  void exec_option();

};

#endif //TETRIS_MENU_H
