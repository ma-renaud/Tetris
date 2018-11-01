#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include <SDL_system.h>
#include <string>
#include "color.h"

class Menu {
  static constexpr int WIDTH = 400;
  static constexpr int HEIGHT = 400;
  static constexpr int FRAME_THIKCNESS = 5;
  static const Color FRAME_COLOR;
  static const Color BACKGROUD_COLOR;

public:
  Menu(int xpos, int ypos);
  ~Menu() = default;

  static int get_width() { return WIDTH; }
  static int get_height() { return HEIGHT; }
  void handle_events();
  void handle_keys(SDL_Keycode key);
  void update();
  void render(SDL_Renderer *renderer);

private:
  SDL_Rect background;
  SDL_Rect frame;

  std::string options[2];

  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, Color color);

};

#endif //TETRIS_MENU_H
