#include <iostream>
#include <sparse_matrix.hpp>

void preliminary_checks() {
  SparseMatrix<int, -1> sparse_matrix;
  assert(sparse_matrix.size() == 0);
  auto a = sparse_matrix[0][0];
  assert(a == -1);
  assert(sparse_matrix.size() == 0);
  sparse_matrix[9][9] = 314;
  assert(sparse_matrix[9][9] == 314);
  assert(sparse_matrix.size() == 1);

  ((sparse_matrix[10][10] = 314) = 0) = 217;
  assert(sparse_matrix[10][10] == 217);
  assert(sparse_matrix.size() == 2);
  std::cout << sparse_matrix;
}

int main() {
  // preliminary_checks();
  SparseMatrix<int, 0> sparse_matrix;
  for (int i = 0, j = 0; i <= 9 && j <= 9; i++, j++) {
    sparse_matrix[i][j] = i;
  }

  for (int i = 9, j = 0; i >= 0 && j <= 9; i--, j++) {
    sparse_matrix[i][j] = i;
  }
  assert(sparse_matrix.size() == 18);

  sparse_matrix.print(std::make_pair(1, 1), std::make_pair(8, 8));
}
