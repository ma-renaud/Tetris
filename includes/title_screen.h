#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "engine.h"
#include "menu.h"
#include "menu_command.h"
#include "tetris_renderer.h"

class TitleScreen : public Menu {

public:
  TitleScreen(int width,
              int height,
              TetrisRenderer *renderer,
              MenuCommand *unpause,
              MenuCommand *show_options,
              MenuCommand *exit);
  ~TitleScreen() override = default;

  void render() override { renderer->draw(this); }
  int get_nb_options() override { return options.size(); }
  int get_selected_option_index() override { return selected_index; }
  std::vector<std::string> get_options() override { return options; }

protected:
  void exec_option() override;

private:
  MenuCommand *unpause;
  MenuCommand *show_options;
  MenuCommand *exit;
  TetrisRenderer *renderer;
};

#endif //TITLE_SCREEN_H
