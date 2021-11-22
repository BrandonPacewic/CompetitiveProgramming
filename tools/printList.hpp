template<typename T_List>
void printList(T_List List, bool space = true, bool new_line = true) {

    for (int i = 0; i < List.size(); i++) {
        cout << List[i];
        
        if (space)
            cout << ' ';
    }    
        if (new_line)
            cout << '\n';
        else 
            cout << ' ';
}