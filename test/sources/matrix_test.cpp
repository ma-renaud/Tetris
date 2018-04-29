#include "gmock/gmock.h"
#include "square_matrix.h"

using namespace testing;

class MatrixTestGroup : public Test {
public:
  static constexpr int SIZE = 3;
  SquareMatrix<int, SIZE> matrix{};

  template<std::size_t N>
  void init_matrix(SquareMatrix<int, N> &toInit) {
    for (int i = 0; i < toInit.size(); i++) {
      for (int j = 0; j < toInit.size(); j++) {
        toInit(i, j) = static_cast<int>(i * N + j + 1);
      }
    }
  }

  void SetUp() override {
    init_matrix<SIZE>(matrix);
  }
};

TEST_F(MatrixTestGroup, test_matrix_access) { // NOLINT
  int expected = 5;
  matrix(2, 2) = 5;

  ASSERT_THAT(matrix(2, 2), Eq(expected));
}

TEST_F(MatrixTestGroup, test_matrix_overflow) { // NOLINT
  ASSERT_THROW(matrix(2, 3) = 5, std::out_of_range);
}

TEST_F(MatrixTestGroup, test_init) { // NOLINT
  SquareMatrix<int, 3> expected{};
  expected.init({{{1, 2, 3},
                  {4, 5, 6},
                  {7, 8, 9}}});

  ASSERT_THAT(matrix, Eq(expected));
}

TEST_F(MatrixTestGroup, test_rotate_clockwise) { // NOLINT
  SquareMatrix<int, 4> expected{};
  expected.init({{{13, 9, 5, 1},
                  {14, 10, 6, 2},
                  {15, 11, 7, 3},
                  {16, 12, 8, 4}}});

  SquareMatrix<int, 4> matrix_x4{};
  init_matrix<4>(matrix_x4);
  matrix_x4.rotate(Rotation::CW);

  ASSERT_THAT(matrix_x4, Eq(expected));
}

TEST_F(MatrixTestGroup, test_rotate_counter_clockwise) { // NOLINT
  SquareMatrix<int, 4> expected{};
  expected.init({{{4, 8, 12, 16},
                  {3, 7, 11, 15},
                  {2, 6, 10, 14},
                  {1, 5, 9, 13}}});

  SquareMatrix<int, 4> matrix_x4{};
  init_matrix<4>(matrix_x4);
  matrix_x4.rotate(Rotation::CCW);

  ASSERT_THAT(matrix_x4, Eq(expected));
}

