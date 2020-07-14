#include <menu_pause.h>
#include <algorithm>    // std::min

MenuPause::MenuPause(int xpos, int ypos, int width, int height, Game *game)
    : Menu(xpos, ypos, width, height, game) {}

void MenuPause::handle_keys(EngineWrapper::Key key) {
  switch (key) {
  case EngineWrapper::Key::DOWN: {
    selected_index = std::min(selected_index + 1, (static_cast<int>(options.size()) - 1));
    break;
  }
  case EngineWrapper::Key::UP: {
    selected_index = std::max(selected_index - 1, 0);
    break;
  }
  case EngineWrapper::Key::RETURN: {
    exec_option();
    break;
  }
  case EngineWrapper::Key::ESCAPE: {
    game->unpause();
    selected_index = 0;
    break;
  }
  default:break;
  }
}

void MenuPause::exec_option() {
  switch (selected_index) {
  case 0: {
    game->unpause();
    break;
  }
  case 1: {
    game->restart();
    break;
  }
  case 2: {
    game->title_screen();
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
