#ifndef __PRIMITIVE_TYPES__
#define __PRIMITIVE_TYPES__

#include <istream>
#include <ostream>

enum class PrimitiveTypes {
  Circle,
};

inline std::ostream &operator<<(std::ostream &os, const PrimitiveTypes &type) {
  return os << static_cast<std::underlying_type_t<PrimitiveTypes>>(type);
}

inline std::istream &operator>>(std::istream &is, PrimitiveTypes &type) {
  int underlyingValue;
  is >> underlyingValue;

  type = static_cast<PrimitiveTypes>(underlyingValue);

  return is;
}

#endif /* __PRIMITIVE_TYPES__ */
