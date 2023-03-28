## cmake
> 需要配合写一个CMakeLists
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
- `./main`


## g++

- `g++ main.cpp sum.cpp -o main`
- `./main`


## sum.h

- 第一行和最后一行是预处理器指令，用于防止头文件被重复包含。`#ifndef SUM_H`指令检查`SUM_H`符号是否已经定义。如果没有定义，那么预处理器会执行`#ifndef`和`#endif`之间的代码。如果已经定义，那么预处理器会跳过这些代码。

- 第二行`#define SUM_H`指令定义了`SUM_H`符号。这样，当头文件被再次包含时，`SUM_H`符号已经定义，预处理器就会跳过 `#ifndef`和`#endif`之间的代码，从而防止头文件被重复包含。

## 编译的顺序

- 在`add_executable`命令中，源文件的顺序通常不重要。`CMake`会根据源文件之间的依赖关系来确定编译顺序。

- 在上面的例子中，`main.cpp`文件依赖于`sum.h`头文件，而`sum.h`头文件又依赖于`sum.cpp`文件。因此，`CMake`会先编译 `sum.cpp`文件，然后再编译`main.cpp`文件。