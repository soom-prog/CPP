#include <iostream>

int main()
{
    for(int i = 1; i <= 5; ++i)
    {
        for(int j = 1; j<=5-i; ++j)
        {
            std::cout << " "; //숫자를 오른쪽으로 밀기 위함
        }

        for(int j = 1; j <= i; ++j)
        {
            std::cout << j;
        }
        std::cout << "\n";
    }
}