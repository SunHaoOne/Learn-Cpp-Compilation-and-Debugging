#include <iostream>

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i <= 5; i++)
    { // 错误的循环条件，数组索引会溢出
        std::cout << arr[i] << std::endl;
    }
    return 0;
}