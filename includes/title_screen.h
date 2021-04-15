#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "engine.h"
#include "menu.h"
#include "menu_command.h"

class TitleScreen : public Menu {

public:
  TitleScreen(int xpos, int ypos, int width, int height, MenuCommand* unpause, MenuCommand *exit);
  ~TitleScreen() override = default;

  int get_xpos() override { return xpos; }
  int get_ypos() override { return ypos; }
  int get_width() override { return width; }
  int get_height() override { return height; }
  int get_nb_options() override { return options.size(); }
  int get_selected_option_index() override { return selected_index; }
  std::vector<std::string> get_options() override { return options; }

protected:
  void exec_option() override;

private:
  MenuCommand *unpause;
  MenuCommand *exit;

};

#endif //TITLE_SCREEN_H
