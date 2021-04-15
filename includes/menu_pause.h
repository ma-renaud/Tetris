#ifndef MENU_PAUSE_H
#define MENU_PAUSE_H

#include "engine.h"
#include "menu.h"
#include "menu_command.h"

class MenuPause : public Menu {

public:
  MenuPause(int xpos, int ypos, int width, int height, MenuCommand *unpause);
  ~MenuPause() override = default;

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
  MenuCommand *unpause;

};

#endif //MENU_PAUSE_H
