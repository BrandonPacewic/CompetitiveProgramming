#include <iostream>

// TODO: Fun needs to be a boolean func
template<typename T, class Fun>
void print_empty_matrix(const int& _x, const int& _y, T a, T b, Fun condition, 
        const bool& space = false) {
    for (int x = 0; x < _x; x++) {
        for (int y = 0; y < _y; y++) {
            std::cout << (condition(x, y) ? b : a);

            if (space) {
                std::cout << ' ';
            }
        }

        std::cout << '\n';
    }
}