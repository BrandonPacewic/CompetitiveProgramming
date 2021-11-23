template<typename T_Matrix> int64_t trace(T_Matrix Matrix) {
        int64_t total = 0;
        for (int64_t i = 0; i < Matrix.size(); i++)
            total += int64_t(Matrix[i][i]);
        
        return total;
}