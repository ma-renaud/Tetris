#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include <functional>
#include "engine.h"
#include "menu.h"
#include "menu_command.h"
#include "options.h"

class MenuOptions : public Menu {

public:
  MenuOptions(int xpos, int ypos, int width, int height, std::function<void()> save_options,
              std::function<void()> close_menu);
  ~MenuOptions() override = default;

  int get_xpos() override { return xpos; }
  int get_ypos() override { return ypos; }
  int get_width() override { return width; }
  int get_height() override { return height; }
  int get_nb_options() override { return options.size(); }
  int get_selected_option_index() override { return selected_index; }
  std::vector<std::string> get_options() override { return options; }
  void handle_key(EngineWrapper::Key key) override;

protected:
  void exec_option() override;

private:
  std::function<void ()> save_options;
  std::function<void ()> close_menu;

};

#endif //MENU_OPTIONS_H
