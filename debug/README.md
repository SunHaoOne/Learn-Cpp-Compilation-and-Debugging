## g++
> 需要带`-g`指令，才能用`gdb`看到一些警告信息

- 这是一个数组越界的例子，通过`gdb`调试后可以发现第6行有问题，有无法访问的内存空间

1. `g++ -g main.cpp -o main`: 在编译时添加`-g`选项

2. `gdb main`: 使用`gdb`打开生成的可执行文件

3. `b 6`: 在`gdb`中输入命令在第6行代码处设置断点

4. `r`: 在 GDB 中输入命令运行程序

5. 会提示下列内容:
```
Breakpoint 1, main () at main.cpp:6
6           for (int i = 0; i <= 5; i++)
```
6. `p i`: 在`gdb`输入命令查看数组索引变量的值
```
(gdb) p i
$1 = 21845
```
7. `p arr[i]`: 在`gdb`输入命令查看数组元素的值
```
(gdb) p arr[i]
Cannot access memory at address 0x800000012474
```
8. `q`: 退出`gdb`