# Debug Testing Tools

The test(...) macro is used to easily visualize variables within a coding 
test. The way the current macro is set up makes it possible to use the same
macro with all variables and containers. The macro is also variadic so it can
take as many or as little inputs as you like.

```cpp
test(a, b, c);

test(a);
```

The complex looking typename standard enable if logic is just to avoid outputing
the stardard string type as a standard container as it already has a overloaded
ostream<< operator.

```cpp
template<typename T_container, typename T = typename std::enable_if
    !std::is_same<T_container, std::string>::value, 
    typename T_container::value_type>::type>
```

```cpp
std::string a = "this";

test(a);
```

#### With


```
[a]: {"this"}
```

#### Without

```
[a]: {{'t', 'h', 'i', 's'}}
```

Simply just avoids outputing the stardard string type as a standard container of
type char.

The ```ifdef``` macros are used to specify when the test macro should run.

To run the macro include the ```-D DBG_MODE``` flag when compiling.

This is done so that when submitting the code to the online judge the macro
will not be ran. Then you don't need no worry about removing or commenting the 
function calls when submitting.

Visit my Test Samples script to see the basis of my templates that all include
this macro.