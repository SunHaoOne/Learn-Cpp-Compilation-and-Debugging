## g++
> 需要带`-g`指令，才能用`gdb`看到一些警告信息

- 这是一个指针调用类内函数的代码，如果`heading`值是`-999`的时候，表示当前没有获取到`lane`的信息，因此创建后会返回空指针。
- 当一个空指针调用类内函数代码的时候会报错`段错误 (核心已转储)`，因为涉及到了空指针解引用的错误。


1. `g++ -g main.cpp -o main`: 在编译时添加`-g`选项

2. `gdb main`: 使用`gdb`打开生成的可执行文件

3. `b 52`: 在`gdb`中输入命令在第52行代码处设置断点

4. `r`: 在`gdb`中输入命令运行程序，即`run`

5. 那么接下来每次输入`n`执行`next`命令即可，通过这种方式能快速定位哪行出了问题。
```
Breakpoint 1, main () at main.cpp:52
52          auto *ptr1 = Velocity::create(10, 10, M_PI / 4.0);
(gdb) n
53          auto *ptr2 = Velocity::create(10, 10, -999); // 可能由于没有获取到lane_id信息,lane_heading=-999
(gdb) n
55          ptr1->print_decomposed_velocity();
(gdb) n
vl = 14.1421, vs = 8.88178e-16
56          ptr2->print_decomposed_velocity();
(gdb) n

Program received signal SIGSEGV, Segmentation fault.
0x00005555555554dd in Velocity::decompose_velocity (this=0x0) at main.cpp:19
19              double lx = cos(this->lane_heading);
(gdb) n

Program terminated with signal SIGSEGV, Segmentation fault.
The program no longer exists.
```

6. 找到了哪行出现问题后，可以使用`s`命令，进入函数一步一步运行查看具体的情况。

- 经过分析后，发现`19`行报错，由于传入的是空指针，因此没有对应的`lane_heading`属性而报错。
```
Velocity::print_decomposed_velocity (this=0x55555556aeb0) at main.cpp:33
33              auto speeds = decompose_velocity();
(gdb) s
Velocity::decompose_velocity (this=0x55555556aeb0) at main.cpp:16
16          std::pair<double, double> decompose_velocity()
(gdb) s
19              double lx = cos(this->lane_heading);
```

## 解决方案

- 增加`if`判断，如果指针非空的情况下才进行后续的一系列操作。


```
#include <iostream>
#include <cmath>
#include <vector>

class Velocity
{
public:
    static Velocity *create(double vx, double vy, double lane_heading)
    {
        if (lane_heading == -999)
            return nullptr;
        else
            return new Velocity(vx, vy, lane_heading);
    }

    std::pair<double, double> decompose_velocity()
    {
        // 计算道路方向向量和垂直方向向量
        double lx = cos(this->lane_heading);
        double ly = sin(this->lane_heading);

        // 计算沿着道路方向的速度
        double speed_along_lane = this->vx * lx + this->vy * ly;

        // 计算垂直道路方向的速度
        double speed_perpendicular_to_lane = this->vx * (-ly) + this->vy * lx;

        return std::make_pair(speed_along_lane, speed_perpendicular_to_lane);
    }

    void print_decomposed_velocity()
    {
        auto speeds = decompose_velocity();
        std::cout << "vl = " << speeds.first << ", vs = " << speeds.second << std::endl;
    }

private:
    Velocity(double vx, double vy, double lane_heading)
    {
        this->vx = vx;
        this->vy = vy;
        this->lane_heading = lane_heading;
    }
    double vx;
    double vy;
    double lane_heading;
};

int main()
{

    auto *ptr1 = Velocity::create(10, 10, M_PI / 4.0);
    auto *ptr2 = Velocity::create(10, 10, -999); // 可能由于没有获取到lane_id信息,lane_heading=-999

    if (ptr1 != nullptr)
    {
        ptr1->print_decomposed_velocity();
    }

    if (ptr2 != nullptr)
    {
        ptr1->print_decomposed_velocity();
    }

    delete ptr1;
    delete ptr2;
    return 0;
}

```