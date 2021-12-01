template<typename T_Matrix>
void printMatrix(const T_Matrix &MATRIX) {
    for (int i = 0; i < MATRIX.size(); i++)
        for (int j = 0; j < MATRIX[i].size(); j++)
            cout << MATRIX[i][j] << (j < MATRIX[i].size() - 1 ? ' ' : '\n'); 
}