#ifndef TETRIS_BAG_H
#define TETRIS_BAG_H

#include "tetromino_factory.h"
#include "tetromino.h"
#include <deque>
#include <random>

class Bag {
public:
  Bag();
  ~Bag() = default;

  std::unique_ptr<Tetromino> next();
  std::unique_ptr<Tetromino> preview() { return bag.front()->clone(); }
  std::size_t bag_count() { return bag.size(); }

  static constexpr int BAG_SIZE = 7;
  static constexpr int S_OR_Z_MAX_STREAK = 4;
  static constexpr int MAXIMUM_INTERVAL_WITHOUT_I = 12;

protected:
  std::deque<std::unique_ptr<Tetromino>> bag;
  std::uniform_int_distribution<int> shapes;
  std::mt19937 prng;
  int piece_since_last_I{0};
  int S_or_Z_streak{0};

private:
  void fill();
  bool exceed_I_interval(TetrominoShape shape);
  bool exceed_S_or_Z_streak(TetrominoShape shape);
};

#endif //TETRIS_BAG_H
