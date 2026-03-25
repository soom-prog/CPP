#include "p147_6(2).hpp"

static int Numgames = 0;
static int NumWins = 0;
static double Score = 0;
double tElapsed = 0;

static bool playGuguOnce()
{
    int a = rand() %90 + 10;
    int b = rand() %90 + 10;
    int result;

    Numgames++;
    printf("[문제%2d]: %2d * %2d = ", Numgames, a, b );
    scanf("%d", &result);

    if (result == a*b) NumWins++;
    return (result == a*b);
}

double playSpeedGugu(int nPlay)
{
    clock_t t0 = clock();

    for (int i = 0; i < nPlay; i++)
    {
        if (!playGuguOnce())
            printf("\t틀렸습니다.\n");
    }

    clock_t t1 = clock();

    tElapsed = (double)(t1 - t0) / CLOCKS_PER_SEC;

    // 부분점수 + 속도 반영
    Score = 100.0 * ((double)NumWins / Numgames)
                * ((40.0 * Numgames - tElapsed) / (40.0 * Numgames));       //문제당 기준시간 20초

    if (Score < 0) Score = 0;

    printf("\n맞은 개수: %d / %d\n", NumWins, Numgames);
    printf("점수: %.1f점\n", Score);
    printf("소요 시간: %.1f초\n", tElapsed);

    return Score;

}

int main()
{
    srand(time(NULL));
    playSpeedGugu(3);                                                       //문제개수
}