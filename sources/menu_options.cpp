#include "menu_options.h"

MenuOptions::MenuOptions(int xpos, int ypos, int width, int height, std::function<void()> save_options,
                         std::function<void()> close_menu) : Menu(xpos, ypos, width, height),
                                                             save_options(save_options), close_menu(close_menu) {
  options = {"Save", "Cancel"};
}

void MenuOptions::handle_key(EngineWrapper::Key key) {
  Menu::handle_key(key);
  if (key == EngineWrapper::Key::ESCAPE) {
    close_menu();
    selected_index = 0;
  }
}

void MenuOptions::exec_option() {
  switch (selected_index) {
  case 0: {
    unpause->execute();
    break;
  }
  case 1: {
    close_menu();
    break;
  }
  default:break;
  }
  selected_index = 0;
}
