#include "SDLEngine.h"
#include <SDL.h>

namespace {
const std::map<Uint32, EngineWrapper::EventType> event_map =
    {{SDL_QUIT, EngineWrapper::EventType::QUIT},
     {SDL_KEYDOWN, EngineWrapper::EventType::KEYDOWN},
     {SDL_KEYUP, EngineWrapper::EventType::KEYUP}};
}

void SDLEngine::poll_event(EngineWrapper::Event &event) {
  SDL_Event sdl_event;
  SDL_PollEvent(&sdl_event);

  auto it = event_map.find(sdl_event.type);
  if (it != event_map.end()) {
    event.type = event_map.find(sdl_event.type)->second;
    event.key = static_cast<EngineWrapper::Key>(sdl_event.key.keysym.sym);
  }
}