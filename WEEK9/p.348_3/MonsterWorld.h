#pragma once
#include "Canvas.h"
#include "Monster.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define DIM  40
#define MAXMONS 5

class MonsterWorld {
	int map[DIM][DIM];
	int xMax, yMax, nMon, nMove;
	Monster mon[MAXMONS];
	Canvas	canvas;

	int& Map(int x, int y) { return map[y][x]; }
	bool isDone() { return countItems() == 0; }
	int countItems() {
		int nItems = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) nItems++;
		return nItems;
	}

	bool anyDead() {
    for (int i = 0; i < nMon; i++)
        if (mon[i].isDead())
            return true;
    return false;
	}

	void print() {
		canvas.clear();
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0) canvas.draw(x, y, "■");
		for (int i = 0; i < nMon; i++)
			mon[i].draw(canvas);
		canvas.print("[ Monster World (Basic) ]");

		cerr << " 전체 이동 횟수 = " << nMove << endl;
		cerr << " 남은 아이템 수 = " << countItems() << endl;
		for (int i = 0; i < nMon; i++)
			mon[i].print();
	}
public:
	MonsterWorld(int w, int h) : canvas(w, h), xMax(w), yMax(h) {
		nMon = 0;
		nMove = 0;
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++) Map(x, y) = 1;
	}
	~MonsterWorld() { }
	void add(const Monster& m) {
		if (nMon < MAXMONS) mon[nMon++] = m;
	}
void play(int maxwalk, int wait) {
    print();
    cerr << " 엔터를 누르세요...";
    getchar();

    for (int i = 0; i < maxwalk; i++) {

        for (int k = 0; k < nMon; k++)
            mon[k].move(map, xMax, yMax);

        nMove++;
        print();

        // 아이템 다 먹으면 종료
        if (isDone()) break;

        // 한 명이라도 DEAD면 게임 중단
        if (anyDead()) {
            cerr << "\n 한 몬스터가 DEAD 상태입니다. 게임을 종료합니다...\n";
            break;
        }

        Sleep(wait);
    }

    cerr << "\n 게임이 종료되었습니다. 엔터를 누르면 닫힙니다...";
    getchar();
	}
};