template<typename T> bool findInList(T List, T find) {
    for (T i : List)
        if (i == find)
            return true;
    return false;
}