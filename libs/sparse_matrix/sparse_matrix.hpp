#ifndef __SPARSE_MATRIX__
#define __SPARSE_MATRIX__

#include <boost/functional/hash.hpp>
#include <cstddef>
#include <iomanip>
#include <ostream>
#include <unordered_map>
#include <utility>

template <typename T, T default_val> class SparseMatrix;

template <typename T, T default_val>
std::ostream &operator<<(std::ostream &os,
                         const SparseMatrix<T, default_val> &mat);

template <typename T, T default_val = T()> class SparseMatrix {
private:
  std::unordered_map<std::pair<int, int>, T, boost::hash<std::pair<int, int>>>
      sparse_matrix;

  class Proxy {
  private:
    SparseMatrix &matrix_ref;
    int row;
    int col;

  public:
    Proxy(SparseMatrix &matrix_ref, int row)
        : matrix_ref(matrix_ref), row(row) {}

    Proxy &operator[](int col) {
      this->col = col;
      return *this;
    }

    Proxy &operator=(T value) {
      if (value == default_val) {
        auto it = matrix_ref.sparse_matrix.find(std::make_pair(row, col));
        if (it != matrix_ref.sparse_matrix.end()) {
          matrix_ref.sparse_matrix.erase(it);
        }
      } else {
        matrix_ref.sparse_matrix[std::make_pair(row, col)] = value;
      }
      return *this;
    }
    operator T() const {
      auto it = matrix_ref.sparse_matrix.find(std::make_pair(row, col));
      return (it != matrix_ref.sparse_matrix.end()) ? it->second : default_val;
    }
  };

public:
  size_t size(void) { return sparse_matrix.size(); }

  void print(const std::pair<int, int> &start_pos,
             const std::pair<int, int> &end_pos) {
    for (int i = start_pos.first; i <= end_pos.first; i++) {
      for (int j = start_pos.second; j <= end_pos.second; j++) {
        auto it = sparse_matrix.find(std::make_pair(i, j));
        const auto &print_val =
            (it != sparse_matrix.end()) ? it->second : default_val;
        std::cout << std::setw(1) << print_val << " ";
      }
      std::cout << "\n";
    }
  }

  Proxy operator[](int row) { return Proxy(*this, row); }

  template <class U, U def_val>
  friend std::ostream &operator<<(std::ostream &os,
                                  SparseMatrix<U, def_val> &mat);
};

template <typename T, T default_val>
inline std::ostream &operator<<(std::ostream &os,
                                SparseMatrix<T, default_val> &mat) {
  int max_row = 0;
  int max_col = 0;
  for (const auto &entry : mat.sparse_matrix) {
    max_row = std::max(max_row, entry.first.first);
    max_col = std::max(max_col, entry.first.second);
  }
  for (int i = 0; i <= max_row; i++) {
    for (int j = 0; j <= max_col; j++) {
      auto it = mat.sparse_matrix.find(std::make_pair(i, j));
      const auto &print_val =
          (it != mat.sparse_matrix.end()) ? it->second : default_val;
      os << std::setw(1) << print_val << " ";
    }
    os << "\n";
  }
  return os;
}

#endif /* __SPARSE_MATRIX__ */
