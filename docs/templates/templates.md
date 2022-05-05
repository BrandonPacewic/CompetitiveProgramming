# [C++ Templates](https://github.com/BrandonPacewic/CompetitiveProgramming/tree/mega/templates)

The templates that I use for contests are pretty straight forward.
They combine the dbg `test(...)` macro with including lots and lots of 
library headers.

I prefer not to use the include all headers macro.

```cpp
#include <bits/stdc++.h>
```

Mainly because I want to know what each of the libraries do, and what code
comes from where. I think that it is totally fine to include all libraries if
you want but I want to keep the knowledge of what each library does.

The next thing to discuss is `namespace std`.

```cpp
using namespace std;
```

You will notice that all of my templates, except for the blank template, 
are using `namespace std`, however they all have the `std::` syntax anyways.
I want people to be able to take my code and use it regardless of if the want
to use the `std::` syntax or not. It's only there because when I am in a contest
I want to save the time of typing `std::`. Most of that code is problem specific
and I don't expect most people to want to use it.