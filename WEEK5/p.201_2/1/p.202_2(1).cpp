#include <cstdio>
#include <cstdlib>

void randomMap(int map[5][5])
{
    for (int i=0; i<5; ++i)
    {
        for (int j=0; j<5; ++j)
        {
            map[i][j] = std::rand() % 2;
        }
    }
}
