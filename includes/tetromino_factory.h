#ifndef TETRIS_TETROMINO_FACTORY_H
#define TETRIS_TETROMINO_FACTORY_H

#include "tetromino.h"

class TetrominoFactory {
public:
  static std::unique_ptr<Tetromino> getTetromino(TetrominoShape shape) {
    switch (shape) {
    case TetrominoShape::I :return std::make_unique<I>();
    case TetrominoShape::O :return std::make_unique<O>();
    case TetrominoShape::T :return std::make_unique<T>();
    case TetrominoShape::S :return std::make_unique<S>();
    case TetrominoShape::Z :return std::make_unique<Z>();
    case TetrominoShape::J :return std::make_unique<J>();
    case TetrominoShape::L :return std::make_unique<L>();
    default :return std::make_unique<I>();
    }
  }
};

#endif //TETRIS_TETROMINO_FACTORY_H
