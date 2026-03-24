#include <iostream>
#include <145_5.hpp>


std::string reverse(std::string s)
{
    std::reverse(s.begin(), s.end());
    return s;
}

int main()
{
    std::string s;
    std::cin >> s;

    std::cout << reverse(s) << std::endl;
}