template<typename T_List, typename Type> bool findInList(T_List List, Type find) {
    for (Type i : List)
        if (i == find)
            return true;
    return false;
}