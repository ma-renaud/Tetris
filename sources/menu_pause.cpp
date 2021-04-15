#include <menu_pause.h>
#include <algorithm>    // std::min

MenuPause::MenuPause(int xpos, int ypos, int width, int height, MenuCommand* unpause)
    : Menu(xpos, ypos, width, height), unpause(unpause) {
  options = {"Resume", "Restart", "Title Screen", "Exit"};
}

void MenuPause::handle_key(EngineWrapper::Key key) {
  Menu::handle_key(key);
  if (key == EngineWrapper::Key::ESCAPE) {
    unpause.execute();
    selected_index = 0;
  }
}

void MenuPause::exec_option() {
  switch (selected_index) {
  case 0: {
    unpause.execute();
    break;
  }
  case 1: {
    //game->restart();
    break;
  }
  case 2: {
    //game->show_title_screen();
    break;
  }
  case 3: {
    //game->quit();
    break;
  }
  default:break;
  }
  selected_index = 0;
}
