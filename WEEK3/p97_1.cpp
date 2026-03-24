#include <iostream>

void pattern1()                 //빈공간 void 에 pattern1 을 지정해줌
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

void pattern2()
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

void pattern3()
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

void pattern4()
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

int main()
{
    std::cout << "No.1_1\n";
    pattern1();   // 첫 번째 패턴
    std::cout << "\n";
    std::cout << "No.1_2\n";
    pattern2();   // 두 번째 패턴
    std::cout << "\n";
    std::cout << "No.1_3\n";
    pattern3();   // 세 번쨰
    std::cout << "\n";
    std::cout << "No.1_4\n";
    pattern4();
    std::cout << "\n";
}