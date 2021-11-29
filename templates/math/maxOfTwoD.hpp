template<typename T_Grid> 
int maxOfGrid(T_Grid Grid) {
    int sum = 0;
    for (int i = 0; i < Grid.size(); i++)
        for (int j = 0; j < Grid[i].size(); j++)
            sum += Grid[i][j];
    
    return sum;
}