## g++
> 需要带`-g`指令，才能用`gdb`看到一些警告信息

- 这是一个`pop_back()`时候没有判断为空的例子

1. `g++ -g main.cpp -o main`: 在编译时添加`-g`选项

2. `gdb main`: 使用`gdb`打开生成的可执行文件

3. `b 10`: 在`gdb`中输入命令在第10行代码处设置断点

4. `r`: 在`gdb`中输入命令运行程序，即`run`

5. 会提示下列内容:
```
Breakpoint 1, main () at main.cpp:10
10          while (arr.back() % 2 == 0)
```
6. 我们想监控arr和arr.back()两个值
```
display arr
display arr.back()
```

7. `n`：每次运行一步来调试


```
(gdb) n
12              arr.pop_back();
1: arr = std::vector of length 3, capacity 3 = {2, 4, 6}
2: arr.back() = 6
(gdb) n
10          while (arr.back() % 2 == 0)
1: arr = std::vector of length 2, capacity 3 = {2, 4}
2: arr.back() = 4
(gdb) n

Breakpoint 1, main () at main.cpp:10
10          while (arr.back() % 2 == 0)
1: arr = std::vector of length 2, capacity 3 = {2, 4}
2: arr.back() = 4
(gdb) n
12              arr.pop_back();
1: arr = std::vector of length 2, capacity 3 = {2, 4}
2: arr.back() = 4
(gdb) n
10          while (arr.back() % 2 == 0)
1: arr = std::vector of length 1, capacity 3 = {2}
2: arr.back() = 2
(gdb) n

Breakpoint 1, main () at main.cpp:10
10          while (arr.back() % 2 == 0)
1: arr = std::vector of length 1, capacity 3 = {2}
2: arr.back() = 2
(gdb) n
12              arr.pop_back();
1: arr = std::vector of length 1, capacity 3 = {2}
2: arr.back() = 2
(gdb) n
10          while (arr.back() % 2 == 0)
1: arr = std::vector of length 0, capacity 3
2: arr.back() = 0
(gdb) n

Breakpoint 1, main () at main.cpp:10
10          while (arr.back() % 2 == 0)
1: arr = std::vector of length 0, capacity 3
2: arr.back() = 0
(gdb) n
12              arr.pop_back();
1: arr = std::vector of length 0, capacity 3
2: arr.back() = 0
(gdb) n
10          while (arr.back() % 2 == 0)
1: arr = std::vector of length -1, capacity 3 = {2, 4, 6, 0, 0, 0, 61761, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0...}
2: arr.back() = 33

```

## 解决方案

- 目前的代码可以正常编译并且运行，由于数组`arr`中不含有偶数元素，因此移除了偶数元素后，正常来说不会打印。但实际上可能打印了一个随机数，比如说`33`。
- 在`while`循环中，我们不断地检查`arr`的最后一个元素是否为偶数，如果是偶数，就将其删除。但是如果`vector`为空，调用`pop_back()`会导致未定义的行为。

因此代码可以修改为如下情况:

```
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> arr = {2, 4, 6};

    // 移除偶数元素，返回处理后数组的最后一个元素

    while (!arr.empty() && arr.back() % 2 == 0)
    {
        arr.pop_back();
    }

    if (arr.size() > 0)
    {
        std::cout << "arr的最后一个元素是" << arr.back() << std::endl;
    }

    return 0;
}

```

- 顺便提一下，在`vector`中，`!arr.empty()`和`arr.size()>0`的时间复杂度为常数级别，而在一些数据类型中，建议使用第一种方式，效率通常会高一些。