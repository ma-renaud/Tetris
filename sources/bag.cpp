#include "bag.h"

Bag::Bag() : shapes{0, static_cast<int>(TetrominoShape::END_OF_SHAPES) - 1} {
  std::random_device rd; // source d'entropie
  prng = std::mt19937{rd()};
  fill();
}

std::unique_ptr<Tetromino> Bag::next() {
  std::unique_ptr<Tetromino> res = std::move(bag.front());
  bag.pop_front();
  fill();
  return std::move(res);
}

void Bag::fill() {
  while (bag_count() < BAG_SIZE) {
    std::unique_ptr<Tetromino> tetromino = TetrominoFactory::getTetromino(static_cast<TetrominoShape>(shapes(prng)));

    if (!bag.empty()) {
      if (exceed_I_interval(tetromino->shape())) {
        tetromino = TetrominoFactory::getTetromino(TetrominoShape::I);
        piece_since_last_I = 0;
      }

      if (exceed_S_or_Z_streak(tetromino->shape())) {
        while (tetromino->shape() == TetrominoShape::S or tetromino->shape() == TetrominoShape::Z) {
          tetromino.reset();
          tetromino = TetrominoFactory::getTetromino(static_cast<TetrominoShape>(shapes(prng)));
        }
        S_or_Z_streak = 0;
      }
    }

    bag.push_back(std::move(tetromino));
  }
}

bool Bag::exceed_I_interval(TetrominoShape shape) {
  if (shape == TetrominoShape::I)
    piece_since_last_I = 0;
  else
    ++piece_since_last_I;

  return piece_since_last_I > MAXIMUM_INTERVAL_WITHOUT_I;
}

bool Bag::exceed_S_or_Z_streak(TetrominoShape shape) {
  if ((shape == TetrominoShape::S or shape == TetrominoShape::Z) and
      (bag.front()->shape() == TetrominoShape::S or bag.front()->shape() == TetrominoShape::Z))
    ++S_or_Z_streak;
  else
    S_or_Z_streak = 0;

  return S_or_Z_streak > S_OR_Z_MAX_STREAK;
}
