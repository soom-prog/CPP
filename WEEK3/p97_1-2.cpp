#include <iostream>

    int main()
{
    for(int i = 5; i >= 1; --i)
    {
        for(int j = 5; j >= 6 - i; --j)
        {
            std::cout << j;
        }
        std::cout << "\n";
    }
}