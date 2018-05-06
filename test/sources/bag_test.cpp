#include "gmock/gmock.h"

using namespace testing;

class BagTestGroup : public TestWithParam<int> {
public:
  //std::unique_ptr<ExposedWell> well = std::make_unique<ExposedWell>();
};

TEST_P(BagTestGroup, test_bag) { // NOLINT
  FAIL();
}

//INSTANTIATE_TEST_CASE_P(Generation, BagTestGroup, Range(0, 100)); // NOLINT



