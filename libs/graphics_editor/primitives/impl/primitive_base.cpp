#include <primitive_base.hpp>

PrimitiveBase::PrimitiveBase(float x, float y, Colour colour)
    : x(x), y(y), colour(colour) {}

void PrimitiveBase::set_colour(Colour new_colour) { colour = new_colour; }

void PrimitiveBase::move(float x_add, float y_add) {
  x += x;
  y += y;
}

Colour &PrimitiveBase::get_colour(void) { return colour; }

std::pair<float, float> PrimitiveBase::get_pos(void) {
  return std::make_pair(x, y);
}
