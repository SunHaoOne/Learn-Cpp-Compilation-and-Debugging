## cmake
> 需要配合写一个CMakeLists
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
- `./main`


## g++

- `g++ -o main main.cpp -L. -lsum`
- `./main`

- `-L.`参数指定链接器在当前目录中查找动态链接库文件，`-lsum`参数指定链接器链接名为`libsum.so`的动态链接库

## 生成动态链接库文件

- `g++ -shared -fPIC -o libsum.so sum.cpp`

- `-shared`选项告诉编译器生成一个共享库（动态链接库）。在Linux和Unix系统中，共享库（shared library）也被称为动态链接库（dynamic link library，简称DLL）。动态链接库是一种特殊的库文件，可以在运行时被程序动态加载到内存中，并被多个程序共享使用，从而节省内存空间。

- `-fPIC`选项是gcc编译器的一个参数，它表示生成位置无关的代码（Position Independent Code）。这种代码可以在任何内存地址运行，不需要重定位。动态链接库需要使用这种代码，因为它们在加载时不知道被放置在哪个地址。

## cmake路径的区别

- `CMAKE_CURRENT_SOURCE_DIR`: 表示当前正在处理的CMakeLists.txt文件所在的目录，它是一个相对路径。如果你在一个子目录中使用add_subdirectory()命令，那么这个变量就会改变为子目录的路径。
- `CMAKE_BINARY_DIR`: 表示构建树的顶层目录，它是一个绝对路径。这个目录是你运行cmake命令时指定的目标目录，它通常和源码目录不同，以避免污染源码。这个变量在整个构建过程中不会改变。

