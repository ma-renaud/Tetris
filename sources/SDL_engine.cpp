#include "SDL_engine.h"
#include <SDL_engine.h>
#include <iostream>

namespace {
const std::map<Uint32, EngineWrapper::EventType> event_map =
    {{SDL_QUIT, EngineWrapper::EventType::QUIT},
     {SDL_KEYDOWN, EngineWrapper::EventType::KEYDOWN},
     {SDL_KEYUP, EngineWrapper::EventType::KEYUP}};
}

bool SDL_engine::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
  bool res = false;
  this->width = width;
  this->height = height;

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystems Initialised!..." << std::endl;

    Uint32 flags = 0;
    if (fullscreen)
      flags = SDL_WINDOW_FULLSCREEN;

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window)
      std::cout << "Window created!" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
      std::cout << "Renderer created!" << std::endl;
    }

    if (TTF_Init() == -1) {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
      font = TTF_OpenFont("../../assets/LVDC_Game_Over.ttf", 16);
      if (font == nullptr) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
      }
    }
    res = true;
  }
  return res;
}

int SDL_engine::poll_event(EngineWrapper::Event &event) {
  SDL_Event sdl_event;
  bool res = SDL_PollEvent(&sdl_event);

  auto it = event_map.find(sdl_event.type);
  if (it != event_map.end()) {
    event.type = event_map.find(sdl_event.type)->second;
    event.key = static_cast<EngineWrapper::Key>(sdl_event.key.keysym.sym);
  }

  return res;
}

void SDL_engine::clean() {
  TTF_CloseFont(font);
  font = nullptr;

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

uint32_t SDL_engine::get_ticks() {
  return SDL_GetTicks();
}