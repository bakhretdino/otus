#include <config.h>

#include <version.hpp>

int get_ver_major() {
#ifdef PROJECT_VERSION_MAJOR
  return PROJECT_VERSION_MAJOR;
#else
  return 0;
#endif
}
int get_ver_minor() {
#ifdef PROJECT_VERSION_MINOR
  return PROJECT_VERSION_MINOR;
#else
  return 0;
#endif
}
int get_ver_patch() {
#ifdef PROJECT_VERSION_PATCH
  return PROJECT_VERSION_PATCH;
#else
  return 0;
#endif
}
