#ifndef __ICLASSIFIER__
#define __ICLASSIFIER__

#include <cstddef>
#include <vector>

class IClassifier {
public:
  using features_t = std::vector<float>;
  using probas_t = std::vector<float>;

  virtual ~IClassifier() = default;

  virtual size_t num_classes() const = 0;

  virtual size_t predict_one(const features_t &) const = 0;
  virtual probas_t predict_all(const features_t &) const = 0;
};

#endif /* __ICLASSIFIER__ */
