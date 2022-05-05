# Encoding 

## Run Length Encoding

Basic template function that condences repeated items into a pair of
the item and the number of times it appears in a row at that index.

Sample usage

```cpp
std::vector<std::pair<char, uint16_t>> encoding = run_length_encoding<char>(str);
```

Input:

```cpp
std::string str = "AAAABBBCCDAA";
```

Output:

```cpp
std::vector<std::pair<char, uint16_t>> encoding = {
    {'A', 4},
    {'B', 3},
    {'C', 2},
    {'D', 1},
    {'A', 2}};
```

Check [this](https://github.com/BrandonPacewic/CompetitiveProgramming/blob/mega/contests/google_code_jam/2022/roundA/A.cc) 
problem for a possible use case.