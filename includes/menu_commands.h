#ifndef MENU_COMMANDS_H
#define MENU_COMMANDS_H

#include "menu_command.h"
#include "game.h"

class MenuCommandPause : public MenuCommand {
public :
  explicit MenuCommandPause(Game *game) : game(game) {}
  void execute() override { game->unpause() }

private:
  Game* game;
};

#endif //MENU_COMMANDS_H
