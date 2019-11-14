#include <menu.h>
#include <algorithm>    // std::min

Menu::Menu(int xpos, int ypos, int width, int height, Game *game)
    : xpos(xpos), ypos(ypos), width(width), height(height), game(game) {}

void Menu::handle_keys(EngineWrapper::Key key) {
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

void Menu::exec_option() {
  switch (selected_index) {
    case 0: {
      game->unpause();
      break;
    }
    case 1: {
      game->restart();
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
