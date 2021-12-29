template<typename T_List>
void print_list(const T_List &List, const bool space = true, const bool new_line = true, int start = -1, int end = -1) {
if (start == -1) start = 0;
if (end == -1) end = List.size();

    for (int i = start; i < end; i++) {
        std::cout << List[i];
        
        if (space) std::cout << ' ';
    }    
        if (new_line)
            std::cout << '\n';
        else 
            std::cout << ' ';
}