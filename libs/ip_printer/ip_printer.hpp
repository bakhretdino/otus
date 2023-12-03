#ifndef __IP_PRINTER__
#define __IP_PRINTER__

#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

/* integer instantiation */
template <typename T>
typename std::enable_if<
    std::is_integral<std::remove_reference_t<T>>::value>::type
print_ip(T ip) {
  for (int i = sizeof(T) - 1; i >= 0; --i) {
    std::cout << ((ip >> (8 * i)) & 0xFF);
    if (i > 0)
      std::cout << ".";
  }
  std::cout << "\n";
}

/* string instantiation */
template <typename T>
typename std::enable_if<
    std::is_same<std::remove_reference_t<T>, std::string>::value>::type
print_ip(T ip) {
  std::cout << ip << "\n";
}

/* vector and list instantiation */

template <typename T> struct is_vector : std::false_type {};

template <typename... Args>
struct is_vector<std::vector<Args...>> : std::true_type {};

template <typename T> struct is_list : std::false_type {};

template <typename... Args>
struct is_list<std::list<Args...>> : std::true_type {};

template <typename T>
typename std::enable_if<is_vector<std::remove_reference_t<T>>::value ||
                        is_list<std::remove_reference_t<T>>::value>::type
print_ip(T ip) {
  auto it = ip.begin();
  const auto end = ip.end();

  while (it != end) {
    std::cout << *it;

    if (++it != end) {
      std::cout << ".";
    }
  }

  std::cout << "\n";
}

/* Tuple with the same argument types instantiation */
template <typename... Args> struct are_all_same;

template <typename T> struct are_all_same<T> : std::true_type {};

template <typename T, typename U, typename... Args>
struct are_all_same<T, U, Args...>
    : std::conditional_t<std::is_same_v<T, U>, are_all_same<U, Args...>,
                         std::false_type> {};

// Function template for tuples with all same types
template <typename... Args>
typename std::enable_if<are_all_same<Args...>::value>::type
print_ip(std::tuple<Args...> &&ip) {
  std::apply(
      [](const auto &...args) {
        std::size_t i = 0;
        ((std::cout << args << (++i == sizeof...(Args) ? "" : ".")), ...);
        std::cout << std::endl;
      },
      ip);
}
#endif /* __IP_PRINTER__ */
