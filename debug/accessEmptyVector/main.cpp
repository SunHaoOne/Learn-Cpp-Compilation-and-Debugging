#include <iostream>
#include <vector>

int main()
{
    std::vector<int> arr = {2, 4, 6};

    // 移除偶数元素，返回处理后数组的最后一个元素

    while (arr.back() % 2 == 0)
    {
        arr.pop_back();
    }

    if (arr.size() > 0)
    {
        std::cout << "arr的最后一个元素是" << arr.back() << std::endl;
    }

    return 0;
}