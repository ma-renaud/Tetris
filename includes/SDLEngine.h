#ifndef TETRIS_SDLENGINE_H
#define TETRIS_SDLENGINE_H

#include <map>
#include "engine.h"

class SDLEngine : public EngineWrapper::Engine {
 public:
  SDLEngine() = default;
  ~SDLEngine() override = default;

  void poll_event(EngineWrapper::Event &event) override;
};

#endif //TETRIS_SDLENGINE_H
