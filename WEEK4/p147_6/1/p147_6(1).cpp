#include "p147_6(1).hpp"                                                                    //설정 헤드파일 불러오기

static int Numgames = 0;                                                                    //교재내용 참고
static int NumWins = 0;                                                                     //맞춘 횟수
static double Score = 0;                                                                    //점수
double tElapsed = 0;                                                                        //앞 헤더 파일에서 가져올 소요시간 ((변수지정))

static bool playPlusOnce()                                                                  
{
    int a = rand() %1000 + 1;
    int b = rand() %1000 + 1;
    int result;

    Numgames++;
    printf("[문제%2d]: %3d + %3d = ", Numgames, a, b );
    scanf("%d", &result);

    if (result == a+b) NumWins++;
    return (result == a+b);
}

double playSpeedPlus(int nPlay)                                                             //헤더파일에서 지정했던 plaaySpeedPlus 함수에 대입
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
                * ((20.0 * Numgames - tElapsed) / (20.0 * Numgames));       //문제당 기준시간 20초

    if (Score < 0) Score = 0;                                               //시간오버에서 점수가 음수 나오기 방지

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