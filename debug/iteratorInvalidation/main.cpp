#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<int, int> mp = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    for (auto it = mp.begin(); it != mp.end(); ++it)
    {
        // 删除偶数键值元素
        if (it->first % 2 == 0)
        {
            mp.erase(it);
        }
    }

    for (auto it = mp.begin(); it != mp.end(); ++it)
    {
        std::cout << "map[" << it->first << "] = " << it->second << std::endl;
    }
    return 0;
}