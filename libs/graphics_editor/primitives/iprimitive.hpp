#ifndef __IPRIMITIVE__
#define __IPRIMITIVE__

#include <colours.hpp>
#include <iostream>

class IPrimitive {
public:
  // virtual void serialize(std::ostream &os) const = 0;
  // virtual void deserialize(std::istream &is) = 0;

  virtual void draw(void) = 0;
  virtual void resize(float) = 0;
  virtual void set_colour(Colour) = 0;
  virtual Colour &get_colour(void) = 0;
  virtual void move(float, float) = 0;
  virtual std::pair<float, float> get_pos(void) = 0;

  virtual ~IPrimitive() = default;
};

#endif /* __IPRIMITIVE__ */
