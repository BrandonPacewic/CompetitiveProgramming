template<typename T_iterable>
void print_list(const T_iterable &_iterable, const bool _space = true, const bool _new_line = true, int _start = -1, int _end = -1) {
if (_start == -1) _start = 0;
if (_end == -1) _end = int(_iterable.size());

    for (int i = _start; i < _end; i++) {
        std::cout << iterable[i];
        
        if (_space) std::cout << ' ';
    }    
        if (_new_line)
            std::cout << '\n';
        else 
            std::cout << ' ';
}