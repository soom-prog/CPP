#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <locale.h>

#define DIM 3 // 4x4 ���� // 5x5 3x3 �����ϴ�

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };
static int DirKey[4] = { Left, Right, Up, Down };

static int map[DIM][DIM];     // ���� ��
static int x, y;              // ������ ��ġ / y = ��, x = ��
static int nMove;             // �̵� Ƚ�� (��ŷ�� �ʿ�)
static clock_t tStart;        // ���� �ð� (��ŷ�� �ʿ�)

//���÷��� ��� ����
static int moveHistory[10000];  //�ִ� 10000ȸ
static int moveCount = 0;       //����� ����

// ���� �� �ʱ�ȭ �Լ�
static void init() {
    // 1���� ������� ä��� ������ ĭ�� ���
    for (int i = 0; i < DIM * DIM - 1; i++)
        map[i / DIM][i % DIM] = i + 1;

    map[DIM - 1][DIM - 1] = 0;  // ������ ĭ�� ��ĭ���� ����

    x = DIM - 1;
    y = DIM - 1;                // ��ĭ ��ġ ����

    srand(time(NULL));          // ���� �߻� �ʱ�ȭ
}


// ȭ�� ��� �Լ�
static void display() {
    system("cls");              // �ܼ� ȭ�� �����

    printf("\tFifteen Puzzle\n\t");
    printf("--------------\n\t");

    // ���� ��ü ���
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] > 0)  // ���� ���
                printf("%3d", map[r][c]);
            else                // ��ĭ ���
                printf("   ");
        }
        printf("\n\t");
    }

    printf("--------------\n\t");

    clock_t t1 = clock();  // ���� �ð�
    double d = (double)(t1 - tStart) / CLOCKS_PER_SEC; // ��� �ð�(��)

    printf("\n\t�̵� Ƚ��:%6d\n\t�ҿ� �ð�:%6.1f\n\n", nMove, d);
}


// ���� �̵� �Լ�
static bool move(int dir) {
    if (dir == Right && x > 0) {              // ���� Ÿ���� ���������� �̵�
        map[y][x] = map[y][x - 1];
        map[y][--x] = 0;
    }
    else if (dir == Left && x < DIM - 1) {    // ������ Ÿ���� �������� �̵�
        map[y][x] = map[y][x + 1];
        map[y][++x] = 0;
    }
    else if (dir == Up && y < DIM - 1) {      // �Ʒ� Ÿ���� ���� �̵�
        map[y][x] = map[y + 1][x];
        map[++y][x] = 0;
    }
    else if (dir == Down && y > 0) {          // �� Ÿ���� �Ʒ��� �̵�
        map[y][x] = map[y - 1][x];
        map[--y][x] = 0;
    }
    else return false;                        // �̵� �Ұ���

    moveHistory[moveCount++] = dir;           //������ ���

    nMove++;
    return true;
}


// ���� ���� �Լ�
static void shuffle(int nShuffle) {
    for (int i = 0; i < nShuffle; i++) {
        int key = DirKey[rand() % 4];     // ���� ���� ����

        if (move(key) == false) {         // �̵� ���� �� �ٽ� �õ�
            i--;
            continue;
        }

        display();
        Sleep(50);                       // ���� ���� �ð�ȭ
    }
}


// ���� �Ϸ� ���� �˻�
static bool isDone() {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            // ������� �Ǿ� �ִ��� Ȯ��
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1) && (c == DIM - 1);
        }
    }
    return true;
}


// ����Ű �Է� ó�� �Լ�
static int getDirKey() {
    return _getch() == 224 ? _getch() : 0;
}

static void replayMoves()
{
    printf("\n���÷��� ����...\n");
    Sleep(1000);

    init();              //�ʱ���� �ҷ�����

    for (int i =0; i < moveCount; i++)  //���÷��̿��� ���� ��� ���÷���
    {
        move(moveHistory[i]);
        display();
        Sleep(200);
    }

    printf("\n���÷��� ����\n");
    _getch();
}

// ���� ���� �Լ�
int playFifteenPuzzle() {
    moveCount = 0; //����� ��� �ʱ�ȭ�� ����
    init();        // ���� �ʱ�ȭ
    display();     // ȭ�� ���

    // printRanking(); // ��ŷ ��� (�̱���)

    printf("\n ������ �����ּ���(����)...");
    _getch();      // ���� ���

    shuffle(100);  // ���� ����

    printf("\n ������ ���۵˴ϴ�...");
    _getch();      // ���� ���

    nMove = 0;     
    tStart = clock();  // �ð� ���� ����

    while (!isDone()) {
        move(getDirKey());  // Ű �Է� ó��
        display();
    }

    clock_t t1 = clock();
    double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;

    prntf("���÷��� (Y/N): ");
    char choice = _getch();
    if (choice == 'Y' || choice == 'y')     //Y ���ý� ���÷��� ����
    {
        replayMoves();
    }
    return 0;
}


int main() {
    setlocale(LC_ALL, "Korean"); // �ѱ� ��� ����

    playFifteenPuzzle();
    return 0;
}