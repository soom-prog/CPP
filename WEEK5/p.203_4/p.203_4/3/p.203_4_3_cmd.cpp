#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <locale.h>

#define DIM 3 // 4x4 퍼즐 // 5x5 3x3 조정하는

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };
static int DirKey[4] = { Left, Right, Up, Down };

static int map[DIM][DIM];     // 퍼즐 맵
static int x, y;              // 공백의 위치 / y = 행, x = 열
static int nMove;             // 이동 횟수 (랭킹에 필요)
static clock_t tStart;        // 기준 시간 (랭킹에 필요)
//리플레이 기록 저장
static int moveHistory[10000];  //최대 10000회
static int moveCount = 0;       //기록한 개수


typedef struct {
    int map[DIM][DIM];
    int x, y;
    int nMove;
    double elapsed;
    int moveHistory[10000];
    int moveCount;
} SaveData;

void saveGame() {
    FILE* fp = fopen("save.dat", "wb");
    if (!fp) return;

    SaveData data;

    memcpy(data.map, map, sizeof(map));
    data.x = x;
    data.y = y;
    data.nMove = nMove;

    clock_t now = clock();
    data.elapsed = (double)(now - tStart) / CLOCKS_PER_SEC;

    memcpy(data.moveHistory, moveHistory, sizeof(moveHistory));
    data.moveCount = moveCount;

    fwrite(&data, sizeof(SaveData), 1, fp);
    fclose(fp);

    printf("\n게임 저장 완료!\n");
}

// 퍼즐 맵 초기화 함수
static void init() {
    // 1부터 순서대로 채우고 마지막 칸은 비움
    for (int i = 0; i < DIM * DIM - 1; i++)
        map[i / DIM][i % DIM] = i + 1;

    map[DIM - 1][DIM - 1] = 0;  // 마지막 칸을 빈칸으로 설정

    x = DIM - 1;
    y = DIM - 1;                // 빈칸 위치 설정

    srand(time(NULL));          // 난수 발생 초기화
}


// 화면 출력 함수
static void display() {
    system("cls");              // 콘솔 화면 지우기

    printf("\tFifteen Puzzle\n\t");
    printf("--------------\n\t");

    // 퍼즐 전체 출력
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] > 0)  // 숫자 출력
                printf("%3d", map[r][c]);
            else                // 빈칸 출력
                printf("   ");
        }
        printf("\n\t");
    }

    printf("--------------\n\t");

    clock_t t1 = clock();  // 현재 시간
    double d = (double)(t1 - tStart) / CLOCKS_PER_SEC; // 경과 시간(초)

    printf("\n\t이동 횟수:%6d\n\t소요 시간:%6.1f\n\n", nMove, d);
}


// 퍼즐 이동 함수
static bool move(int dir) {
    if (dir == Right && x > 0) {              // 왼쪽 타일을 오른쪽으로 이동
        map[y][x] = map[y][x - 1];
        map[y][--x] = 0;
    }
    else if (dir == Left && x < DIM - 1) {    // 오른쪽 타일을 왼쪽으로 이동
        map[y][x] = map[y][x + 1];
        map[y][++x] = 0;
    }
    else if (dir == Up && y < DIM - 1) {      // 아래 타일을 위로 이동
        map[y][x] = map[y + 1][x];
        map[++y][x] = 0;
    }
    else if (dir == Down && y > 0) {          // 위 타일을 아래로 이동
        map[y][x] = map[y - 1][x];
        map[--y][x] = 0;
    }
    else return false;                        // 이동 불가능

    moveHistory[moveCount++] = dir;           //성공시 기록

    nMove++;
    return true;
}


// 퍼즐 섞기 함수
static void shuffle(int nShuffle) {
    for (int i = 0; i < nShuffle; i++) {
        int key = DirKey[rand() % 4];     // 랜덤 방향 선택

        if (move(key) == false) {         // 이동 실패 시 다시 시도
            i--;
            continue;
        }

        display();
        Sleep(50);                       // 섞는 과정 시각화
    }
}


// 퍼즐 완료 여부 검사
static bool isDone() {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            // 순서대로 되어 있는지 확인
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1) && (c == DIM - 1);
        }
    }
    return true;
}


// 방향키 입력 처리 함수
static int getDirKey() {
    return _getch() == 224 ? _getch() : 0;
}

static void replayMoves()
{
    printf("\n리플레이 시작...\n");
    Sleep(1000);

    init();              //초기상태 불러오기

    for (int i =0; i < moveCount; i++)  //리플레이에서 보일 행렬 디스플레이
    {
        move(moveHistory[i]);
        display();
        Sleep(200);
    }

    printf("\n리플레이 종료\n");
    _getch();
}

// 게임 실행 함수
int playFifteenPuzzle() {
    moveCount = 0; //실행시 기록 초기화를 위함
    init();        // 퍼즐 초기화
    display();     // 화면 출력

    // printRanking(); // 랭킹 출력 (미구현)

    printf("\n 퍼즐을 섞어주세요(엔터)...");
    _getch();      // 시작 대기

    shuffle(100);  // 퍼즐 섞기

    printf("\n 게임이 시작됩니다...");
    _getch();      // 시작 대기

    nMove = 0;     
    tStart = clock();  // 시간 측정 시작

while (!isDone()) {
    int key = _getch();

    // ? 저장 후 종료
    if (key == 's') {
        saveGame();
        printf("\n저장 후 종료합니다...\n");
        Sleep(1000);
        return 0;
    }

    // 방향키 처리
    if (key == 224) {
        move(_getch());
    }

    display();
}
    clock_t t1 = clock();
    double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;

    printf("리플레이 (Y/N): ");
    char choice = _getch();
    if (choice == 'Y' || choice == 'y')     //Y 선택시 리플레이 진행
    {
        replayMoves();
    }
    return 0;
}


int main() {
    setlocale(LC_ALL, "Korean"); // 한글 출력 설정

    playFifteenPuzzle();
    return 0;
}