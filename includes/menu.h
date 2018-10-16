#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include <SDL_system.h>

class Menu {
public:
  Menu(int width, int height);
  ~Menu() = default;

  void show_menu();

private:
  SDL_Rect background;
  SDL_Rect frame;

};

#endif //TETRIS_MENU_H
