#include <functional>

// TODO: Double check the lambda implementation.
template<
    typename T_container, 
    typename T = typename T_container::value_type, 
    class Fun>
void for_each(T_container& container, Fun lambda) {
    for (T& item : container) {
        lambda(item);
    }
}