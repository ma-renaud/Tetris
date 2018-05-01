#ifndef TETRIS_WELL_H
#define TETRIS_WELL_H

#include <array>

class Well {
public:
  Well();
  ~Well() = default;

private:
  static constexpr uint8_t WIDTH = 12;
  static constexpr uint8_t HEIGHT = 22;
  std::array<std::array<uint8_t, WIDTH>, HEIGHT> well;

  void init();
};

#endif //TETRIS_WELL_H
