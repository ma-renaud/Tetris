#ifndef TETRIS_WELL_H
#define TETRIS_WELL_H

#include <array>

class Well {
public:
  Well();
  ~Well() = default;

  static constexpr uint8_t WIDTH = 12;
  static constexpr uint8_t HEIGHT = 22;

  uint8_t get_tile(int x, int y);

private:
  std::array<std::array<uint8_t, WIDTH>, HEIGHT> well;

  void init();
};

#endif //TETRIS_WELL_H
