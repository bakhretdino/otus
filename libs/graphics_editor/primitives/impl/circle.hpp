#ifndef __CIRCLE__
#define __CIRCLE__

#include <primitive_base.hpp>
#include <primitive_types.hpp>

class Circle : public PrimitiveBase {
private:
  static const PrimitiveTypes type;
  float radius;

public:
  Circle();
  Circle(float x, float y, Colour colour, float radius);
  Circle(const Circle &obj);

  void draw() override;
  void resize(float) override;

  friend std::ostream &operator<<(std::ostream &os, const Circle &obj);
  friend std::istream &operator>>(Circle &obj, std::istream &is);

  // void serialize(std::ostream &os) const override;
  // void deserialize(std::istream &is) override;
};

#endif /* __CIRCLE__ */
