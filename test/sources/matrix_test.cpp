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
  expected(0,0) = 1;
  expected(0,1) = 2;
  expected(0,2) = 3;
  expected(1,0) = 4;
  expected(1,1) = 5;
  expected(1,2) = 6;
  expected(2,0) = 7;
  expected(2,1) = 8;
  expected(2,2) = 9;

  ASSERT_THAT(matrix, Eq(expected));
}

TEST_F(MatrixTestGroup, test_rotate_clockwise) { // NOLINT
  SquareMatrix<int, 4> expected{};
  expected(0,0) = 13;
  expected(0,1) = 9;
  expected(0,2) = 5;
  expected(0,3) = 1;
  expected(1,0) = 14;
  expected(1,1) = 10;
  expected(1,2) = 6;
  expected(1,3) = 2;
  expected(2,0) = 15;
  expected(2,1) = 11;
  expected(2,2) = 7;
  expected(2,3) = 3;
  expected(3,0) = 16;
  expected(3,1) = 12;
  expected(3,2) = 8;
  expected(3,3) = 4;

  SquareMatrix<int, 4> matrix_x4{};
  init_matrix<4>(matrix_x4);
  matrix_x4.rotate(Rotation::CW);

  ASSERT_THAT(matrix_x4, Eq(expected));
}

TEST_F(MatrixTestGroup, test_rotate_counter_clockwise) { // NOLINT
  SquareMatrix<int, 4> expected{};
  expected(0,0) = 4;
  expected(0,1) = 8;
  expected(0,2) = 12;
  expected(0,3) = 16;
  expected(1,0) = 3;
  expected(1,1) = 7;
  expected(1,2) = 11;
  expected(1,3) = 15;
  expected(2,0) = 2;
  expected(2,1) = 6;
  expected(2,2) = 10;
  expected(2,3) = 14;
  expected(3,0) = 1;
  expected(3,1) = 5;
  expected(3,2) = 9;
  expected(3,3) = 13;

  SquareMatrix<int, 4> matrix_x4{};
  init_matrix<4>(matrix_x4);
  matrix_x4.rotate(Rotation::CCW);

  ASSERT_THAT(matrix_x4, Eq(expected));
}

