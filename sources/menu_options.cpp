#include "menu_options.h"

MenuOptions::MenuOptions(int width, int height, int nb_displays, TetrisRenderer *renderer, MenuCommand *save_options,
                         MenuCommand *close_menu) : Menu(width, height), nb_displays(nb_displays),
                                                    save_options(save_options), close_menu(close_menu),
                                                    renderer(renderer) {
  options = {"Save", "Cancel"};
  nb_index = game_options.nb_options + options.size();
}

void MenuOptions::handle_key(EngineWrapper::Key key) {
  switch (key) {
  case EngineWrapper::Key::DOWN: {
    if (!options.empty())
      selected_index = std::min(selected_index + 1, (static_cast<int>(nb_index) - 1));
    break;
  }
  case EngineWrapper::Key::UP: {
    if (!options.empty())
      selected_index = std::max(selected_index - 1, 0);
    break;
  }
  case EngineWrapper::Key::RETURN: {
    exec_option();
    break;
  }
  case EngineWrapper::Key::LEFT: {
    previous();
    break;
  }
  case EngineWrapper::Key::RIGHT: {
    next();
    break;
  }
  case EngineWrapper::Key::ESCAPE: {
    close_menu->execute();
    selected_index = 0;
    break;
  }
  default:break;
  }
}

void MenuOptions::exec_option() {
  switch (selected_index - game_options.nb_options) {
  case 0: {
    selected_index = 0;
    save_options->execute();
    close_menu->execute();
    break;
  }
  case 1: {
    selected_index = 0;
    close_menu->execute();
    break;
  }
  default:break;
  }
}

void MenuOptions::next() {
  switch (selected_index) {
  case 0:game_options.display_mode++;
    break;
  case 1:game_options.resolution++;
    break;
  case 2:game_options.selected_display = std::min(game_options.selected_display + 1, nb_displays - 1);
    break;
  case 3:
    if (!options.empty())
      selected_index = std::min(selected_index + 1, (static_cast<int>(nb_index) - 1));
    break;
  case 4:
    if (!options.empty())
      selected_index = std::max(selected_index - 1, 0);
    break;
  }
}

void MenuOptions::previous() {
  switch (selected_index) {
  case 0:game_options.display_mode--;
    break;
  case 1:game_options.resolution--;
    break;
  case 2:game_options.selected_display = std::max(game_options.selected_display - 1, 0);
    break;
  case 3:selected_index = std::min(selected_index + 1, (static_cast<int>(nb_index) - 1));
    break;
  case 4:selected_index = std::max(selected_index - 1, 0);
    break;
  }
}
