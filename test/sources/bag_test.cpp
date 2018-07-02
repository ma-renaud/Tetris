#include "gmock/gmock.h"

using namespace testing;

#include "bag.h"

class ExposedBag : public Bag {
public:
  int get_last_I() {
    return piece_since_last_I;
  }

  int get_S_or_Z_streak() {
    return S_or_Z_streak;
  }
};

class BagTestGroup : public TestWithParam<int> {
public:
  std::unique_ptr<ExposedBag> bag = std::make_unique<ExposedBag>();
};

TEST_F(BagTestGroup, test_bag_fill) { // NOLINT
  ASSERT_THAT(bag->bag_count(), Eq(Bag::BAG_SIZE));
}

TEST_F(BagTestGroup, test_get_preview) { // NOLINT
  std::unique_ptr<Tetromino> tetromino = bag->preview();
  ASSERT_THAT(bag->bag_count(), Eq(Bag::BAG_SIZE));
}

TEST_F(BagTestGroup, test_get_next) { // NOLINT
  std::unique_ptr<Tetromino> tetromino = bag->next();
  ASSERT_THAT(bag->bag_count(), Eq(Bag::BAG_SIZE));
}

TEST_F(BagTestGroup, test_I_Interval) { // NOLINT
  for (int i = 0; i < 1000; i++) {
    std::unique_ptr<Tetromino> tetromino = bag->next();
    ASSERT_THAT(bag->get_last_I(), Le(Bag::MAXIMUM_INTERVAL_WITHOUT_I));
  }
}

TEST_F(BagTestGroup, test_S_or_Z_streak) { // NOLINT
  for (int i = 0; i < 1000; i++) {
    std::unique_ptr<Tetromino> tetromino = bag->next();
    ASSERT_THAT(bag->get_S_or_Z_streak(), Le(Bag::S_OR_Z_MAX_STREAK));
  }
}