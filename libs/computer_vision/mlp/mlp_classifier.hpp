#ifndef __MLP_CLASSIFIER__
#define __MLP_CLASSIFIER__

#include <iclassifier.hpp>

#include <Eigen/Dense>

class MLPClassifier : public IClassifier {
private:
  Eigen::MatrixXf w1, w2;

public:
  MLPClassifier(const Eigen::MatrixXf &, const Eigen::MatrixXf &);
  size_t num_classes() const override;
  size_t predict_one(const features_t &) const override;
  probas_t predict_all(const features_t &) const override;
};

#endif /* __MLP_CLASSIFIER__ */
