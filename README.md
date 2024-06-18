<!--
Copyright 2021 arnavyc <arnavyc@outlook.com>
SPDX-License-Identifier: 0BSD
-->

# Getdelim

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

`getdelim()` & `getline()` implementation in C.

Licensed under BSD Zero Clause License, a public-domain equivalent license.

## Table of Contents

- [Install](#install)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Install

To use `getdelim()` & `getline()` functions:

- Include this project using CMake and link your targets with CMake targets
  `getdelim::getdelim`.

- Or, copy [`include/ay/getdelim.h`](include/ay/getdelim.h) into your project
  and create a C file with following content (or just copy `src/ay/getdelim.c`
  ):

```c
#define AY_GETDELIM_IMPLEMENTATION 1
#include "Path to getdelim.h file"
```

## Usage

Refer to POSIX documentation for `getdelim()` & `getline()` functions, found
here: https://pubs.opengroup.org/onlinepubs/9699919799/functions/getdelim.html

## Contributing

Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in the work by you, shall be licensed as below, without any
additional terms or conditions.

## License

&copy; 2021 arnavyc \<arnavyc@outlook.com\>

Licensed under the Zero Clause BSD License. See [`LICENSE.md`](LICENSE.md)
file in the project root, or https://opensource.org/licenses/0BSD for full
license information.
