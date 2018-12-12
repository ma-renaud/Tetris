#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include <SDL_system.h>
#include <string>
#include "color.h"
#include <SDL_ttf.h>
#include "texture.h"
#include <array>
#include "game.h"

class Menu {
  static constexpr int WIDTH = 300;
  static constexpr int HEIGHT = 200;
  static constexpr int FRAME_THIKCNESS = 5;
  static const Color FRAME_COLOR;
  static const Color BACKGROUD_COLOR;

 public:
  Menu(int xpos, int ypos, TTF_Font *font, SDL_Renderer *renderer, Game *game);
  ~Menu() = default;

  static int get_width() { return WIDTH; }
  static int get_height() { return HEIGHT; }
  void handle_keys(SDL_Keycode key);
  void render();

 private:
  int xpos;
  int ypos;
  int selected_index = 0;
  SDL_Rect background;
  SDL_Rect frame;
  TTF_Font *font;
  SDL_Renderer *renderer;
  Game *game;

  Texture arrow;
  Texture title;
  std::array<Texture, 3> options;

  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, Color color);
  void exec_option();

};

#endif //TETRIS_MENU_H
