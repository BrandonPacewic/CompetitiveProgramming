# Type Size Reference

## Integer Types

Ranges on the following chart are inclusive.

| Type | Size in Bytes | Other Names | Minimum Value | Maximum Value |
| ---- | ------------- | ------------ | ------------- | ------------- |
| <code>int8_t</code> | 1 | none | -128 | 127 |
| <code>uint8_t</code> | 1 | none | 0 | 255 |
| <code>int16_t</code> | 2 | <code>short</code> | -32768 | 32767 |
| <code>uint16_t</code> | 2 | <code>unsigned short</code> | 0 | 65535 |
| <code>int32_t</code> | 4 | <code>int</code> | -2147483648 | 2147483647 |
| <code>uint32_t</code> | 4 | <code>unsigned int</code> | 0 | 4294967295 |
| <code>int64_t</code> | 8 | <code>long long</code> | -9223372036854775808 | 9223372036854775807 |
| <code>uint64_t</code> | 8 | <code>unsigned long long</code> | 0 | 18446744073709551615 |

GCC and Clang also support the <code>__int128</code> type.
- Size in Bytes: 16
- Minimum Value: -9223372036854775808
- Maximum Value: 9223372036854775807

As well as the <code>unsigned __int128</code> type.
- Size in Bytes: 16
- Minimum Value: 0
- Maximum Value: 18446744073709551615 

You can use these types to define your own version of these types that better
conform to the usual naming conventions.

```cpp
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;
```

Please note that the <code>short</code> and <code>long</code> types are not 
always 16-bit and 32-bit respectively. For example, in arduino, 
<code>short</code> is 8-bit, and <code>long</code> is 32-bit.

### Size Macros

```cpp
#define INT8_MIN -128
#define INT8_MAX 127
```

```cpp
#define UINT8_MAX 255
```


```cpp
#define int_16_min -32768
#define int_16_max 32767
```

```cpp
#define uint_16_max 65535
```

```cpp
#define int_32_min -2147483648
#define int_32_max 2147483647
```

```cpp
#define uint_32_max 4294967295
```

```cpp
#define int_64_min -9223372036854775808
#define int_64_max 9223372036854775807
```

```cpp
#define uint_64_max 18446744073709551615
```

```cpp
#define int_128_min -9223372036854775808
#define int_128_max 9223372036854775807
```

```cpp
#define uint_128_max 18446744073709551615
```

### int64_t vs long long

I strongly prefer the <code>int64_t</code> type over <code>long long</code>
even though in most cases they are the same. The keyword <code>long</code> can
change from system to system, and <code>int64_t</code> is guaranteed to be the
same on all systems. 

Some people like to use <code>define</code> shorten the keyword.

```cpp
#define ll long long
```

I dislike this for two reasons:
- <code>l</code> can be confused with <code>1</code>
- The problem of portability as discussed

If you really want to insist on defining <code>long long</code> as something
shorter, at least use capital ls'.

```cpp
#define LL long long
```

## Floating Point Types

Ranges on the following chart are inclusive.

| Type | Size in Bytes | Other Names | Minimum Value | Maximum Value |
| ---- | ------------- | ------------ | ------------- | ------------- |
| <code>float</code> | 4 | none | -3.402823e+38 | 3.402823e+38 |
| <code>double</code> | 8 | <code>long double</code> | -1.7976931348623157e+308 | 1.7976931348623157e+308 |

Note that <code>long double</code> and <code>double</code> are the same in most
cases, depending on the compiler.

### Size Macros

```cpp
#define float_min -3.402823e+38
#define float_max 3.402823e+38
```

```cpp
#define double_min -1.7976931348623157e+308
#define double_max 1.7976931348623157e+308
```

## Character Types

Ranges on the following chart are inclusive.

| Type | Size in Bytes | Other Names | Minimum Value | Maximum Value |
| ---- | ------------- | ------------ | ------------- | ------------- |
| <code>char</code> | 1 | <code>signed char</code> | -128 | 127 |
| <code>unsigned char</code> | 1 | <code>char8_t</code> | 0 | 255 |
| <code>wchar_t</code> | 2 | none | 0 | 65535 |
| <code>char16_t</code> | 2 | none | 0 | 65535 |
| <code>char32_t</code> | 4 | none | 0 | 4294967295 |

### Size Macros

```cpp
#define char_min -128
#define char_max 127
```

```cpp
#define uchar_max 255
```

```cpp
#define wchar_max 65535
```

```cpp
#define char16_max 65535
```

```cpp
#define char32_max 4294967295
```

## Boolean

Put very simply :)

| Type | Size in Bytes | Other Names | Minimum Value | Maximum Value |
| ---- | ------------- | ------------ | ------------- | ------------- |
| <code>bool</code> | 1 | none | 0 (false) | 1 (true) |

And just for the sake of being thorough,

```cpp
#define bool_min 0
#define bool_max 1
```
