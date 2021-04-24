#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include <functional>
#include "engine.h"
#include "menu.h"
#include "menu_command.h"
#include "options.h"

class MenuOptions : public Menu {

public:
  MenuOptions(int xpos, int ypos, int width, int height, MenuCommand *save_options,
              MenuCommand *close_menu);
  ~MenuOptions() override = default;

  int get_xpos() override { return xpos; }
  int get_ypos() override { return ypos; }
  int get_width() override { return width; }
  int get_height() override { return height; }
  int get_nb_options() override { return options.size(); }
  int get_selected_option_index() override { return selected_index; }
  std::vector<std::string> get_options() override { return options; }
  void handle_key(EngineWrapper::Key key) override;
  void set_options(Options::GameOptions options) { game_options = options; }
  Options::GameOptions get_game_options() { return game_options; }

protected:
  void exec_option() override;

private:
  int nb_index = 0;
  MenuCommand *save_options;
  MenuCommand *close_menu;
  Options::GameOptions game_options;
  void next();
  void previous();

};

#endif //MENU_OPTIONS_H
