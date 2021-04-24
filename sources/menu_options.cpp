#include "menu_options.h"

MenuOptions::MenuOptions(int xpos, int ypos, int width, int height, MenuCommand *save_options,
                         MenuCommand *close_menu) : Menu(xpos, ypos, width, height),
                                                    save_options(save_options), close_menu(close_menu) {
  options = {"Save", "Cancel"};
}

void MenuOptions::handle_key(EngineWrapper::Key key) {
  Menu::handle_key(key);
  if (key == EngineWrapper::Key::ESCAPE) {
    close_menu->execute();
    selected_index = 0;
  }
}

void MenuOptions::exec_option() {
  switch (selected_index) {
  case 0: {
    save_options->execute();
    break;
  }
  case 1: {
    close_menu->execute();
    break;
  }
  default:break;
  }
  selected_index = 0;
}
