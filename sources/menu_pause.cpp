#include <menu_pause.h>
#include <algorithm>    // std::min

MenuPause::MenuPause(int xpos,
                     int ypos,
                     int width,
                     int height,
                     MenuCommand *unpause,
                     MenuCommand *restart,
                     MenuCommand *title_screen,
                     MenuCommand *exit)
    : Menu(xpos, ypos, width, height), unpause(unpause), restart(restart), title_screen(title_screen), exit(exit) {
  options = {"Resume", "Restart", "Title Screen", "Exit"};
}

void MenuPause::handle_key(EngineWrapper::Key key) {
  Menu::handle_key(key);
  if (key == EngineWrapper::Key::ESCAPE) {
    unpause->execute();
    selected_index = 0;
  }
}

void MenuPause::exec_option() {
  switch (selected_index) {
  case 0: {
    unpause->execute();
    break;
  }
  case 1: {
    restart->execute();
    break;
  }
  case 2: {
    title_screen->execute();
    break;
  }
  case 3: {
    exit->execute();
    break;
  }
  default:break;
  }
  selected_index = 0;
}
