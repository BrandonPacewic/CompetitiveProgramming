# `uniform_matrix` Class (Brandon C++ Competivite Programming Library)

Describes an object that controls a two dimensional matrix of type `Ty` with a
uniform size of `n` by `n`.

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
| [`row_type'](#row_type) | A type that represents a row of the matrix, limited to [`_uniform_matrix_row`](#_uniform_matrix_row). |
| ['row_pointer'](#row_pointer) | The type of a pointer to a [`row_type`](#row_type) element. |
| ['row_const_pointer'](#row_const_pointer) | The type of a constant pointer to a [`row_type`](#row_type) element. |
| ['type_pointer'](#type_pointer) | The type of a pointer to an element inside ['row_type'](#row_type). |
| ['type_const_pointer'](#type_const_pointer) | The type of a constant pointer to an element inside ['row_type'](#row_type). |
| ['row_reference'](#row_reference) | The type of a reference to a [`row_type`](#row_type) element. |
| ['row_const_reference'](#row_const_reference) | The type of a constant reference to a [`row_type`](#row_type) element. |
| ['type_reference'](#type_reference) | The type of a reference to an element inside ['row_type'](#row_type). |
| ['type_const_reference'](#type_const_reference) | The type of a constant reference to an element inside ['row_type'](#row_type). |
| ['size_type'](#size_type) | The type of an unsigned distance between two elements. |
| ['value_type`](#value_type) | The type of an element. |

| Member Function | Description |
| ---------------- | ----------- |
| ['uniform_matrix'](#uniform_matrix) | Constructs a new `uniform_matrix` object. |
| ['any_of'](#any_of) | Returns **`true`** when a condition is present at least once in the complete range of elements.  |
| ['all_of'](#all_of) | Returns **`true`** when a condition is present at all in the complete range of elements. |
| ['none_of'](#none_of) | Returns **`true`** when a condition is not present at all in the complete range of elements. |
| ['count'](#count) | Returns the number of elements in the matrix that satisfy the condition. |
| ['count_if'](#count_if) | Returns the number of elements in the matrix that satisfy the condition. |
| ['iota'](#iota) | Fills the matrix with a sequence of values starting at **`start`**. |
| ['is_sorted'](#is_sorted) | Returns **`true`** when the complete matrix is sorted. |
| ['fill'](#fill) | Fills the matrix with a value. |
| ['find_if'](#find_if) | Returns the first element in the matrix that satisfies the condition. |
| ['for_each'](#for_each) | Applies a function to each element in the matrix. |
| ['output'](#output) | Outputs the matrix to specifyed output stream. |
| ['rows_sorted'](#rows_sorted) | Returns **`true`** when the each row in the matrix is sorted. |
| ['sort'](#sort) | Sorts the complete matrix. |
| ['sort_rows'](#sort_rows) | Sorts each row in the matrix individually. |

| Operator | Description |
| -------- | ----------- |
| ['uniform_matrix::operator[]'](#uniform_matrix::operator[]) | Accesses an element at a specified position. |

## Remarks

To access an element at a specified position, use the `[][]` syntax.

```cpp
uniform_matrix<int> m(3, 3);
auto m_element = m[1][2];
```

Creates an object `m` that holds `3` by `3` values, initialized to `3`.
assignes the value of `m_element` to the element at position `(1, 2)` in `m`.

## Requirments

**Headers:** `<algorithm>`, `<cstddef>`, `<functional>`, `<iostream>`, `<memory>`

**Namespaces:** None

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
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

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
range of elements inside the matrix.

### Remarks

There is no way to restrict the range of the elements to be tested. If you need
this functionality, use a [`for_each`](#for_each) loop instead.



