template<typename T_container>
void output_container(const T_container& container, 
        const bool space = true, 
        const bool new_line = true) {
    for (std::size_t i = 0; i < container.size(); ++i) {
        std::cout << container[i];

        if (space && i < end - 1) {
            std::cout << ' ';
        }
    }

    std::cout << (new_line ? '\n' : ' ');
}