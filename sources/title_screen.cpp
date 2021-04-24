#include <title_screen.h>
#include <algorithm>    // std::min

TitleScreen::TitleScreen(int xpos,
                         int ypos,
                         int width,
                         int height,
                         MenuCommand *unpause,
                         MenuCommand *show_options,
                         MenuCommand *exit)
    : Menu(xpos, ypos, width, height), unpause(unpause), show_options(show_options), exit(exit) {
  options = {"Start", "Options", "Exit"};
}

void TitleScreen::exec_option() {
  switch (selected_index) {
  case 0: {
    unpause->execute();
    break;
  }
  case 1: {
    show_options->execute();
    break;
  }
  case 2: {
    exit->execute();
    break;
  }
  default:break;
  }
}
