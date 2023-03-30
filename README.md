# tocase

single-file header-only recursive unicode path case convert using icu

## Downloading

```sh
git clone --recurse-submodules --recursive http://github.com/jopadan/tocase
```

## Dependencies

- [unicode-org/icu](http://github.com/unicode-org/icu)

## Building

```sh
cmake . --install-prefix=[prefix] && make install
```

## Usage

```c++
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "tocase.h"

using namespace std;
using namespace std::filesystem;

path src = argv[1];
case_mode mode = case_mode_from_str["lower"];
traverse_mode traverse = traverse_mode::recursive;

/* rename path and all of its contents recursively */
src = tocase(src, mode, traverse_moode::recursive);
cout << src << std::endl;

/* rename only path and none of its contents */
src = tocase(src, mode, traverse_mode::none);
cout << src << std::endl;
```

```sh
g++ -std=gnu++23 -I<location of directory including tocase.h> <file.cpp> -licuuc
```

## Credits

Jon Daniel <jondaniel879@gmail.com>
