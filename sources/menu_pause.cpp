#include <menu_pause.h>
#include <algorithm>    // std::min
#include "igame.h"

MenuPause::MenuPause(int xpos, int ypos, int width, int height, IGame* game)
    : Menu(xpos, ypos, width, height), game(game) {
  options = {"Resume", "Restart", "Title Screen", "Exit"};
}

void MenuPause::handle_key(EngineWrapper::Key key) {
  Menu::handle_key(key);
  if (key == EngineWrapper::Key::ESCAPE) {
    game->close_menu();
    selected_index = 0;
  }
}

void MenuPause::exec_option() {
  switch (selected_index) {
  case 0: {
    game->close_menu();
    break;
  }
  case 1: {
    game->restart();
    break;
  }
  case 2: {
    game->show_title_screen();
    break;
  }
  case 3: {
    game->quit();
    break;
  }
  default:break;
  }
  selected_index = 0;
}
