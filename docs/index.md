# cpp-magic_enum-example

Experimental example for magic_enum C++ library per CMake package management.

## Download

```bash
$ git clone https://github.com/sthagen/cpp-magic_enum-example.git
```

## Development Cycle

The examples use `ninja` as build system and the build type `Release` but other build systems should equally work.

### Build

Commands:
```bash
$ cd cpp-magic_enum-example
$ cmake -DCMAKE_BUILD_TYPE=Release -GNinja -B build .
$ ninja -C build
```

Example build (assuming a macos machine and the git clone directory below `/here_below/`:
```bash
$ cd cpp-magic_enum-example
$ cmake -DCMAKE_BUILD_TYPE=Release -GNinja -B build .
cmake -DCMAKE_BUILD_TYPE=Release -GNinja -B build .
-- The CXX compiler identification is AppleClang 12.0.5.12050022
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Library/Developer/CommandLineTools/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Downloading CPM.cmake v0.27.2
-- CPM: adding package magic_enum@0.7.3 (v0.7.3)
-- CPM: adding package doctest@2020.12 (2020.12)
-- Note the fetched includes are taken from below: /here_below/cpp-magic_enum-example/build/_deps
-- Configuring done
-- Generating done
-- Build files have been written to: /here_below/cpp-magic_enum-example/build
$ ninja -C build
ninja -C build
ninja: Entering directory `build'
[4/4] Linking CXX executable magic_enum_test
```

### Test

```bash
$ ninja -C build test
ninja -C build test
ninja: Entering directory `build'
[0/1] Running tests...
Test project /here_below/cpp-magic_enum-example/build
    Start 1: magic_enum_example
1/3 Test #1: magic_enum_example ...............   Passed    0.40 sec
    Start 2: basic
2/3 Test #2: basic ............................   Passed    0.20 sec
    Start 3: custom_name
3/3 Test #3: custom_name ......................   Passed    0.15 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.76 sec
```

### Execute

Direct execution of the explicit test (only):
```bash
$ build/magic_enum_test

[doctest] doctest version is "2.4.4"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases: 13 | 13 passed | 0 failed | 0 skipped
[doctest] assertions: 28 | 28 passed | 0 failed |
[doctest] Status: SUCCESS!
```

Direct execution of the basic example app:
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
Direct execution of the custom_name example app:
```bash
$ build/examples/custom_name

the red color
The BLUE
GREEN
true
the one
Two
Three
```

### Clean

```bash
$ ninja -C build clean

ninja: Entering directory `build'
[1/1] Cleaning all built files...
Cleaning... 4 files.
```

## Status
Experimental

**Note**: The default branch is `default`.
