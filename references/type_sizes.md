# Type Size Reference

### Integer Types

Ranges on the following chart are inclusive.

| Type | Size in Bytes | Other Names | Minimum Value | Maximum Value |
| ---- | ------------- | ------------ | ------------- | ------------- |
| <code>int16_t</code> | 2 | <code>short</code> | -32768 | 32767 |
| <code>uint16_t</code> | 2 | <code>unsigned short</code> | 0 | 65535 |
| <code>int32_t</code> | 4 | <code>int</code> | -2147483648 | 2147483647 |
| <code>uint32_t</code> | 4 | <code>unsigned int</code> | 0 | 4294967295 |
| <code>int64_t</code> | 8 | <code>long</code> | -9223372036854775808 | 9223372036854775807 |
| <code>uint64_t</code> | 8 | <code>unsigned long</code> | 0 | 18446744073709551615 |

### Size Macros

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

### Comparison between 