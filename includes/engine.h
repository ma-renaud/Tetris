#ifndef TETRIS_ENGINE_H
#define TETRIS_ENGINE_H

namespace EngineWrapper {

enum class EventType { NONE, QUIT, KEYDOWN, KEYUP };

enum class Key {
  UNKNOWN = 0,
  RETURN = 13,
  ESCAPE = 27,
  DOWN = 1073741905,
  UP = 1073741906,
  LEFT = 1073741904,
  RIGHT = 1073741903
};

class Event {
 public:
  Event() = default;
  ~Event() = default;
  EventType type = EventType::NONE;
  Key key = Key::UNKNOWN;
};

class Engine {
 public:
  Engine() = default;
  virtual ~Engine() = default;

  virtual void poll_event(Event &event) = 0;
};
}

#endif //TETRIS_ENGINE_H
