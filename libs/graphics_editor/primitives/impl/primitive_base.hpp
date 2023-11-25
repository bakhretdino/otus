#ifndef __PRIMITIVE_BASE__
#define __PRIMITIVE_BASE__

#include <colours.hpp>
#include <iprimitive.hpp>

class PrimitiveBase : public IPrimitive {
protected:
  float x;
  float y;
  Colour colour;

public:
  PrimitiveBase(float x, float y, Colour colour);
  void set_colour(Colour) override;
  Colour &get_colour(void) override;
  void move(float, float) override;
  std::pair<float, float> get_pos(void) override;
};

#endif /* __PRIMITIVE_BASE__ */
