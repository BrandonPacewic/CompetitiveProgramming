// TODO: Fun needs to be a bool lambda function
template<typename T, class Fun>
void print_empty_matrix(const int &_x, const int &_y, T _a, T _b, Fun condition, const bool space = false) {
    for (int x = 0; x < _x; x++) {
        for (int y = 0; y < _y; y++) {
            std::cout << (condition(x, y) ? _b : _a);

            if (space) std::cout << ' ';
        }

        std::cout << '\n';
    }
}