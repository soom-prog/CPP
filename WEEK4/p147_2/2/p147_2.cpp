#include <iostream>
#include <algorithm>

int reverse(int);

int main()
{
    int x;
    std::cin >> x;

    std::cout << reverse(x) << std::endl;
    
}

int reverse(int x)
{
    int reverse_Number =0;
    while(x)
    {
    int digit = x%10;
    reverse_Number = reverse_Number * 10 + digit;
    x /= 10;
}

    return reverse_Number;
}


