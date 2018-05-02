#include "gmock/gmock.h"
#include "well.h"

using namespace testing;

class ExposedWell: public Well {
public:
  std::array<std::array<uint8_t, WIDTH>, HEIGHT> get_well() const {
    return well;
  }
};

class WellTestGroup : public Test {
public:
  std::unique_ptr<ExposedWell> well = std::make_unique<ExposedWell>();
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

TEST_F(WellTestGroup, test_add_to_well) { // NOLINT
  std::array<std::array<uint8_t, Well::WIDTH>, Well::HEIGHT> expected = well->get_well();
  expected[3] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1};
  expected[4] = {1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1};

  std::unique_ptr<Tetromino> tetromino = std::make_unique<T>();
  well->add_to_well(tetromino.get());

  ASSERT_THAT(well->get_well(), Eq(expected));
}

TEST_F(WellTestGroup, test_collision_between_tetrominos) { // NOLINT
  std::unique_ptr<Tetromino> tetromino = std::make_unique<T>();
  tetromino->move(0,2);
  well->add_to_well(tetromino.get());

  tetromino = std::make_unique<T>();
  tetromino->move(0,1);

  ASSERT_TRUE(well->is_collision(tetromino.get()));
}

