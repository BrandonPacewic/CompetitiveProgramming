template<typename T_Grid> 
int maxOfGrid(T_Grid Grid) {
    int max_val = -INF;
    for (int i = 0; i < Grid.size(); i++)
        for (int j = 0; j < Grid[i].size(); j++)
            max_val = max(max_val, Grid[i][j]);
    
    return max_val;
}