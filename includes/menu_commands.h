#ifndef MENU_COMMANDS_H
#define MENU_COMMANDS_H

#include "menu_command.h"

class Game;

class MenuCommandUnpause : public MenuCommand {
public :
  explicit MenuCommandUnpause(Game* game) : game(game) {}
  void execute() override;

private:
  Game* game;
};

class MenuCommandRestart : public MenuCommand {
public :
  explicit MenuCommandRestart(Game* game) : game(game) {}
  void execute() override;

private:
  Game* game;
};

class MenuCommandCloseMenu : public MenuCommand {
public :
  explicit MenuCommandCloseMenu(Game* game) : game(game) {}
  void execute() override;

private:
  Game* game;
};

class MenuCommandTitleScreen : public MenuCommand {
public :
  explicit MenuCommandTitleScreen(Game* game) : game(game) {}
  void execute() override;

private:
  Game* game;
};

class MenuCommandExitGame : public MenuCommand {
public :
  explicit MenuCommandExitGame(Game* game) : game(game) {}
  void execute() override;

private:
  Game* game;
};

class MenuCommandShowOptions : public MenuCommand {
public :
  explicit MenuCommandShowOptions(Game* game) : game(game) {}
  void execute() override;

private:
  Game* game;
};

class MenuCommandSaveOptions : public MenuCommand {
public :
  explicit MenuCommandSaveOptions(Game* game) : game(game) {}
  void execute() override;

private:
  Game* game;
};

#endif //MENU_COMMANDS_H
