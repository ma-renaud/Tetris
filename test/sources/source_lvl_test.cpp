#include "gmock/gmock.h"

using namespace testing;

#include "score_lvl.h"

class ScoreTestGroup : public TestWithParam<int> {
public:
  std::unique_ptr<ScoreLvl> score = std::make_unique<ScoreLvl>();
};

TEST_F(ScoreTestGroup, test_score_one_line) { // NOLINT
  score->update(1);
  ASSERT_THAT(score->get_score(), Eq(40));
}

TEST_F(ScoreTestGroup, test_score_two_line) { // NOLINT
  score->update(2);
  ASSERT_THAT(score->get_score(), Eq(100));
}

TEST_F(ScoreTestGroup, test_score_three_line) { // NOLINT
  score->update(3);
  ASSERT_THAT(score->get_score(), Eq(300));
}

TEST_F(ScoreTestGroup, test_score_four_line) { // NOLINT
  score->update(4);
  ASSERT_THAT(score->get_score(), Eq(1200));
}

TEST_F(ScoreTestGroup, test_level_up_one_lines) { // NOLINT
  score->update(1);
  score->update(1);
  score->update(1);
  score->update(1);
  score->update(1);
  ASSERT_THAT(score->get_level(), Eq(1));
}

TEST_F(ScoreTestGroup, test_level_up_four_lines) { // NOLINT
  score->update(4);
  ASSERT_THAT(score->get_level(), Eq(1));
}