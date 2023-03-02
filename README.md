# tolower

Convert directories recursivly to lowercase using C++ std::filesystem and unicode-org/icu

## Downloading

```sh
git clone --recurse-submodules --recusive http://github.com/jopadan/tolower
```

## Dependencies

- [unicode-org/icu](http://github.com/unicode-org/icu)

## Building

```sh
PREFIX=[prefix] make install
```

## Usage

```c++
#include "tocase.h"

std::filesystem::path path;

/* rename path and all of its contents recursively */
path = tocase(path, std::simple_lowercase, std::filesystem::recursive);

/* rename only path and none of its contents */
path = tocase(path, std::simple_lowercase, std::filesystem::none);
```

```sh
tolower [PATH]...
```

## Credits

Jon Daniel <jondaniel879@gmail.com>
