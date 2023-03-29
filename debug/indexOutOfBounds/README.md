## g++
> 需要带`-g`指令，才能用`gdb`看到一些警告信息

- 这是一个数组越界的例子，通过`gdb`调试后可以发现第6行有问题，有无法访问的内存空间

1. `g++ -g main.cpp -o main`: 在编译时添加`-g`选项

2. `gdb main`: 使用`gdb`打开生成的可执行文件

3. `b 7`: 在`gdb`中输入命令在第6行代码处设置断点，即`breakpoint at 7th line`

4. `r`: 在`gdb`中输入命令运行程序，即`run`

5. 会提示下列内容:
```
Breakpoint 1, main () at main.cpp:7
7           for (int i = 0; i <= 5; i++)
```
6. `p i`: 在`gdb`输入命令查看数组索引变量的值，即`print`
```
(gdb) p i
$1 = 21845
```
7. `p arr[i]`: 在`gdb`输入命令查看数组元素的值
```
(gdb) p arr[i]
Cannot access memory at address 0x555555580404
```
8. `q`: 退出`gdb`

> 注意，还有一些其他指令，例如`next`，简写为`n`，执行下一条语句，但不会进入函数内部。`step`，简写为`s`，执行下一条语句，并进入函数内部。

## 解决方案

- 目前的代码可以正常编译并且运行，但是由于索引超出了范围，最后一个元素的输出是不确定的。`vector[i]`没有做越界检查，可以用`.at(i)`来替代
- 为了避免这种风险将代码改成以下内容：
```
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> arr = {1, 2, 3, 4, 5};
    for (int i = 0; i <= 5; i++)
    { // 错误的循环条件，数组索引会溢出
        std::cout << arr.at(i) << std::endl;
    }
    return 0;
}

```
- 运行后提示以下内容，这样能更好地定位问题
```
1
2
3
4
5
terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check: __n (which is 5) >= this->size() (which is 5)
已放弃 (核心已转储)

```