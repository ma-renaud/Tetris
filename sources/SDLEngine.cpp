#include "SDLEngine.h"

void SDLEngine::poll_event(EngineWrapper::Event &event) {
  SDL_Event sdl_event;
  SDL_PollEvent(&sdl_event);

  switch (sdl_event.type) {
    case SDL_QUIT: {
      event.type = EngineWrapper::EventType::QUIT;
      break;
    }
    case SDL_KEYDOWN: {
      event.type = EngineWrapper::EventType::KEYDOWN;
      event.key = static_cast<EngineWrapper::Key>(sdl_event.key.keysym.sym);
      break;
    }
    case SDL_KEYUP: {
      event.type = EngineWrapper::EventType::KEYUP;
      break;
    }
    default:break;
  }
}
