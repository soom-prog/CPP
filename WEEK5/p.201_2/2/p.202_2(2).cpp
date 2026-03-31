#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <time.h>

void randomMap(int map[5][5])
{
    for (int i=0; i<5; ++i)
        for (int j=0; j<5; ++j)
            map[i][j] = std::rand() % 2;
}

int map()
{
    int map[5][5];

    srand(time(NULL));
    randomMap(map);

    for (int i=0; i<5; ++i)
    {
        for (int j=0; j<5; ++j)
        {
            map[i][j] = std::rand() % 2;
                std::cout << map[i][j] << " ";
        }
    }
    return 0;
}