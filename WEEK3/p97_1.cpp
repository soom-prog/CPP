#include <iostream>

int main()
{
    // for(int i = 1; i <= 5; ++i;)
    for(int i = 1; i <= 5; ++i)
    {
        // std::cout << 1; << "\n"; 
        // std::cout << 1 << "\n"; 
        
        for(int j = 1; j <= i; ++j)
        {
            std::cout << j;
        }
            std::cout << "\n";
    }
}

#include <iostream>

int main()
{
    // for(int i = 1; i <= 5; ++i;)
    for(int i = 5; i >= 1; --i)
    {
        // std::cout << 1; << "\n"; 
        // std::cout << 1 << "\n"; 
        
        for(int j = 5; j >= i; --j)
        {
            std::cout << j;
        }
            std::cout << "\n";
    }
}