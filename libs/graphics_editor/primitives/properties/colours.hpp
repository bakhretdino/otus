#ifndef __COLOURS__
#define __COLOURS__

#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>

enum class Colour { Red, Green, Blue, Yellow };

inline std::istream &operator>>(std::istream &is, Colour &colour) {
  using UnderlyingType = std::underlying_type_t<Colour>;
  UnderlyingType colourValue;
  is >> colourValue;

  colour = static_cast<Colour>(colourValue);

  return is;
}

inline std::ostream &operator<<(std::ostream &os, const Colour &colour) {
  os << static_cast<std::underlying_type_t<Colour>>(colour);
  return os;
}

struct ColourInfo {
  const std::string name;
  const std::string rgb;
};

inline std::unordered_map<Colour, ColourInfo> colour_map = {
    {Colour::Red, {"Red", "#FF0000"}},
    {Colour::Green, {"Green", "#00FF00"}},
    {Colour::Blue, {"Blue", "#0000FF"}},
    {Colour::Yellow, {"Yellow", "#FFFF00"}},
};

#endif /* __COLOURS__ */
