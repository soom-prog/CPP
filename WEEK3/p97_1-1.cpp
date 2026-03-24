#include <iostream>

int main()              //main 함수 입력
{
    for(int i = 1; i <= 5; ++i)
    {
        for(int j = 1; j <= i; ++j)
        {
            std::cout << j;
        }
        std::cout << "\n";
    }
}