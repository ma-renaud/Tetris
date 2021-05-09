#ifndef TETRIS_ENGINE_H
#define TETRIS_ENGINE_H

#include <cstdint>

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

struct Display {
  int x;
  int y;
  int width;
  int height;
};

class Engine {
 public:
  Engine() = default;
  virtual ~Engine() = default;

  virtual bool init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) = 0;
  virtual int poll_event(Event &event) = 0;
  virtual void clean() = 0;
  virtual uint32_t get_ticks() = 0;
  virtual void fullscreen_mode() = 0;
  virtual void window_mode() = 0;
  virtual void set_resolution(int width, int height) = 0;
  virtual void set_window_position(int x, int y) = 0;
  virtual int get_nb_displays() = 0;
  virtual Display display_info(uint8_t display) = 0;
};
}

#endif //TETRIS_ENGINE_H
