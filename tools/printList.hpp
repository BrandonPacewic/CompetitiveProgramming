template<typename T_List>
void printList(T_List List, bool space = true, bool new_line = true) {
    for (int i = 0; i < List.size(); i++) {
        cout << List[i];
        
        if (space)
            cout << ' ';
        
        cout << new_line && i == List.size() - 1 ? '\n' : ' '; 
    }
}