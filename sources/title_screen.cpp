#include <title_screen.h>
#include <algorithm>    // std::min
#include "igame.h"

TitleScreen::TitleScreen(int xpos, int ypos, int width, int height, IGame* game)
    : Menu(xpos, ypos, width, height), game(game) {
  options = {"Start", "Options", "Exit"};
}

void TitleScreen::exec_option() {
  switch (selected_index) {
  case 0: {
    game->close_menu();
    break;
  }
  case 1: {
    //game->show_options;
    break;
  }
  case 2: {
    game->quit();
    break;
  }
  default:break;
  }
  selected_index = 0;
}
