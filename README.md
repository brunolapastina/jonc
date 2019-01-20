# JONC - Java on C++

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/brunolapastina/jonc/master/LICENSE)

A simple header-only library to call Java methods in C++ without having to think about all the JNI conversions

- [Design goals](#design-goals)
- [Integration](#integration)
- [Examples](#examples)
- [Acknowledgments](#acknowledgments)

## Design Goals

The main goal of JONC is to make things simpler. It tries to achive that by using:
1. Compile time deduction of method signatures based on its call arguments
2. Automatic type conversion from C++ to Java and back

For primitive types, this signature deduction and type convertion is already implemented in the framework, but, of course, you can expand it to any user-defined type.

## Integration

To use this library, you need to include only the `jonc.hpp`.

```cpp
#include <jonc/jonc.hpp>
```

You will also need at least C++11 support (in GCC and Clang, use -std=c++11). If you enable more recent C++ standards, the library will try to make the best use of it, so, if you can, do it!

## Examples

The [test folder](test) has a bunch of examples. Go there and take a look at the README.

## License

This library is released under the [Boost License Version 1.0](https://www.boost.org/LICENSE_1_0.txt)

```
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
```

If you have any question, start by looking at [this link](https://www.boost.org/users/license.html)

## Acknowledgments

- [**Andrzej Krzemienski**](https://akrzemi1.wordpress.com) for building this amazing [Compile-time string concatenation library](https://github.com/akrzemi1/static_string) fully explained in [this article](https://akrzemi1.wordpress.com/2017/06/28/compile-time-string-concatenation/). With this library I was able to eliminate all the runtime overhead of dynamically building the method signatures.
