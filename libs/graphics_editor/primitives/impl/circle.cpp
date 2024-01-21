#include <circle.hpp>

#include <iomanip>
#include <iostream>

const PrimitiveTypes Circle::type = PrimitiveTypes::Circle;

Circle::Circle() : PrimitiveBase(0.0, 0.0, Colour::Red), radius(0.0) {}

Circle::Circle(float x, float y, Colour colour, float radius)
    : PrimitiveBase(x, y, colour), radius(radius) {}

Circle::Circle(const Circle &obj) : PrimitiveBase(obj), radius(obj.radius) {}

void Circle::draw() {
  std::cout << *this;
  // << std::fixed << std::setprecision(2) << "Drawing a circle\npos = ("
  //           << x << ", " << y << "), colour = " << colour_map[colour].name
  //           << ", radius = " << radius << "\n ";
}

void Circle::resize(float factor) {
  if (factor > 0) {
    radius *= factor;
  }
}

std::ostream &operator<<(std::ostream &os, const Circle &obj) {
  os << obj.type << " " << obj.x << " " << obj.y << " " << obj.colour << " "
     << obj.radius << "\n";
  return os;
}

std::istream &operator>>(Circle &obj, std::istream &is) {
  is >> obj.x >> obj.y >> obj.colour >> obj.radius;
  return is;
}
