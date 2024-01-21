#include <mlp_classifier.hpp>

#include <algorithm>
#include <cmath>

using Eigen::VectorXf;

MLPClassifier::MLPClassifier(const Eigen::MatrixXf &w1,
                             const Eigen::MatrixXf &w2)
    : w1(w1), w2(w2) {}

template <typename T> auto sigma(T x) { return 1 / (1 + std::exp(-x)); }

VectorXf sigmav(const VectorXf &v) {
  VectorXf res(v.rows());
  for (size_t i = 0; i < v.rows(); i++) {
    res(i) = sigma(v(i));
  }
  return res;
}

VectorXf softmax(const VectorXf &v) {
  VectorXf res(v.rows());
  float denominator = 0.0f;

  for (size_t i = 0; i < v.rows(); i++) {
    denominator += std::exp(v(i));
  }

  for (size_t i = 0; i < v.rows(); i++) {
    res(i) = std::exp(v(i) / denominator);
  }
  return res;
}

size_t MLPClassifier::num_classes() const { return w2.cols(); }

size_t MLPClassifier::predict_one(const features_t &f) const {
  auto proba = predict_all(f);
  auto max_element = std::max_element(proba.begin(), proba.end());
  return std::distance(proba.begin(), max_element);
}

MLPClassifier::probas_t MLPClassifier::predict_all(const features_t &f) const {
  VectorXf x(f.size());
  for (size_t i = 0; i < f.size(); i++) {
    x(i) = f[i] / 255;
  }

  auto o1 = sigmav(w1 * x);
  auto o2 = softmax(w2 * o1);

  probas_t res;

  for (size_t i = 0; i < o2.rows(); i++) {
    res.push_back(o2(i));
  }
  return res;
}
