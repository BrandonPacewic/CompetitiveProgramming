template<typename T_List>
void printList(const T_List &List, const bool space = true, const bool new_line = true) {
    for (int i = 0; i < List.size(); i++) {
        cout << List[i];
        
        if (space) cout << ' ';
    }    
        if (new_line)
            cout << '\n';
        else 
            cout << ' ';
}