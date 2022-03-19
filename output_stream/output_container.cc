template<typename T_container>
void output_container(const T_container& container, const bool& space = true,
    const bool& new_line = true) {
    int start = 0;
    int end = int(container.size());

    for (int i = start; i < end; ++i) {
        std::cout << container[i];

        if (space && i < end - 1) std::cout << ' ';
    }

    std::cout << (new_line ? '\n' : ' ');
}