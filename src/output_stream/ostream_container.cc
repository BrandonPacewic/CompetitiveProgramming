#include <algorithm>
#include <ostream>
#include <string>

template <typename T_container,
          typename T = typename std::enable_if<
              !std::is_same<T_container, std::string>::value,
              typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream& os, const T_container& container) {
    os << '{';
    std::string sep;

    for (const T& item : container) {
        os << sep << item, sep = ", ";
    }

    return os << '}';
}
