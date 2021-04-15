#include "menu_commands.h"
#include "game.h"

void MenuCommandUnpause::execute() {
  game->unpause();
}

void MenuCommandRestart::execute() {
  game->restart();
}

void MenuCommandCloseMenu::execute() {
  game->close_menu();
}

void MenuCommandTitleScreen::execute() {
  game->show_title_screen();
}

void MenuCommandExitGame::execute() {
  game->quit();
}
