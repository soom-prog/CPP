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
static int nx = DIM, ny = DIM;
static int nBomb = DIM;

// ���� ���� �Լ���
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y) { return isValid(x, y) && label(x, y) == Bomb; }
inline bool isEmpty(int x, int y) { return isValid(x, y) && label(x, y) == Empty; }

// ���� Ž��
static bool dig(int x, int y) {
    if (!isValid(x, y) || mask(x, y) == Open) return false;
    mask(x, y) = Open;
    if (isBomb(x, y)) return true; // ����
    if (label(x, y) == 0) {
        for (int dy = -1; dy <= 1; dy++)
            for (int dx = -1; dx <= 1; dx++)
                if (dx || dy)
                    if(dig(x + dx, y + dy)) return true;
    }
    return false;
}

// ��� ǥ��
static void mark(int x, int y) {
    if (isValid(x, y) && mask(x, y) == Hide)
        mask(x, y) = Flag;
}

// ��� ����
static int getBombCount() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(x, y) == Flag) count++;
    return count;
}

// ȭ�� ��� (Ŀ�� ����)
static void print(int cursorX, int cursorY) {
    system("cls");
    printf("   �߰�:%2d   ��ü:%2d\n", getBombCount(), nBomb);

    // �� ��ȣ
    printf("    ");
    for (int x = 0; x < nx; x++)
        printf("%2d", x + 1);
    printf("\n");

    for (int y = 0; y < ny; y++) {
        printf("%2d ", y + 1); // �� ��ȣ
        for (int x = 0; x < nx; x++) {
            if (x == cursorX && y == cursorY) { // ���� ĭ ����
                printf("[��]");
            } else if (mask(x, y) == Hide) {
                printf("[��]");
            } else if (mask(x, y) == Flag) {
                printf("[?]");
            } else {
                if (isBomb(x, y)) printf("[��]");
                else if (isEmpty(x, y)) printf("[  ]");
                else printf("[%d]", label(x, y));
            }
        }
        printf("\n");
    }
}

// �ֺ� ���� ��
static int countNbrBombs(int x, int y) {
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++)
        for (int xx = x - 1; xx <= x + 1; xx++)
            if (isValid(xx, yy) && label(xx, yy) == Bomb)
                count++;
    return count;
}

// �ʱ�ȭ
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

// Ŀ���� ��ġ ����
static bool getPos(int& x, int& y) {
    x = 0; y = 0;
    while (true) {
        print(x, y); // ���� ��ġ ����
        int key = _getch();
        if (key == 224) { // ȭ��ǥ
            key = _getch();
            if (key == 72 && y > 0) y--;        // ��
            else if (key == 80 && y < ny - 1) y++; // ��
            else if (key == 75 && x > 0) x--;    // ��
            else if (key == 77 && x < nx - 1) x++; // ��
        } else if (key == 'p' || key == 'P') {
            return true; // ���
        } else if (key == 13) {
            return false; // Dig
        }
    }
}

// �Ϸ� üũ
static int checkDone() {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) != Open) count++;
            else if (isBomb(x, y)) return -1;
        }
    return (count == nBomb) ? 1 : 0;
}

// ���� ����
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

    print(-1, -1); // ���� �� Ŀ�� ����
    if (status < 0)
        printf("\n����: ���� ����!!!\n\n");
    else
        printf("\n����: Ž�� ����!!!\n\n");

    printf("�ƹ� Ű�� ���� ����...");
    _getch();
}