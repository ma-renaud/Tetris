#ifndef TETRIS_MATRIX_H
#define TETRIS_MATRIX_H

#include <array>

enum class Rotation { CW, CCW };

template<typename T, std::size_t N>
class SquareMatrix {
public:
  SquareMatrix() = default;
  ~SquareMatrix() = default;

  T &operator()(int x, int y) { return data.at(x).at(y); }
  constexpr std::size_t size() const noexcept { return N; }
  bool operator==(const SquareMatrix<T, N> &lhs) const { return data == lhs.data; }

  void rotate(Rotation way) {
    if (way == Rotation::CW)
      rotate_cw();
    else if(way == Rotation::CCW)
      rotate_ccw();
  }

private:
  std::array<std::array<T, N>, N> data;
  void rotate_ccw() {
    for (int x = 0; x < N / 2; x++) {
      for (int y = x; y < N - x - 1; y++) {
        int temp = data[x][y];
        data[x][y] = data[y][N - 1 - x];
        data[y][N - 1 - x] = data[N - 1 - x][N - 1 - y];
        data[N - 1 - x][N - 1 - y] = data[N - 1 - y][x];
        data[N - 1 - y][x] = temp;
      }
    }
  }

  void rotate_cw() {
    for (int x = 0; x < N / 2; x++) {
      for (int y = x; y < N - x - 1; y++) {
        int temp = data[x][y];
        data[x][y] = data[N - 1 - y][x];
        data[N - 1 - y][x] = data[N - 1 - x][N - 1 - y];
        data[N - 1 - x][N - 1 - y] = data[y][N - 1 - x];
        data[y][N - 1 - x] = temp;
      }
    }
  }
};

#endif //TETRIS_MATRIX_H
