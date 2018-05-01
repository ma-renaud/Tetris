#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#include "square_matrix.h"

enum class TetrominoShape { I, O, T, S, Z, J, L };

class Tetromino {
public:
  Tetromino() = default;
  virtual ~Tetromino() = default;

  TetrominoShape shape() { return _shape; }
  int xpos() { return _xpos; }
  int ypos() { return _ypos; }
  void move(int x, int y) { _xpos += x; _ypos += y; }
  virtual void rotate(Rotation way) = 0;
  virtual int matrix_size() = 0;
  virtual bool is_present(int x, int y) = 0;

protected:
  TetrominoShape _shape = TetrominoShape::I;
  int _xpos = 0;
  int _ypos = 0;
};

template<std::size_t N>
class TetrominoProxy : public Tetromino {
public:
  TetrominoProxy() = default;
  ~TetrominoProxy() override = default;

  void rotate(Rotation way) override { matrix.rotate(way); };
  int matrix_size() override { return static_cast<int>(N); }
  bool is_present(int x, int y) override { return matrix(x, y) > 0; }

protected:
  SquareMatrix<uint8_t, N> matrix{};

};

class I : public TetrominoProxy<4> {
public:
  I() {
    _shape = TetrominoShape::I;
    _xpos = 4;
    _ypos = 2;
    matrix.init({{{0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {1, 1, 1, 1},
                  {0, 0, 0, 0}}});
  }
};

class O : public TetrominoProxy<4> {
public:
  O() {
    _shape = TetrominoShape::O;
    _xpos = 4;
    _ypos = 2;
    matrix.init({{{0, 0, 0, 0},
                  {0, 1, 1, 0},
                  {0, 1, 1, 0},
                  {0, 0, 0, 0}}});
  }
};

class T : public TetrominoProxy<3> {
public:
  T() {
    _shape = TetrominoShape::T;
    _xpos = 4;
    _ypos = 3;
    matrix.init({{{0, 1, 0},
                  {1, 1, 1},
                  {0, 0, 0}}});
  }
};

class S : public TetrominoProxy<3> {
public:
  S() {
    _shape = TetrominoShape::S;
    _xpos = 4;
    _ypos = 3;
    matrix.init({{{0, 1, 1},
                  {1, 1, 0},
                  {0, 0, 0}}});
  }
};

class Z : public TetrominoProxy<3> {
public:
  Z() {
    _shape = TetrominoShape::Z;
    _xpos = 4;
    _ypos = 3;
    matrix.init({{{1, 1, 0},
                  {0, 1, 1},
                  {0, 0, 0}}});
  }
};

class J : public TetrominoProxy<3> {
public:
  J() {
    _shape = TetrominoShape::J;
    _xpos = 4;
    _ypos = 3;
    matrix.init({{{1, 0, 0},
                  {1, 1, 1},
                  {0, 0, 0}}});
  }
};

class L : public TetrominoProxy<3> {
public:
  L() {
    _shape = TetrominoShape::L;
    _xpos = 4;
    _ypos = 3;
    matrix.init({{{0, 0, 1},
                  {1, 1, 1},
                  {0, 0, 0}}});
  }
};

#endif //TETRIS_TETROMINO_H
