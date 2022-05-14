# `uniform_matrix` Class

The `uniform_matrix` C++ Brandon Competitive Programming Library class describes
an object that controls a two dimensional matrix of type `Ty` with a
uniform size of `n` by `n`. There is no way to dynamically resize this class.

## Syntax

```cpp
template <class Ty>
class uniform_matrix;
```

### Parameters

`Ty`\
The type of element

## Members

| Type Definition | Description |
| --------------- | ----------- |
| [`row_type`](#row_type) | A type that represents a row of the matrix, limited to [`_uniform_matrix_row`](#_uniform_matrix_row). |
| [`row_pointer`](#row_pointer) | The type of a pointer to a [`row_type`](#row_type) element. |
| [`row_const_pointer`](#row_const_pointer) | The type of a constant pointer to a [`row_type`](#row_type) element. |
| [`type_pointer`](#type_pointer) | The type of a pointer to an element inside [`row_type`](#row_type). |
| [`type_const_pointer`](#type_const_pointer) | The type of a constant pointer to an element inside [`row_type`](#row_type). |
| [`row_reference`](#row_reference) | The type of a reference to a [`row_type`](#row_type) element. |
| [`row_const_reference`](#row_const_reference) | The type of a constant reference to a [`row_type`](#row_type) element. |
| [`type_reference`](#type_reference) | The type of a reference to an element inside [`row_type`](#row_type). |
| [`type_const_reference`](#type_const_reference) | The type of a constant reference to an element inside [`row_type`](#row_type). |
| [`size_type`](#size_type) | The type of an unsigned distance between two elements. |
| [`value_type`](#value_type) | The type of an element. |

| Member Function | Description |
| ---------------- | ----------- |
| [`uniform_matrix`](#uniform_matrix) | Constructs a new `uniform_matrix` object. |
| [`any_of`](#any_of) | Returns **`true`** when a condition is present in at least once in the complete range of elements.  |
| [`all_of`](#all_of) | Returns **`true`** when a condition is present in all positions in the complete range of elements. |
| [`none_of`](#none_of) | Returns **`true`** when a condition is not present at all in the complete range of elements. |
| [`count`](#count) | Returns the number of elements in the matrix that satisfy the condition. |
| [`count_if`](#count_if) | Returns the number of elements in the matrix that satisfy the condition. |
| [`fill`](#fill) | Fills the matrix with a value. |
| [`fill_if`](#fill_if) | Fills the matrix with a value if the position condition is satisfied. |
| [`find_if`](#find_if) | Returns the first element in the matrix that satisfies the condition. |
| [`for_each`](#for_each) | Applies a function to each element in the matrix. |
| [`iota`](#iota) | Fills the matrix with a sequence of values starting at **`start`**. |
| [`is_sorted`](#is_sorted) | Returns **`true`** when the complete matrix is sorted. |
| [`output`](#output) | Outputs the matrix to a specifyed output stream. |
| [`rows_sorted`](#rows_sorted) | Returns **`true`** when the each row in the matrix is sorted. |
| [`sort`](#sort) | Sorts the complete matrix. |
| [`sort_rows`](#sort_rows) | Sorts each row in the matrix individually. |

| Operator | Description |
| -------- | ----------- |
| [`uniform_matrix::operator[]`](#uniform_matrix::operator[]) | Accesses an element at a specified position. |

## Remarks

To access an element at a specified position, use the `[][]` syntax.

```cpp
uniform_matrix<int> m(3, 3);
auto m_element = m[1][2];
```

Creates an object `m` that holds `3` by `3` values, initialized to `3`.
assignes the value of `m_element` to the element at position `(1, 2)` in `m`.

## <a name="requirements"></a> Requirments

**Headers:** `<algorithm>`, `<cstddef>`, `<functional>`, `<iostream>`, `<memory>`

**Namespaces:** None

**Other Classes:** [`_uniform_matrix_row`](#_uniform_matrix_row)

## <a name="uniform_matrix"></a> `uniform_matrix::uniform_matrix`

Constructs an new `uniform_matrix` object.

```cpp
uniform_matrix(size_type _n);

uniform_matrix(size_type _n, const value_type& _value);
```

### Parameters

*`_n`*\
The size of the matrix.

*`_value`*\
The base value to initialize the matrix with.

### Remarks

It is not valid to construct a `uniform_matrix` object with an undefined size
as there is no way to redefine the size of `uniform_matrix` in any way.

### Example

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_constructor.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with all elements initialized to 3.
    uniform_matrix<int> m(3, 3);

    // Construct a 6 by 6 matrix with all elements initialized to 0.
    uniform_matrix<int> m(6, 0);

    // Construct a 10 by 10 matrix with no elements initialized.
    uniform_matrix<int> m(10);
}
```

## <a name="any_of"></a> `uniform_matrix::any_of`

Returns **`true`** when a condition is present at least once in the complete
range of elements inside the matrix.

```cpp
template <class UnaryPredicate>
bool any_of(UnaryPredicate predicate) const;
```

### Parameters

*`predicate`*\
A condition to test for. This is provided by a user-defined predicate function 
object. The predicate defines the condition to be satisfied by the element being 
tested. A unary predicate takes a single argument and returns **`true`** or 
**`false`**.

### Return value

Returns **`true`** if the condition is present at least once in the complete 
range of elements inside the matrix else **`false`**.

### Remarks

There is no way to restrict the range of the elements to be tested. If you need
this functionality, use a [`for_each`](#for_each) loop instead.

### Example

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_any_of.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with all elements initialized to 3.
    uniform_matrix<int> m1(3, 3);

    // Construct a 6 by 6 matrix with all elements initialized to 0.
    uniform_matrix<int> m2(6, 0);

    // Construct a 10 by 10 matrix with no elements initialized.
    uniform_matrix<int> m3(10);

    // Test if any element in the matrix m1 is greater than 5.
    if (m1.any_of([](int x) { return x > 5; })) {
        std::cout << "At least one element in the matrix is greater than 5.\n";
    } else {
        std::cout << "No element in the matrix is greater than 5.\n";
    }

    // Test if any element in the matrix m2 is greater than 5.
    if (m2.any_of([](int x) { return x > 5; })) {
        std::cout << "At least one element in the matrix is greater than 5.\n";
    } else {
        std::cout << "No element in the matrix is greater than 5.\n";
    }

    // Test if any element in the matrix m3 is greater than 5.
    if (m3.any_of([](int x) { return x > 5; })) {
        std::cout << "At least one element in the matrix is greater than 5.\n";
    } else {
        std::cout << "No element in the matrix is greater than 5.\n";
    }

    return 0;
}
```

```Output
At least one element in the matrix is greater than 5.
No element in the matrix is greater than 5.
No element in the matrix is greater than 5.
```

## <a name="all_of"></a> `uniform_matrix::all_of`

Returns **`true`** when a condition is present at all the values in the complete
range of elements inside the matrix.

```cpp
template <class UnaryPredicate>
bool all_of(UnaryPredicate predicate) const;
```

### Parameters

*`predicate`*\
A condition to test for. This is provided by a user-defined predicate function 
object. The predicate defines the condition to be satisfied by the element being 
tested. A unary predicate takes a single argument and returns **`true`** or 
**`false`**.

### Return value

Returns **`true`** if the condition is present at all the values in the complete
range of elements inside the matrix else **`false`**.

### Remarks

There is no way to restrict the range of the elements to be tested. If you need
this functionality, use a [`for_each`](#for_each) loop instead.

The following example also includes an example implementation of the [`iota`](#iota) 
class function.

### Example

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_all_of.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with no elements initialized.
    uniform_matrix<int> m1(3);
    m1.iota(0);

    // Construct a 6 by 6 matrix with no elements initialized.
    uniform_matrix<int> m2(6);
    m2.iota(3);

    // Construct a 10 by 10 matrix with no elements initialized.
    uniform_matrix<int> m3(10);
    m3.iota(5);

    // Test if all elements in the matrix m1 are greater than 5.
    if (m1.all_of([](int x) { return x > 5; })) {
        std::cout << "All elements in the matrix are greater than 5.\n";
    } else {
        std::cout << "Not all elements in the matrix are greater than 5.\n";
    }

    // Test if all elements in the matrix m2 are greater than 3.
    if (m2.all_of([](int x) { return x > 3; })) {
        std::cout << "All elements in the matrix are greater than 3.\n";
    } else {
        std::cout << "Not all elements in the matrix are greater than 3.\n";
    }

    // Test if all elements in the matrix m3 are less than 5.
    if (m3.all_of([](int x) { return x < 5; })) {
        std::cout << "All elements in the matrix are less than 5.\n";
    } else {
        std::cout << "Not all elements in the matrix are less than 5.\n";
    }

    return 0;
}
```

```Output
All elements in the matrix are greater than 5.
All elements in the matrix are greater than 3.
Not all elements in the matrix are less than 5.
```

## <a name="none_of"></a> `uniform_matrix::none_of`

Returns **`true`** when a condition is not present at all the values in the
complete range of elements inside the matrix.

```cpp
template <class UnaryPredicate>
bool none_of(UnaryPredicate predicate) const;
```

### Parameters

*`predicate`*\
A condition to test for. This is provided by a user-defined predicate function
object. The predicate defines the condition to be satisfied by the element being
tested. A unary predicate takes a single argument and returns **`true`** or
**`false`**.

### Return value

Returns **`true`** if the condition is not present at all the values in the
complete range of elements inside the matrix else **`false`**.

### Remarks

This class function is the inverse of the [`any_of`](#any_of) class function.

There is no way to restrict the range of the elements to be tested. If you need
this functionality, use a [`for_each`](#for_each) loop instead.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_none_of.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with all elements initialized to 3.
    uniform_matrix<int> m1(3, 3);

    // Construct a 6 by 6 matrix with all elements initialized to 0.
    uniform_matrix<int> m2(6, 0);

    // Construct a 10 by 10 matrix with no elements initialized.
    uniform_matrix<int> m3(10);

    // Test if none of the elements in the matrix m1 are greater than 5.
    if (m1.none_of([](int x) { return x > 5; })) {
        std::cout << "None of the elements in the matrix are greater than 5.\n";
    } else {
        std::cout << "At least one element in the matrix is greater than 5.\n";
    }

    // Test if none of the elements in the matrix m2 are greater than 5.
    if (m2.none_of([](int x) { return x > 5; })) {
        std::cout << "None of the elements in the matrix are greater than 5.\n";
    } else {
        std::cout << "At least one element in the matrix is greater than 5.\n";
    }

    // Test if none of the elements in the matrix m3 are greater than 5.
    if (m3.none_of([](int x) { return x > 5; })) {
        std::cout << "None of the elements in the matrix are greater than 5.\n";
    } else {
        std::cout << "At least one element in the matrix is greater than 5.\n";
    }

    return 0;
}
```

```Output
None of the elements in the matrix are greater than 5.
None of the elements in the matrix are greater than 5.
At least one element in the matrix is greater than 5.
```

## <a name="count"></a> `uniform_matrix::count`

Returns the number of elements in the matrix that satisfy a condition.

```cpp
size_type count(const value_type& value) const;

template <class UnaryPredicate>
size_type count(UnaryPredicate predicate) const;
```

### Parameters

*`value`*\
The value to test for. Must be of equal type to the elements in the matrix.

*`predicate`*\
A condition to test for. This is provided by a user-defined predicate function 
object. The predicate defines the condition to be satisfied by the element being 
tested. A unary predicate takes a single argument and returns **`true`** or 
**`false`**.

### Return value

Returns the count of the number of elements in the matrix that satisfy the
condition. Of type [`size_type`](#size_type).

### Remarks

It is possible for the return value of [`size_type`](#size_type) to overflow
in the same way that [`total_size`](#total_size) can.

It is not possible to restrict the range of the elements to be tested. If you
need this functionality, use a [`for_each`](#for_each) loop instead.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_count.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with all elements initialized to 3.
    uniform_matrix<int> m1(3, 3);

    // Construct a 6 by 6 matrix with all elements initialized to 0.
    uniform_matrix<int> m2(6, 0);

    // Construct a 10 by 10 matrix with no elements initialized.
    uniform_matrix<int> m3(10);

    // Count the number of elements in the matrix m1 that are greater than 5.
    std::cout << "The number of elements in m1 that are greater than 5 is "
              << m1.count(5) << ".\n";
        
    // Count the number of elements in the matrix m2 that are greater than 5.
    std::cout << "The number of elements in m2 that are greater than 5 is "
              << m2.count(5) << ".\n";

    // Count the number of elements in the matrix m3 that are greater than 5.
    std::cout << "The number of elements in m3 that are greater than 5 is "
              << m3.count(5) << ".\n";

    return 0;
}
```

```Output
The number of elements in m1 that are greater than 5 is 0.
The number of elements in m2 that are greater than 5 is 0.
The number of elements in m3 that are greater than 5 is 0.
```

## <a name="fill"></a> `uniform_matrix::fill`

Assigns a value to all the elements in the matrix, to all current elements
that satisfy the condition.

```cpp
void fill(const value_type& value);

template <class UnaryPredicate>
void fill(const value_type&, UnaryPredicate predicate);
```

### Parameters

*`value`*\
The value to assign to all elements in the matrix. Must be of equal type to the
elements in the matrix.

*`predicate`*\
A condition to test for. This is provided by a user-defined predicate function
object. The predicate defines the condition to be satisfied by the element being
tested. A unary predicate takes a single argument and returns **`true`** or
**`false`**.

### Remarks

New value will be assigned to an element if the *`predicate`* returns **`true`** 
for said element.

If you need to assign a value baised off matrix position use a [`fill_if`](#fill_if)
class function instead.

The following example also includes an implementation of the [`output`](#output)
class function.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_fill.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with all elements initialized to 3.
    uniform_matrix<int> m1(3, 3);

    // Construct a 6 by 6 matrix with all elements initialized to 0.
    uniform_matrix<int> m2(6, 0);

    // Construct a 10 by 10 matrix with no elements initialized.
    uniform_matrix<int> m3(10);
    m3.iota(1);

    // Fill the matrix m1 with the value 5.
    m1.fill(5);

    // Fill the matrix m2 with the value 5 if the element is greater than 5.
    m2.fill(5, [](int x) { return x > 5; });

    // Fill the matrix m3 with the value 5 if the element is greater than 5.
    m3.fill(5, [](int x) { return x > 5; });

    // Output the matrix m1.
    std::cout << "m1 = \n";
    m1.output();

    // Output the matrix m2.
    std::cout << "m2 = \n";
    m2.output();

    // Output the matrix m3.
    std::cout << "m3 = \n";
    m3.output();

    return 0;
}
```

```Output
m1 = 
5 5 5
5 5 5
5 5 5
m2 = 
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
m3 = 
1 2 3 4 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5
```

## <a name="fill_if"></a> `uniform_matrix::fill_if`

Fills the matrix with a value if the positional predicate is satisfied.

```cpp
template <class BinaryPredicate>
void fill_if(const value_type& value, BinaryPredicate predicate);
```

### Parameters

*`value`*\
The value to assign to all elements in the matrix. Must be of equal type to the
elements in the matrix.

*`predicate`*\
A condition to test for. This is provided by a user-defined predicate function
object. The predicate defines the condition to be satisfied by the position being
tested. A binary predicate takes two arguments and returns **`true`** or
**`false`**.

### Remarks

Because the *`predicate`* is positional the range of the elements to be filled
can be restricted. This removes any need of a range based `fill_if` class 
function.

The following example also includes an implementation of the [`output`](#output)
class function as well as the [`for_each`](#for_each) class function.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_fill_if.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with all elements initialized to 3.
    uniform_matrix<int> m1(3, 3);

    // Construct a 6 by 6 matrix with all elements initialized to 0.
    uniform_matrix<int> m2(6, 0);

    // Construct a 10 by 10 matrix with no elements initialized.
    uniform_matrix<int> m3(10);

    // Fill m3 with values from 0 to 9.
    uint8_t current_value = 0;
    m3.for_each([&](auto& element) {
        element = current_value, ++current_value;

        if (current_value >= 10) {
            current_value = 0;
        }
    });

    // Fill the matrix m1 with the value 5 if the element is in the first or 
    // last row.
    m1.fill_if(5, [&](auto& x, auto& y) { 
        return y == 0 || y == m1.size() - 1; 
    });

    // Fill the matrix m2 with the value 2 if the element is in the middle two
    // columns.
    m2.fill_if(2, [&](auto& x, auto& y) { 
        return x >= 2 && x < m2.size() - 2; 
    });

    // Fill the matrix m3 with the value 3 if the element is in the middle 
    // two rows.
    m3.fill_if(3, [&](auto& x, auto& y) { 
        return y >= 2 && y < m3.size() - 2; 
    });

    // Output the matrix m1.
    std::cout << "m1 = \n";
    m1.output();

    // Output the matrix m2.
    std::cout << "m2 = \n";
    m2.output();

    // Output the matrix m3.
    std::cout << "m3 = \n";
    m3.output();

    return 0;
}
```

```Output
m1 = 
5 3 5
5 3 5
5 3 5
m2 = 
0 0 0 0 0 0
0 0 0 0 0 0
2 2 2 2 2 2
2 2 2 2 2 2
0 0 0 0 0 0
0 0 0 0 0 0
m3 = 
0 1 3 3 3 3 3 3 8 9
0 1 3 3 3 3 3 3 8 9
0 1 3 3 3 3 3 3 8 9
0 1 3 3 3 3 3 3 8 9
0 1 3 3 3 3 3 3 8 9
0 1 3 3 3 3 3 3 8 9
0 1 3 3 3 3 3 3 8 9
0 1 3 3 3 3 3 3 8 9
0 1 3 3 3 3 3 3 8 9
0 1 3 3 3 3 3 3 8 9
```

## <a name="find_if"></a> `uniform_matrix::find_if`

Returns a pointer to the first element in the matrix that satisfies the
condition or is equal to the given value.

```cpp
type_pointer find_if(const value_type& target);

template <class UnaryPredicate>
type_pointer find_if(UnaryPredicate predicate);
```

### Parameters

*`target`*\
The value to test for. Must be of equal type to the elements in the matrix.

*`predicate`*\
A condition to test for. This is provided by a user-defined predicate function
object. The predicate defines the condition to be satisfied by the position being
tested. A unary predicate takes one argument and returns **`true`** or
**`false`**.

### Return value

Returns a pointer to the first element in the matrix that satisfies the
condition or is equal to the given value. If no such element is found, a pointer
to the end of the last row is returned.

### Remarks

There is no way to restrict the range of the elements to be tested.
If you require this functionality, use the [`for_each`](#for_each) class function
instead.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_find_if.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with all elements initialized to 3.
    uniform_matrix<int> m1(3, 3);

    // Construct a 6 by 6 matrix with all elements initialized to 0.
    uniform_matrix<int> m2(6, 0);

    // Construct a 10 by 10 matrix with no elements initialized.
    uniform_matrix<int> m3(10);

    // Fill m3 with values from 0 to 9.
    uint8_t current_value = 0;
    m3.for_each([&](auto& element) {
        element = current_value, ++current_value;

        if (current_value >= 10) {
            current_value = 0;
        }
    });

    // Find the first element in m1 that is equal to 5.
    auto found_element = m1.find_if(5);
    if (found_element != m1.end()->end()) {
        std::cout << "Found element: " << *found_element << 
            "\n at adress: " << found_element << '\n';
    } else {
        std::cout << "Element not found." << std::endl;
    }

    // Find the first element in m2 that is equal to 2.
    found_element = m2.find_if(2);
    if (found_element != m2.end()->end()) {
        std::cout << "Found element: " << *found_element << 
            "\n at adress: " << found_element << '\n';
    } else {
        std::cout << "Element not found." << std::endl;
    }

    // Find the first element in m3 that is equal to 3.
    found_element = m3.find_if(3);
    if (found_element != m3.end()->end()) {
        std::cout << "Found element: " << *found_element << 
            "\n at adress: " << found_element << '\n';
    } else {
        std::cout << "Element not found." << std::endl;
    }

    return 0;
}
```

```Output
Element not found.
Element not found.
Found element: 3
 at adress: 0x55874a50219c
```


## <a name="for_each"></a> `uniform_matrix::for_each`

Applies a function to each element in the matrix.

```cpp
void for_each(std::function<void(value_type&)> function);

void for_each(std::function<void(value_type&, size_type&, size_type&)> function);
```

### Parameters

*`function`*\
A function object that is called for each element in the matrix. The function
comes in two forms. The first form takes one argument *`value_type`* the current
element in the matrix. The second form takes three arguments, *`value_type`*,
*`size_type`*, and *`size_type`*. The first argument is the current element in
the matrix. The second argument is the row index of the current element. The
third argument is the column or cell index of the current element.

### Remarks

Most of the class functions provided by the `uniform_matrix` class can easily be
recreated by using the `for_each` class function. If you encounter a situation
where a class function does not provide the needed functionality, you can use
the `for_each` class function as a fallback.

The following example also includes an example implementation of the [`output`](#output)
class function.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_for_each.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

#include <stdlib.h>     // srand, rand
#include <time.h>       // time

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with no elements initialized.
    uniform_matrix<int> m1(3);

    // Construct a 6 by 6 matrix with no elements initialized.
    uniform_matrix<int> m2(6);

    // Construct a 8 by 8 matrix with all elements initialized to 3.
    uniform_matrix<int> m3(8, 3);

    // Fill m1 with random values from 0 to 9.
    srand(time(NULL));
    m3.for_each([&](auto& element) {
        element = rand() % 10;
    });
    
    // Copy m1 to m2 except for values equal to 3 and 4, set those to 0.
    m2.for_each([&](auto& element, auto& row, auto& column) {
        if (m3[row][column] == 3 || m3[row][column] == 4) {
            element = 0;
        } else {
            element = m3[row][column];
        }
    });

    // Sum all of the elements in m3 except for the last row.
    uniform_matrix<int>::size_type sum = 0;
    m3.for_each([&](auto& element, auto& row, auto& column) {
        if (row != m3.size() - 1) {
            sum += element;
        }
    });

    // Print the results.
    std::cout << "m1:\n";
    m1.output();
    std::cout << "m2:\n";
    m2.output();
    std::cout << "Sum of m3: " << sum << '\n';

    return 0;
}
```

```Output
m1:
9 1 4
5 4 6
6 2 9
m2:
9 1 0
5 0 6
6 2 9
Sum of m3: 168
```

## <a name="iota"></a> `uniform_matrix::iota`

Fills the matrix with a sequence of values starting at **`start`** and increasing
by `1`.

```cpp
void iota(value_type start);
```

### Parameters

*`start`*\
The value to start the sequence at.

### Remarks

Extreamly simple implementation. As explained in [`for_each`](#for_each), any
missing functionality can be easily recreated by using the [`for_each`](#for_each)
class function instead.

The following example also includes an example implementation of the [`output`](#output)
class function.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_iota.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with no elements initialized.
    uniform_matrix<int> m1(3);

    // Construct a 6 by 6 matrix with no elements initialized.
    uniform_matrix<int> m2(6);

    // Construct a 8 by 8 matrix with no elements initialized.
    uniform_matrix<int> m3(8);

    // Fill m1 with the sequence of values starting at 0.
    m1.iota(0);

    // Fill m2 with the sequence of values starting at -9.
    m2.iota(-9);

    // Fill m3 with the sequence of values starting at 100.
    m3.iota(100);

    // Print the results.
    std::cout << "m1:\n";
    m1.output();
    std::cout << "m2:\n";
    m2.output();
    std::cout << "m3:\n";
    m3.output();

    return 0;
}
```

```Output
m1:
0 1 2
3 4 5
6 7 8
m2:
-9 -8 -7 -6 -5 -4
-3 -2 -1 0 1 2
3 4 5 6 7 8
9 10 11 12 13 14
15 16 17 18 19 20
21 22 23 24 25 26
m3:
100 101 102 103 104 105 106 107
108 109 110 111 112 113 114 115
116 117 118 119 120 121 122 123
124 125 126 127 128 129 130 131
132 133 134 135 136 137 138 139
140 141 142 143 144 145 146 147
148 149 150 151 152 153 154 155
156 157 158 159 160 161 162 163
```

## <a name="is_sorted"></a> `uniform_matrix::is_sorted`

Return **`true`** if the matrix is sorted in ascending order.

```cpp
bool is_sorted() const;

template <class BinaryPredicate>
bool is_sorted(BinaryPredicate predicate) const;
```

### Parameters

*`predicate`*\
A binary predicate function object that returns **`true`** if the first
argument is less than or equal to the second argument. The default
predicate is **`std::less<value_type>`**.

### Return value

Returns **`true`** if the matrix is sorted in ascending order according to the
`predicate` function object or the `std::less<value_type>` predicate else **`false`**.

### Remarks

This class function tests if the whole matrix is sorted, if you only want to check
if the rows of the matrix are sorted, use the [`rows_sorted`](#rows_sorted) class
function instead.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_is_sorted.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with no elements initialized.
    uniform_matrix<int> m1(3);

    // Construct a 6 by 6 matrix with no elements initialized.
    uniform_matrix<int> m2(6);

    // Construct a 4 by 4 matrix with no elements initialized.
    uniform_matrix<int> m3(4);

    // Fill m1 with the sequence of values starting at 0.
    m1.iota(0);

    // Fill m2 with the sequence of values starting at -9.
    m2.iota(-9);

    // Fill m3 with the sequence of values starting at 100.
    m3.iota(100);

    // Replace the last element of m1 with -1.
    m1.back().back() = -1;

    // Print the results.
    std::cout << "m1:\n";
    m1.output();
    std::cout << "m2:\n";
    m2.output();
    std::cout << "m3:\n";
    m3.output();

    // Test if m1 is sorted.
    std::cout << "m1 is sorted: " << m1.is_sorted() << '\n';

    // Test if m2 is sorted.
    std::cout << "m2 is sorted: " << m2.is_sorted() << '\n';

    // Test if m3 is sorted.
    std::cout << "m3 is sorted: " << m3.is_sorted() << '\n';

    return 0;
}
```

```Output
m1:
0 1 2
3 4 5
6 7 -1
m2:
-9 -8 -7 -6 -5 -4
-3 -2 -1 0 1 2
3 4 5 6 7 8
9 10 11 12 13 14
15 16 17 18 19 20
21 22 23 24 25 26
m3:
100 101 102 103
104 105 106 107
108 109 110 111
112 113 114 115
m1 is sorted: 0
m2 is sorted: 1
m3 is sorted: 1
```

## <a name="output"></a> `uniform_matrix::output`

Outputs the whole matrix to a specifyed output stream.

```cpp
void output(const bool& space = true) const;

void output(std::ostream& os) const;
```

### Parameters

*`space`*\
If **`true`**, a space is inserted between each element.

*`os`*\
The output stream to write to.

### Remarks

There is no way to restrict the output to a specific range of the matrix or
change the output stream and the format of the output at the same time. If this
is functionality is needed, use the [`for_each`](#for_each) class function instead.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_output.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with no elements initialized.
    uniform_matrix<int> m(3);

    // Fill m1 with the sequence of values starting at 0.
    m.iota(0);

    // Print the results.
    std::cout << "m:\n";
    m.output();

    return 0;
}
```

```Output
m1:
0 1 2
3 4 5
6 7 8
```

## <a name="rows_sorted"></a> `uniform_matrix::rows_sorted`

Returns **`true`**  all rows of the matrix are sorted in ascending order.

```cpp
bool rows_sorted() const;

template <class BinaryPredicate>
bool rows_sorted(BinaryPredicate predicate) const;
```

### Parameters

*`predicate`*\
A binary predicate function object that returns **`true`** if the first
argument is less than or equal to the second argument. The default
predicate is **`std::less<value_type>`**.

### Return value

Returns **`true`** if all rows of the matrix are sorted in ascending order 
according to the `predicate` function object or the `std::less<value_type>`
predicate else **`false`**.

### Remarks

This class function does not test if the whole matrix is sorted only if all of
the rows are. If you are looking for this functionality, use the [`is_sorted`](#is_sorted)
class function instead.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_rows_sorted.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with no elements initialized.
    uniform_matrix<int> m1(3);

    // Construct a 6 by 6 matrix with no elements initialized.
    uniform_matrix<int> m2(6);

    // Construct a 4 by 4 matrix with no elements initialized.
    uniform_matrix<int> m3(4);

    // Fill m1 with the sequence of values starting at 0.
    m1.iota(0);

    // Fill m2 with the sequence of values starting at -9.
    m2.iota(-9);
    // Set the first element of m2 to 100.
    m2[0][0] = 100;

    // Fill m3 with the sequence of values starting at 100.
    m3.iota(1);

    // Fill m3's second row with a sequence of values starting at 100.
    std::iota(m3[1].begin(), m3[1].end(), 100);

    // Print the results.
    std::cout << "m1:\n";
    m1.output();
    std::cout << "m2:\n";
    m2.output();
    std::cout << "m3:\n";
    m3.output();

    // Test if m1 has sorted rows.
    std::cout << "m1 has sorted rows: " << m1.rows_sorted() << '\n';

    // Test if m2 has sorted rows.
    std::cout << "m2 has sorted rows: " << m2.rows_sorted() << '\n';

    // Test if m3 has sorted rows.
    std::cout << "m3 has sorted rows: " << m3.rows_sorted() << '\n';

    return 0;
}
```

```Output
m1:
0 1 2
3 4 5
6 7 8
m2:
100 -8 -7 -6 -5 -4
-3 -2 -1 0 1 2
3 4 5 6 7 8
9 10 11 12 13 14
15 16 17 18 19 20
21 22 23 24 25 26
m3:
1 2 3 4
100 101 102 103
9 10 11 12
13 14 15 16
m1 has sorted rows: 1
m2 has sorted rows: 0
m3 has sorted rows: 1
```

## <a name="sort"></a> `uniform_matrix::sort`

Sorts the complete range of elements in the matrix.

```cpp
void sort();

template <class BinaryPredicate>
void sort(BinaryPredicate predicate);
```

### Parameters

*`predicate`*\
A binary predicate function object that returns **`true`** if the first
argument is less than or equal to the second argument. The default
predicate is **`std::less<value_type>`**.

### Remarks

This class function does not sort the whole matrix if you only want to sort the
individual rows, use the [`sort_rows`](#sort_rows) class function instead.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_sort.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with no elements initialized.
    uniform_matrix<int> m1(3);

    // Construct a 6 by 6 matrix with no elements initialized.
    uniform_matrix<int> m2(6);

    // Construct a 4 by 4 matrix with no elements initialized.
    uniform_matrix<int> m3(4);

    // Fill m1 with the sequence of values starting at 0.
    m1.iota(0);

    // Fill m2 with the sequence of values starting at -9.
    m2.iota(-9);
    // Set the first element of m2 to 100.
    m2[0][0] = 100;

    // Fill m3 with the sequence of values starting at 100.
    m3.iota(1);

    // Fill m3's second row with a sequence of values starting at 100.
    std::iota(m3[1].begin(), m3[1].end(), 100);

    // Sort m1.
    m1.sort();

    // Sort m2.
    m2.sort();

    // Sort m3.
    m3.sort();

    // Print the results.
    std::cout << "m1:\n";
    m1.output();
    std::cout << "m2:\n";
    m2.output();
    std::cout << "m3:\n";
    m3.output();

    return 0;
}
```

```Output
m1:
0 1 2
3 4 5
6 7 8
m2:
-8 -7 -6 -5 -4 -3
-2 -1 0 1 2 3
4 5 6 7 8 9
10 11 12 13 14 15
16 17 18 19 20 21
22 23 24 25 26 100
m3:
1 2 3 4
9 10 11 12
13 14 15 16
100 101 102 103
```

## <a name="sort_rows"></a> `uniform_matrix::sort_rows`

Sorts each individual row of the matrix separately.

```cpp
void sort_rows();

template <class BinaryPredicate>
void sort_rows(BinaryPredicate predicate);
```

### Parameters

*`predicate`*\
A binary predicate function object that returns **`true`** if the first
argument is less than or equal to the second argument. The default
predicate is **`std::less<value_type>`**.

### Remarks

If you want to sort the whole matrix, use the [`sort`](#sort) class function
instead.

```cpp
// Example authored by Brandon Pacewic
// uniform_matrix_sort_rows.cc
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

template <class Ty>
class _uniform_matrix_row;

template <class Ty>
class uniform_matrix;

int main() {
    // Construct a 3 by 3 matrix with no elements initialized.
    uniform_matrix<int> m1(3);

    // Construct a 6 by 6 matrix with no elements initialized.
    uniform_matrix<int> m2(6);

    // Construct a 4 by 4 matrix with no elements initialized.
    uniform_matrix<int> m3(4);

    // Fill m1 with the sequence of values starting at 0.
    m1.iota(0);

    // Fill m2 with the sequence of values starting at -9.
    m2.iota(-9);
    // Set the first element of m2 to 100.
    m2[0][0] = 100;

    // Fill m3 with the sequence of values starting at 100.
    m3.iota(1);

    // Fill m3's second row with a sequence of values starting at 100.
    std::iota(m3[1].begin(), m3[1].end(), 100);

    // Sort m1's rows.
    m1.sort_rows();

    // Sort m2's rows.
    m2.sort_rows();

    // Sort m3's rows.
    m3.sort_rows();

    // Print the results.
    std::cout << "m1:\n";
    m1.output();
    std::cout << "m2:\n";
    m2.output();
    std::cout << "m3:\n";
    m3.output();

    return 0;
}
```

```Output
m1:
0 1 2
3 4 5
6 7 8
m2:
-8 -7 -6 -5 -4 100
-3 -2 -1 0 1 2
3 4 5 6 7 8
9 10 11 12 13 14
15 16 17 18 19 20
21 22 23 24 25 26
m3:
1 2 3 4
100 101 102 103
9 10 11 12
13 14 15 16
```

## Closing remarks

Most class functions are designed to mimic simmilary standard library `<algorithm>'
functions, and are modifyed to work with a two dimensional container. Any missing
functionality can be obtained by using a [`for_each`](#for_each) function.

# <a name="_uniform_matrix_row"></a> `_uniform_matrix_row` class (Brandon C++ Competitive Programming Library)

Describes the inner row object of the [`uniform_matrix`](#uniform_matrix) class.

## Syntax

```cpp
template <class Ty>
class _uniform_matrix_row;
```

### Parameters

`ty`\
The type of the elements in the row.

## Members

| Type Definition | Description |
|----------------|-------------|
| [`value_type`](#value_type) | The type of the elements in the row. |
| [`pointer`](#pointer) | The type of a pointer to a element. |
| [`const_pointer`](#const_pointer) | The type of a pointer to a const element. |
| [`reference`](#reference) | The type of a reference to a element. |
| [`const_reference`](#const_reference) | The type of a reference to a const element. |
| [`size_type`](#size_type) | The type of the size of the row. |

| Member Function | Description |
|----------------|-------------|
| [`back`](#back) | Returns a reference to the last element of the row. |
| [`begin`](#begin) | Returns a pointer to the first element of the row. |
| [`end`](#end) | Returns a pointer to the element after the last element of the row. |
| [`front`](#front) | Returns a reference to the first element of the row. |
| [`size`](#size) | Returns the number of elements in the row. |

| Operator | Description |
|---------|-------------|
| [`_uniform_matrix_row::operator[]`](#_uniform_matrix_row::operator[]) | Accesses an element at a specified position. |

## Remarks

**`IMPORTANT:`** This class is not meant to be used directly, never construct 
an instance of this class. Simply allow the [`uniform_matrix`](#uniform_matrix)
class to manage this class internally. The purpose of providing documentation
for this class is to provide a reference for the functions that can be called
on this class. Provided that it is stored within the [`uniform_matrix`](#uniform_matrix)
class as it was designed to be.

Constructors will not be documented, they should only be called by the 
[`uniform_matrix`](#uniform_matrix) class.

## Requirments

Requirements are identical to `uniform_matrix` [requirments](#requirments).


## <a name="back"></a> `_uniform_matrix_row::back`

Returns a reference to the last element of the row.

```cpp
typename _uniform_matrix_row<implementation-specific>::reference back() noexcept;

typename _uniform_matrix_row<implementation-specific>::const_reference back() const noexcept;
```

### Return value

Retruns a reference to the last element of the row.

### Remarks

If the return value is assigned the `_uniform_matrix_row<Ty>::reference` type,
then the object can be modified, else if the return value is assigned the
`_uniform_matrix_row<Ty>::const_reference` type, then the object cannot be modified.


## <a name="begin"></a> `_uniform_matrix_row::begin`

Returns a pointer to the frist element of the row.

```cpp
typename _uniform_matrix_row<implementation-specific>::pointer begin() noexcept;

typename _uniform_matrix_row<implementation-specific>::const_pointer begin() const noexcept;
```

### Return value

Returns a pointer to the first element of the row.

### Remarks

If the return value is assigned the `_uniform_matrix_row<Ty>::pointer` type,
then the object can be motifed, else if the return value is assigned the `_uniform_matrix_row<Ty>::const_pointer` than the object cannot be modified.

## <a name="end"></a> `_uniform_matrix_row::end`

Returns a pointer to the element after the last element of the row.

```cpp
typename _uniform_matrix_row<implementation-specific>::pointer end() noexcept;

type_name _uniform_matrix_row<implementation-specific>::const_pointer end() const noexcept;
```

### Return value

Returns a pointer to the element after the last element of the row.

### Remarks

If the return value is assigned the `_uniform_matrix_row<Ty>::pointer` type,
then the object can be modified, else if the return value is assigned the 
`_uniform_matrix_row<Ty>::const_pointer` than the object cannot be modified.

## <a name="front"></a> `_uniform_matrix_row::front`

Returns a reference to the first element of the row.

```cpp
typename _uniform_matrix_row<implementation-specific>::reference front() noexcept;

type_name _uniform_matrix_row<implementation-specific>::const_reference front() const noexcept;
```

### Return value

Returns a reference to the first element of the row.

### Remarks

If the return value is assigned the `_uniform_matrix_row<Ty>::reference` type,
then the object can be modified, else if the return value is assigned the
`_uniform_matrix_row<Ty>::const_reference` type, then the object cannot be modified.

## <a name="size"></a> `_uniform_matrix_row::size`

Returns the number of elements in the row.

```cpp
const typename _uniform_matrix_row::size_type size() const;
```

### Return value

Returns the number of elements in the row.

### Remarks

The return value of the [`row_type`](#row_type) is the same as the return value of
the [`uniform_matrix::size`](#uniform_matrix::size) function. There is no difference.

## Closing remarks

Any needed functionality that is needed from the [`_uniform_matrix_row`](#_uniform_matrix_row) class should be obtained from the standard library
using range based functions.

