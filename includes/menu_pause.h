#ifndef MENU_PAUSE_H
#define MENU_PAUSE_H

#include "engine.h"
#include "menu.h"
#include "menu_command.h"
#include "tetris_renderer.h"

class MenuPause : public Menu {

public:
  MenuPause(int width, int height, TetrisRenderer *renderer, MenuCommand *unpause,
            MenuCommand *restart,
            MenuCommand *title_screen,
            MenuCommand *exit);
  ~MenuPause() override = default;

  void render() override { renderer->draw(this); }
  int get_nb_options() override { return options.size(); }
  int get_selected_option_index() override { return selected_index; }
  std::vector<std::string> get_options() override { return options; }
  void handle_key(EngineWrapper::Key key) override;

protected:
  void exec_option() override;

private:
  MenuCommand *unpause;
  MenuCommand *restart;
  MenuCommand *title_screen;
  MenuCommand *exit;
  TetrisRenderer *renderer;
};

#endif //MENU_PAUSE_H
