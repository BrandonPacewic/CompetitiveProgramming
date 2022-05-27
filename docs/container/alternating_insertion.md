# `alternating_insertion` Function

## Requirements

**Headers:** `<algorithm>`

**Namespace:** None

## Syntax

```cpp
template <class ForwardIterator1, class ForwardIterator2, class OutputIterator>
OutputIterator alternating_insertion(
    ForwardIterator1 first1,
    ForwardIterator1 last1,
    ForwardIterator2 first2,
    ForwardIterator2 last2,
    OutputIterator result);
```

Combines two ranges into one range taking alternating elements from each range, 
without modifying the original ranges.

### Parameters

*`first1`*\ 
A forward iterator to the first element of the first range.

*`last1`*\
A forward iterator to one past the last element of the first range.

*`first2`*\
A forward iterator to the first element of the second range.

*`last2`*\
A forward iterator to one past the last element of the second range.

*`result`*\
An output iterator to the front of the resulting range.

### Return Value

An output iterator to the front of the resulting range.

### Example

```cpp
// example authored by Brandon Pacewic
#include <algorithm>
#include <iostream>
#include <vector>

template <class ForwardIterator1, class ForwardIterator2, class OutputIterator>
OutputIterator alternating_insertion();

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {6, 7, 8, 9, 10};
    std::vector<int> c = {11, 12, 13, 14, 15};
    
    // combine a and b
    std::vector<int> ab(a.size() + b.size());
    alternating_insertion(a.begin(), a.end(), b.begin(), b.end(), ab.begin());

    // print ab
    std::cout << "ab: ";
    for (const auto& i : ab) {
        std::cout << i << " ";
    }

    std::cout << '\n';

    // combine b and c
    std::vector<int> bc(b.size() + c.size());
    alternating_insertion(b.begin(), b.end(), c.begin(), c.end(), bc.begin());

    // print bc
    std::cout << "bc: ";
    for (const auto& i : bc) {
        std::cout << i << " ";
    }

    std::cout << '\n';

    // combine a and c
    std::vector<int> ac(a.size() + c.size());
    alternating_insertion(a.begin(), a.end(), c.begin(), c.end(), ac.begin());

    // print ac
    std::cout << "ac: ";
    for (const auto& i : ac) {
        std::cout << i << " ";
    }

    std::cout << '\n';

    return 0;
}
```

```Output
ab: 1 6 2 7 3 8 4 9 5 10 
bc: 6 11 7 12 8 13 9 14 10 15 
ac: 1 11 2 12 3 13 4 14 5 15 
```
