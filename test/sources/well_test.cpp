#include "gmock/gmock.h"
#include "well.h"

using namespace testing;

class WellTestGroup : public Test {
public:
  std::unique_ptr<Well> well = std::make_unique<Well>();
};

TEST_F(WellTestGroup, test_collision_left) { // NOLINT
  std::unique_ptr<Tetromino> tetromino = std::make_unique<T>();
  tetromino->move(-4,0);

  ASSERT_TRUE(well->is_collision(tetromino.get()));
}

TEST_F(WellTestGroup, test_collision_right) { // NOLINT
  std::unique_ptr<Tetromino> tetromino = std::make_unique<T>();
  tetromino->move(5,0);

  ASSERT_TRUE(well->is_collision(tetromino.get()));
}

TEST_F(WellTestGroup, test_collision_bottom) { // NOLINT
  std::unique_ptr<Tetromino> tetromino = std::make_unique<T>();
  tetromino->move(0,18);

  ASSERT_TRUE(well->is_collision(tetromino.get()));
}

TEST_F(WellTestGroup, test_out_of_well) { // NOLINT
  std::unique_ptr<Tetromino> tetromino = std::make_unique<T>();
  tetromino->move(0,42);

  ASSERT_NO_THROW(well->is_collision(tetromino.get()));
}



