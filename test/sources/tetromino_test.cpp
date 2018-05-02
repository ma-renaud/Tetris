#include "gmock/gmock.h"
#include "tetromino.h"

using namespace testing;

class TetrominoTestGroup : public Test {
public:
  std::unique_ptr<Tetromino> tetromino = std::make_unique<I>();
};

TEST_F(TetrominoTestGroup, test_move) { // NOLINT
  int expected_x = 2;
  int expected_y = 0;

  tetromino->move(-2, -2);

  ASSERT_THAT(tetromino->xpos(), Eq(expected_x));
  ASSERT_THAT(tetromino->ypos(), Eq(expected_y));
}

