#include <fstream>
#include <iomanip>
#include <iostream>

#include <mlp_classifier.hpp>

Eigen::MatrixXf read_and_transpose_matrix(const std::string &file_path) {

  std::ifstream file(file_path);
  if (!file.is_open()) {
    std::ostringstream error_msg;
    error_msg << "Failed to open file " << file_path;
    throw std::runtime_error(error_msg.str());
  }

  std::vector<std::vector<float>> matrix_data;
  std::string line;
  while (std::getline(file, line)) {
    std::vector<float> row;
    std::istringstream stream(line);
    float value;
    while (stream >> value) {
      row.push_back(value);
      if (stream.peek() == ',' || stream.peek() == ' ') {
        stream.ignore();
      }
    }
    matrix_data.push_back(row);
  }

  Eigen::MatrixXf matrix(matrix_data[0].size(), matrix_data.size());
  for (int i = 0; i < matrix_data.size(); ++i) {
    for (int j = 0; j < matrix_data[0].size(); ++j) {
      matrix(j, i) = matrix_data[i][j];
    }
  }

  return matrix;
}

int main(int argc, char **argv) {

  if (argc != 4) {
    std::cout << "Usage: " << argv[0]
              << " <test_data_file> <model_1_file> <model_2_file>\n";
    return -1;
  }

  std::string test_data_file(argv[1]);
  std::string model_1_file(argv[2]);
  std::string model_2_file(argv[3]);

  auto transp_w1 = read_and_transpose_matrix(model_1_file);
  auto transp_w2 = read_and_transpose_matrix(model_2_file);

  auto mlp_classifier = MLPClassifier(transp_w1, transp_w2);

  std::ifstream test_data(test_data_file.c_str());
  std::string line;
  int iter = 0;
  int matches = 0;
  while (std::getline(test_data, line)) {
    std::istringstream ss(line);
    size_t type_exp;

    if (ss >> type_exp) {
      std::vector<float> features;

      std::string feature;
      while (std::getline(ss, feature, ',')) {
        if (!feature.empty()) {
          features.push_back(std::stof(feature));
        }
      }

      size_t type_actual = mlp_classifier.predict_one(features);
      if (type_actual == type_exp) {
        matches++;
      }
      iter++;
    }
  }

  float result = (float)matches / iter;
  std::cout << std::fixed << std::setprecision(2) << result << std::endl;

  return 0;
}
