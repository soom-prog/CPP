#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <locale.h>

#define DIM 3 // 퍼즐 크기 3x3, 필요하면 4x4, 5x5로 변경 가능

// 방향키 값 정의
enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };
static int DirKey[4] = { Left, Right, Up, Down };

// 게임 상태 변수
static int map[DIM][DIM];     // 퍼즐 맵
static int x, y;              // 빈칸 위치 (x:열, y:행)
static int nMove;             // 이동 횟수
static clock_t tStart;        // 게임 시작 시간

// 리플레이 기록 저장
static int moveHistory[10000];  
static int moveCount = 0;       

// 저장 데이터 구조체
typedef struct {
    int map[DIM][DIM];
    int x, y;
    int nMove;
    double elapsed;            // 경과 시간
    int moveHistory[10000];
    int moveCount;
} SaveData;

// 게임 저장 함수
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

// 저장된 게임 불러오기
bool loadGame() {
    FILE* fp = fopen("save.dat", "rb");
    if (!fp) {
        printf("\n저장 파일이 없습니다.\n");
        return false;
    }

    SaveData data;
    fread(&data, sizeof(SaveData), 1, fp);
    fclose(fp);

    // 상태 복원
    memcpy(map, data.map, sizeof(map));
    x = data.x;
    y = data.y;
    nMove = data.nMove;

    memcpy(moveHistory, data.moveHistory, sizeof(moveHistory));
    moveCount = data.moveCount;

    // 시간 복원
    tStart = clock() - (clock_t)(data.elapsed * CLOCKS_PER_SEC);

    printf("\n불러오기 완료!\n");
    return true;
}

// 퍼즐 맵 초기화 (순서대로 채우고 마지막 칸 빈칸)
static void init() {
    for (int i = 0; i < DIM * DIM - 1; i++)
        map[i / DIM][i % DIM] = i + 1;

    map[DIM - 1][DIM - 1] = 0;  // 마지막 칸 빈칸
    x = DIM - 1;
    y = DIM - 1;

    srand(time(NULL));
}

// 화면 출력
static void display() {
    system("cls");
    printf("\tFifteen Puzzle\n\t");
    printf("--------------\n\t");

    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] > 0)
                printf("%3d", map[r][c]);
            else
                printf("   ");
        }
        printf("\n\t");
    }

    printf("--------------\n\t");

    clock_t t1 = clock();
    double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
    printf("\n\t이동 횟수:%6d\n\t소요 시간:%6.1f\n\n", nMove, d);
}

// 퍼즐 이동
static bool move(int dir) {
    if (dir == Right && x > 0) {
        map[y][x] = map[y][x - 1];
        map[y][--x] = 0;
    }
    else if (dir == Left && x < DIM - 1) {
        map[y][x] = map[y][x + 1];
        map[y][++x] = 0;
    }
    else if (dir == Up && y < DIM - 1) {
        map[y][x] = map[y + 1][x];
        map[++y][x] = 0;
    }
    else if (dir == Down && y > 0) {
        map[y][x] = map[y - 1][x];
        map[--y][x] = 0;
    }
    else return false;

    moveHistory[moveCount++] = dir;
    nMove++;
    return true;
}

// 퍼즐 섞기 (시각화 포함)
static void shuffle(int nShuffle) {
    for (int i = 0; i < nShuffle; i++) {
        int key = DirKey[rand() % 4];
        if (!move(key)) {
            i--;
            continue;
        }
        display();
        Sleep(50);
    }
}

// 퍼즐 완료 여부 확인
static bool isDone() {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1) && (c == DIM - 1);
        }
    }
    return true;
}

// 리플레이 출력
static void replayMoves() {
    printf("\n리플레이 시작...\n");
    Sleep(1000);

    init();

    for (int i = 0; i < moveCount; i++) {
        move(moveHistory[i]);
        display();
        Sleep(200);
    }

    printf("\n리플레이 종료\n");
    _getch();
}

// 게임 루프
int playFifteenPuzzle() {
    while (!isDone()) {
        int key = _getch();

        // 저장 후 종료
        if (key == 's' || key == 'S') {
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

    printf("퍼즐 완료!\n");
    printf("리플레이 (Y/N): ");
    char choice = _getch();
    if (choice == 'Y' || choice == 'y') {
        replayMoves();
    }

    return 0;
}

// 메인 함수
int main() {
    setlocale(LC_ALL, "Korean");

    printf("=== Fifteen Puzzle ===\n");
    printf("1: 새 게임\n2: 이어하기\n선택: ");
    int sel = _getch();

    if (sel == '2') {
        if (!loadGame()) {
            printf("\n저장된 게임이 없어 새 게임을 시작합니다.\n");
            moveCount = 0;
            init();
            shuffle(100);   // 새 게임만 섞기
            nMove = 0;
            tStart = clock();
        } else {
            printf("\n이어하기 선택, 기존 상태 그대로 시작합니다.\n");
            display();
            tStart = clock();  // 이어하기 시작 시 시간 초기화
        }
    } else {
        moveCount = 0;
        init();
        shuffle(100);       // 새 게임만 섞기
        nMove = 0;
        tStart = clock();
        display();
    }

    playFifteenPuzzle(); // 게임 루프 실행
    return 0;
}