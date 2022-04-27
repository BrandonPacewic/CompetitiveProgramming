# Type Size Reference

### Integer Types

| Type | Size in Bytes | Minimum Value | Maximum Value |
| ---- | ------------- | ------------- | ------------- |
| int_16 | 16 | -32768 | 32767 |
| uint_16 | 16 | 0 | 65535 |
| int_32 | 32 | -2147483648 | 2147483647 |
| uint_32 | 32 | 0 | 4294967295 |
| int_64 | 64 | -9223372036854775808 | 9223372036854775807 |
| uint_64 | 64 | 0 | 18446744073709551615 |

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
