#include "gmock/gmock.h"
#include "tetromino.h"

using namespace testing;

class TetrominoTestGroup : public Test {
public:
  std::unique_ptr<Tetromino> tetromino = std::make_unique<I>();

  void SetUp() override {

  }
};

TEST_F(TetrominoTestGroup, test_move) { // NOLINT
  int expectedx = 2;
  int expectedy = 0;

  tetromino->move(-2, -2);

  ASSERT_THAT(tetromino->xpos(), Eq(expectedx));
  ASSERT_THAT(tetromino->ypos(), Eq(expectedy));
}

