#include <title_screen.h>
#include <algorithm>    // std::min

TitleScreen::TitleScreen(int xpos, int ypos, int width, int height, MenuCommand* unpause, MenuCommand *exit)
    : Menu(xpos, ypos, width, height), unpause(unpause), exit(exit) {
  options = {"Start", "Options", "Exit"};
}

void TitleScreen::exec_option() {
  switch (selected_index) {
  case 0: {
    unpause->execute();
    break;
  }
  case 1: {
    //game->show_options;
    break;
  }
  case 2: {
    exit->execute();
    break;
  }
  default:break;
  }
  selected_index = 0;
}
