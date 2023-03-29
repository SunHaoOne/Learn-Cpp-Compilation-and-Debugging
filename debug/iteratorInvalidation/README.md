## g++
> 需要带`-g`指令，才能用`gdb`看到一些警告信息

- 这是一个迭代器越界的例子，当调用`mp.erase(it)`删除迭代器指向的键值对时，迭代器`it`将失效，也就是说`it`指向的元素不再是有效的，但是循环中的代码`++it`会继续执行，这样就会跳过下一个元素。此后，程序可能会访问无效的迭代器，导致程序崩溃或者产生错误结果。

> 注意，`display`和`print`的区别在于，如果我们想要在每次程序暂停执行时都查看`num`的值，我们可以使用`display num`命令。这样，每当程序暂停执行时，`gdb`调试器都会自动打印出`num`的值。相反，如果我们只想查看一次`num`的值，我们可以使用`print num`命令。这样，`gdb`调试器只会打印一次`num`的值。 


1. `g++ -g main.cpp -o main`: 在编译时添加`-g`选项

2. `gdb main`: 使用`gdb`打开生成的可执行文件

3. `b 7`: 在`gdb`中输入命令在第6行代码处设置断点

4. `r`: 在`gdb`中输入命令运行程序，即`run`

5. 持续监控`mp`和迭代器`it`
```
display mp
display it
```
6. 那么接下来每次输入`n`执行`next`命令即可。
```
Breakpoint 1, main () at main.cpp:7
7           for (auto it = mp.begin(); it != mp.end(); ++it)
(gdb) display mp
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
(gdb) display it
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x7fffffffceb0}, <No data fields>}
(gdb) n
10              if (it->first % 2 == 0)
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df60}, <No data fields>}
(gdb) n
7           for (auto it = mp.begin(); it != mp.end(); ++it)
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df60}, <No data fields>}
(gdb) n
10              if (it->first % 2 == 0)
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df40}, <No data fields>}
(gdb) n
12                  mp.erase(it);
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df40}, <No data fields>}
(gdb) n
7           for (auto it = mp.begin(); it != mp.end(); ++it)
1: mp = std::unordered_map with 4 elements = {[5] = 5, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df40}, <No data fields>}
(gdb) n
15          return 0;
1: mp = std::unordered_map with 4 elements = {[5] = 5, [3] = 3, [2] = 2, [1] = 1}
```
- 可以看到偶数元素并没有完全被删除
- 迭代器的地址从`0x55555556df60`变成`0x55555556df40`后，下一次迭代器`it++`失效，直接跳出循环。

## 解决方案

- 将代码改成以下内容：
```
#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<int, int> mp = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    for (auto it = mp.begin(); it != mp.end();)
    {
        // 删除偶数键值元素
        if (it->first % 2 == 0)
        {
            it = mp.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return 0;
}

```
- `erase`方法返回指向下一个元素的迭代器，因此修改后，在删除元素时使用erase方法的返回值来更新迭代器，就可以避免迭代器失效的问题。
- 可以看到迭代器可以正确的改变地址，从`0x55555556df60`，`0x55555556df60`，`0x55555556df20`,`0x55555556df20`到`0x55555556dee0`。

```
Breakpoint 1, main () at main.cpp:7
7           for (auto it = mp.begin(); it != mp.end(); ++it)
(gdb) display mp
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
(gdb) display it
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x7fffffffceb0}, <No data fields>}
(gdb) n
10              if (it->first % 2 == 0)
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df60}, <No data fields>}
(gdb) n
16                  ++it;
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df60}, <No data fields>}
(gdb) n
7           for (auto it = mp.begin(); it != mp.end(); ++it)
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df40}, <No data fields>}
(gdb) n
10              if (it->first % 2 == 0)
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df20}, <No data fields>}
(gdb) n
16                  ++it;
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df20}, <No data fields>}
(gdb) n
7           for (auto it = mp.begin(); it != mp.end(); ++it)
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556df00}, <No data fields>}
(gdb) n
10              if (it->first % 2 == 0)
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556dee0}, <No data fields>}
(gdb) n
16                  ++it;
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x55555556dee0}, <No data fields>}
(gdb) n
7           for (auto it = mp.begin(); it != mp.end(); ++it)
1: mp = std::unordered_map with 5 elements = {[5] = 5, [4] = 4, [3] = 3, [2] = 2, [1] = 1}
2: it = {<std::__detail::_Node_iterator_base<std::pair<int const, int>, false>> = {_M_cur = 0x0}, <No data fields>}
```