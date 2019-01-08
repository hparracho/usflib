# μSF - Micro String Format
___________________________
[![Standard](https://img.shields.io/badge/c%2B%2B-11/14/17-blue.svg)](https://isocpp.org/std/the-standard)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Download](https://img.shields.io/badge/download%20%20-latest-blue.svg)](https://raw.githubusercontent.com/hparracho/usflib/master/include/usf/usf.hpp)
[![Version](https://img.shields.io/badge/version-0.1.0-brightgreen.svg)](https://github.com/hparracho/usflib/releases)
[![Build Status](https://travis-ci.org/hparracho/usflib.svg?branch=master)](https://travis-ci.org/hparracho/usflib)

μSF is a lean C++ string format library (mainly) for embedded platforms.
Its main purpose is to be a smaller, safer and faster alternative to (s)(n)printf functions adding some additional features.
The library is in its very early stages of development and its interface can (inevitably will) change at any time based on my own usage experience and any feedback / comments I get.

## Motivation
_____________
Damn... yet another formatting library???
Well, basically I have no sympathy for the (s)(n)printf functions, even less for the cumbersome IOStream's interface.
I really love the [**\{fmt\}**](http://fmtlib.net) library but it has an hefty price tag when working with targets with only a few Kb of flash and RAM.
This happens mostly because it has a **lot** of features (rarely needed in an embedded target) and also because it falls back to printf in some cases (hopefully this is still true in the latest version).

So, based on my love for the [**\{fmt\}**](http://fmtlib.net)'s format string syntax (itself similar to the one of [str.format](https://docs.python.org/3.8/library/string.html) in Python), I decided to roll my own version with a nice balance in mind between code size, execution speed and available features that made sense to my main target platforms, small embedded micro-controllers, mostly ARM Cortex-M0/3/4.

I also did it for the challenge of making it and it turned out to be more demanding than I has expecting at first...

## Features
___________
- Safe alternative to (s)(n)printf and IOStream functions.
- Ease of use: single header file library [usf.hpp](https://raw.githubusercontent.com/hparracho/usflib/master/include/usf/usf.hpp) without any external dependencies.
- Small code size: both in terms of source code (around 2500 loc) and produced binary size.
- Reliable: it has an extensive set of [unit tests](https://github.com/hparracho/usflib/tree/master/unit_tests) (*work in progress*).
- Support for positional arguments.
- Support for user-defined custom types.
- Portable and consistent across platforms and compilers.
- Clean warning-free codebase even with [aggressive](https://github.com/hparracho/usflib/blob/master/unit_tests/CMakeLists.txt#L10) warning levels.
- Support for  C\+\+11/14/17 standards:
  - GCC 4.8.1 or greater
  - Clang 3.4.0 or greater
  - Should work with MSVC\+\+ 14.0 or greater (*untested yet*)

#### Roadmap - upcoming features
- Complete unit tests.
- IAR and Arm Compiler 5/6 support.
- Dynamic width and precision support.
- std::string replacement with inplace storage.
- Besides formatting, also printing capability with custom output handler, e.g.: Console, UARTs, LCDs, etc...
- Wide character strings support (the foundations are done but it was never used or tested).
- Better floating point conversion routines (the current ones suck!). Looking at the possibility of adapting [ryu](https://github.com/ulfjack/ryu)'s algorithm.

## Usage
________
To get started with **usflib** all you need to do is download the [**latest version**](https://raw.githubusercontent.com/hparracho/usflib/master/include/usf/usf.hpp) which is just a single header file and add it to your source files (or add this repository as a git submodule).

Assuming you can use the single header file directly: ```#include "usf.hpp"``` - place it either in the same folder of your source files or add its location to the include paths of your build system. 

## A minimal example
___________________
```c++
#include "usf.hpp"

int main()
{
    char str[64]{};

    usf::format_to(str, 64, "Hello, {}!", "world");      // str == "Hello, world!"
    usf::format_to(str, 64, "dec:{0} hex:{0:x}", 16);    // str == "dec:16 hex:10"
    usf::format_to(str, 64, "{0}{1}{0}", "abra", "cad"); // str == "abracadabra"
}
```
