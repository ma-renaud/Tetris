#ifndef TETRIS_SDLENGINE_H
#define TETRIS_SDLENGINE_H

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "engine.h"

class SDL_engine : public EngineWrapper::Engine {
public:
  SDL_engine();
  ~SDL_engine() override = default;

  bool init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) override;
  int poll_event(EngineWrapper::Event &event) override;
  void clean() override;
  uint32_t get_ticks() override;
  void fullscreen_mode() override;
  void window_mode() override;
  void set_resolution(int width, int height) override;
  void set_window_position(int x, int y) override;
  int get_nb_displays() override { return static_cast<int>(displayBounds.size()); }
  EngineWrapper::Display display_info(uint8_t display) override;

  SDL_Renderer *get_renderer() { return renderer; }
  TTF_Font *get_font() { return font; }
  int get_window_width() const { return width; }
  int get_window_height() const { return height; }

private:
  int width = 0;
  int height = 0;
  bool initialized = false;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  TTF_Font *font = nullptr;
  std::vector<SDL_Rect> displayBounds;

};

#endif //TETRIS_SDLENGINE_H
