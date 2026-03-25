#include "p147_6(3).hpp"

static int Numgames = 0;
static int NumWins = 0;
static double Score = 0;
double tElapsed = 0;

static long long makeBigRand()
{
    return ((long long)rand() << 30) | rand();
}

static bool playPlusOnce()
{
    long long a = makeBigRand() % 999999999 + 100;
    long long b = makeBigRand() % 999999999 + 100;
    long long result;

    Numgames++;
    printf("[문제%2d]: %9d + %9d = ", Numgames, a, b );
    scanf("%d", &result);

    if (result == a+b) NumWins++;
    return (result == a+b);
}

double playSpeedPlus(int nPlay)
{
    clock_t t0 = clock();

    for (int i = 0; i < nPlay; i++)
    {
        if (!playPlusOnce())
            printf("\t틀렸습니다.\n");
    }

    clock_t t1 = clock();

    tElapsed = (double)(t1 - t0) / CLOCKS_PER_SEC;

    // 부분점수 + 속도 반영
    Score = 100.0 * ((double)NumWins / Numgames)
                * ((60.0 * Numgames - tElapsed) / (60.0 * Numgames));       //문제당 기준시간 20초

    if (Score < 0) Score = 0;

    printf("\n맞은 개수: %d / %d\n", NumWins, Numgames);
    printf("점수: %.1f점\n", Score);
    printf("소요 시간: %.1f초\n", tElapsed);

    return Score;

}

int main()
{
    srand(time(NULL));
    playSpeedPlus(3);
}