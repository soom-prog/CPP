#include <cstdio>
#include <cstdlib>
#include <ctime>

static int NumGames = 0;   // 전체 시도 횟수
static int NumWins = 0;    // 성공 횟수
static double Score = 0;   // 점수
double tElapsed = 0;       // 총 소요시간

static bool playGuguOnce()                                              //GuguGame
{
    int a = rand() % 8 + 2;   // 2~9
    int b = rand() % 8 + 2;
    int result;

    NumGames++;
    printf("[문제%2d]: %2d x %2d = ", NumGames, a, b);
    scanf("%d", &result);

    if (result == a * b) NumWins++;
    return (result == a * b);
}

static bool playMulOnce()                                               //두자리 곱셈
{
    int a = rand() % 90 + 10;  // 10~99
    int b = rand() % 90 + 10;
    int result;

    NumGames++;
    printf("[문제%2d]: %2d x %2d = ", NumGames, a, b);
    scanf("%d", &result);

    if (result == a * b) NumWins++;
    return (result == a * b);
}

static long long makeNDigit(int digits)                                 //n자리 덧셈
{
    long long min = 1;
    for (int i = 1; i < digits; i++)
        min *= 10;

    long long max = min * 10 - 1;

    return rand() % (max - min + 1) + min;
}

static bool playPlusOnce(int digits)
{
    long long a = makeNDigit(digits);
    long long b = makeNDigit(digits);
    long long result;

    NumGames++;
    printf("[문제%2d]: %lld + %lld = ", NumGames, a, b);
    scanf("%lld", &result);

    if (result == a + b) NumWins++;
    return (result == a + b);
}

double playSpeedGame(int nPlay, int mode)
{
    NumGames = 0;
    NumWins = 0;

    clock_t t0 = clock();

    for (int i = 0; i < nPlay; i++)
    {
        bool correct;

        if (mode == 1)
            correct = playGuguOnce();        // 구구단
        else if (mode == 2)
            correct = playMulOnce();         // 두 자리 곱셈
        else
            correct = playPlusOnce(mode);    // n자리 덧셈 (3~9)

        if (!correct)
            printf("\t틀렸습니다.\n");
    }

    clock_t t1 = clock();

    tElapsed = (double)(t1 - t0) / CLOCKS_PER_SEC;

    // 부분점수 + 속도 반영 (문제당 20초 기준 → 총 60초 for 3문제)
    Score = 100.0 * ((double)NumWins / NumGames)
                * ((60.0 * NumGames - tElapsed) / (60.0 * NumGames));           //시간 1분으로 고정

    if (Score < 0) Score = 0;

    printf("\n맞은 개수: %d / %d\n", NumWins, NumGames);
    printf("점수: %.1f점\n", Score);
    printf("소요 시간: %.1f초\n", tElapsed);

    return Score;
}

int main()
{
    srand(time(NULL));

    int mode;

    printf("----문제 선택----\n");
    printf("1. 구구단\n");
    printf("2. 두 자리 곱셈\n");
    printf("3~9. n자리 덧셈\n");
    printf("선택: ");
    scanf("%d", &mode);

    playSpeedGame(3, mode);

    return 0;
}