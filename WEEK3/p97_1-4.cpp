#include <iostream>

int main()
{
    for(int i = 1; i <= 5; ++i)
    {
        for(int j = 1; j<=5-i; ++j)
        {
            std::cout << " "; //숫자를 오른쪽으로 밀기 위함
        }

        for(int j = i; j >= 1; --j)
        {
            std::cout << j;
        }
        for(int j=2; j<=i; ++j) //j의 값이 1로 갈떄는 줄어들고, 1을 지난 2부터는 증가함을 의미
        {
            std::cout << j;
        }
        std::cout << "\n";
    }
}