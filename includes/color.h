#ifndef TETRIS_COLOR_H
#define TETRIS_COLOR_H

class Color {
public:
  static const int MAX = 0xff;
  Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = MAX) {
    _red = red;
    _green = green;
    _blue = blue;
    _alpha = alpha;
  }

  Uint8 red() { return _red; }
  Uint8 green() { return _green; }
  Uint8 blue() { return _blue; }
  Uint8 alpha() { return _alpha; }

private:
  Uint8 _red;
  Uint8 _green;
  Uint8 _blue;
  Uint8 _alpha;
};

#endif //TETRIS_COLOR_H
