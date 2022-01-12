template<typename T_matrix>
void print_matrix(const T_matrix &matrix, const bool _space = false, const bool _newLine = true) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j];

            if (_space) 
                std::cout << ' ';
        }

        if (_newLine)
            std::cout << '\n';
    }
}