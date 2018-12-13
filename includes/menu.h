#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include <SDL_system.h>
#include <string>
#include <SDL_ttf.h>
#include "texture.h"
#include <array>
#include "game.h"

class Menu {
  static constexpr int WIDTH = 300;
  static constexpr int HEIGHT = 200;
  static constexpr int FRAME_THIKCNESS = 5;
  static constexpr SDL_Color FRAME_COLOR = {0, 0, 0, 255};
  static constexpr SDL_Color BACKGROUD_COLOR = {255, 255, 255, 255};

 public:
  Menu(int xpos, int ypos, TTF_Font *font, SDL_Renderer *renderer, Game *game);
  ~Menu() = default;

  static int get_width() { return WIDTH; }
  static int get_height() { return HEIGHT; }
  void handle_keys(SDL_Keycode key);
  void render();

 private:
  int xpos = 0;
  int ypos = 0;
  int selected_index = 0;
  SDL_Rect background;
  SDL_Rect frame;
  TTF_Font *font = nullptr;
  SDL_Renderer *renderer = nullptr;
  Game *game = nullptr;

  Texture arrow;
  Texture title;
  std::array<Texture, 3> options;

  void draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color color);
  void exec_option();

};

#endif //TETRIS_MENU_H
