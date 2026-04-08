#include "MineGame.hpp"
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>

#define DIM 9

enum LabelType { Empty = 0, Bomb = 9 };
enum MaskType { Hide = 0, Open, Flag };
static int MineMapMask[40][80];
static int MineMapLabel[40][80];
int nx = DIM, ny = DIM;
static int nBomb = DIM;

// 작은 헬퍼 함수들
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

// 지뢰 탐색
static bool dig(int x, int y) {
    if (!isValid(x, y) || mask(x, y) == Open) return false;
    mask(x, y) = Open;
    if (isBomb(x, y)) return true; // 폭발
    if (label(x, y) == 0) {
        for (int dy = -1; dy <= 1; dy++)
            for (int dx = -1; dx <= 1; dx++)
                if (dx || dy)
                    if(dig(x + dx, y + dy)) return true;
    }
    return false;
}

// 깃발 표시
static void mark(int x, int y) {
    if (isValid(x, y) && mask(x, y) == Hide)
        mask(x, y) = Flag;
}

// 깃발 갯수
static int getBombCount() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(x, y) == Flag) count++;
    return count;
}

// 화면 출력 (커서 강조)
static void print(int cursorX, int cursorY) {
    system("cls");
    printf("   발견:%2d   전체:%2d\n", getBombCount(), nBomb);

    // 열 번호
    printf("    ");
    for (int x = 0; x < nx; x++)
        printf("%2d", x + 1);
    printf("\n");

    for (int y = 0; y < ny; y++) {
        printf("%2d ", y + 1); // 행 번호
        for (int x = 0; x < nx; x++) {
            if (x == cursorX && y == cursorY) { // 선택 칸 강조
                printf("[■]");
            } else if (mask(x, y) == Hide) {
                printf("[□]");
            } else if (mask(x, y) == Flag) {
                printf("[?]");
            } else {
                if (isBomb(x, y)) printf("[※]");
                else if (isEmpty(x, y)) printf("[  ]");
                else printf("[%d]", label(x, y));
            }
        }
        printf("\n");
    }
}

// 주변 지뢰 수
static int countNbrBombs(int x, int y) {
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++)
        for (int xx = x - 1; xx <= x + 1; xx++)
            if (isValid(xx, yy) && label(xx, yy) == Bomb)
                count++;
    return count;
}

// 초기화
static void init(int total = 9) {
    srand((unsigned int)time(NULL));
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            mask(x, y) = Hide;
            label(x, y) = 0;
        }
    nBomb = total;
    for (int i = 0; i < nBomb; i++) {
        int x, y;
        do {
            x = rand() % nx;
            y = rand() % ny;
        } while (label(x, y) != Empty);
        label(x, y) = Bomb;
    }
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (label(x, y) == Empty)
                label(x, y) = countNbrBombs(x, y);
}

// 커서로 위치 선택
static bool getPos(int& x, int& y) {
    x = 0; y = 0;
    while (true) {
        print(x, y); // 현재 위치 강조
        int key = _getch();
        if (key == 224) { // 화살표
            key = _getch();
            if (key == 72 && y > 0) y--;        // ↑
            else if (key == 80 && y < ny - 1) y++; // ↓
            else if (key == 75 && x > 0) x--;    // ←
            else if (key == 77 && x < nx - 1) x++; // →
        } else if (key == 'p' || key == 'P') {
            return true; // 깃발
        } else if (key == 13) {
            return false; // Dig
        }
    }
}

// 완료 체크
static int checkDone() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) != Open) count++;
            else if (isBomb(x, y)) return -1;
        }
    return (count == nBomb) ? 1 : 0;
}

// 게임 실행
void playMineSweeper(int total) {
    int x, y, status;
    init(total);
    bool exploded = false;
    do {
        bool isFlag = getPos(x, y);
        if (isFlag) mark(x, y);
        else exploded = dig(x, y);
        status = exploded ? -1 : checkDone();
    } while (status == 0);

    print(-1, -1); // 종료 시 커서 제거
    if (status < 0)
        printf("\n실패: 지뢰 폭발!!!\n\n");
    else
        printf("\n성공: 탐색 성공!!!\n\n");

    printf("아무 키나 눌러 종료...");
    _getch();
}