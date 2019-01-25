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
  void poll_event(EngineWrapper::Event &event) override;
  void clean() override;

 private:
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  TTF_Font *font = nullptr;

};

#endif //TETRIS_SDLENGINE_H
