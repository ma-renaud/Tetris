#ifndef TETRIS_SDLENGINE_H
#define TETRIS_SDLENGINE_H

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include "engine.h"

class SDLEngine : public EngineWrapper::Engine {
 public:
  SDLEngine() = default;
  ~SDLEngine() override = default;

  bool init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) override;
  int poll_event(EngineWrapper::Event &event) override;
  void clean() override;
  uint32_t get_ticks() override;

  SDL_Renderer *get_renderer() { return renderer; }
  TTF_Font *get_font() { return font; }
  int get_window_width() { return width; }
  int get_window_height() { return height; }

 private:
  int width = 0;
  int height = 0;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  TTF_Font *font = nullptr;

};

#endif //TETRIS_SDLENGINE_H
