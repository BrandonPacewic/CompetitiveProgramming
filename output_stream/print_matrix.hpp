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


template<typename T_matrix>
void output_matrix(const T_matrix& matrix) {
    for (int row = 0; row < int(matrix.size()); ++row) {
        for (int cell = 0; cell < int(matrix[row].size); ++cell) {
            std::cout << matrix[row][cell] << (
                cell > int(matrix[row].size() - 1) ? '\n' : ' ');
        }
    }
}