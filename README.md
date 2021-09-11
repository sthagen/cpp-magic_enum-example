# cpp-magic_enum-example

Experimental example for magic_enum C++ library per CMake package management.

## Download

```bash
$ git clone https://github.com/sthagen/cpp-magic_enum-example.git
```

## Build

```bash
$ cd cpp-magic_enum-example
$ cmake -DCMAKE_BUILD_TYPE=Release -GNinja -B build .
$ cmake --build build
```

## Execute

Example run of the test:
```bash
$ build/magic_enum_test

[doctest] doctest version is "2.4.4"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases: 13 | 13 passed | 0 failed | 0 skipped
[doctest] assertions: 28 | 28 passed | 0 failed |
[doctest] Status: SUCCESS!
```

Example run of the basic example app:
```bash
$ build/examples/basic

RED
Color names: RED BLUE GREEN
BLUE = 0
GREEN = 10
RED = -10
Color: RED BLUE GREEN
Color enum size: 3
Color[0] = RED
Colors values: RED BLUE GREEN
5
Colors entries: RED = -10 BLUE = 0 GREEN = 10
```

## Status
Experimental

**Note**: The default branch is `default`.
