#pragma once
#include "Monster.h"

class Zombie : public Monster {
public:
	Zombie(string n = "허접좀비", string i = "§", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

class Vampire : public Monster {
public:
	Vampire(string n = "뱀파이어", string i = "★", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }

	void move(int** map, int maxx, int maxy) {
		int dir = rand() % 4;
		if (dir == 0) x--;
		else if (dir == 1) x++;
		else if (dir == 2) y--;
		else y++;
		clip(maxx, maxy);
		eat(map);
	}
};

class KGhost : public Monster {
public:
	KGhost(string n = "처녀귀신", string i = "♥", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }

	void move(int** map, int maxx, int maxy) {
		x = rand() % maxx;
		y = rand() % maxy;
		clip(maxx, maxy);
		eat(map);
	}
};

class Jiangshi : public Monster {
	bool bHori;
public:
	Jiangshi(string n = "대륙강시", string i = "↔", int x = 0, int y = 0, bool bH = true)
		: Monster(n, i, x, y), bHori(bH) {}
	~Jiangshi() { cout << " Jiangshi"; }

	void move(int** map, int maxx, int maxy) {
		int dir = rand() % 2;
		int jump = rand() % 2 + 1;
		if (bHori) x += ((dir == 0) ? -jump : jump);
		else y += ((dir == 0) ? -jump : jump);
		clip(maxx, maxy);
		eat(map);
	}
};

class Smombi : public Monster {
public:
	Smombi(string n = "스몸비", string i = "X", int x = 0, int y =0)				// 생성자
		: Monster(n, i, x, y) {}
	~Smombi() { cout << "Smombi"; }													// 소멸자

	void move(int** map, int maxx, int maxy) {										// 이동 함수
		int dir = rand() % 4;														// 4개의 대각선 방향 중 하나 선택하는

		switch (dir) {
			case 0:																	// 오른쪽 아래
				x++;
				y++;
				break;
			case 1:																	// 오른쪽 위
				x++;
				y--;
				break;
			case 2:																	// 왼쪽 아래
				x--;
				y++;
				break;
			case 3:																	// 왼쪽 위
				x--;
				y--;
				break;
		}

		clip(maxx, maxy);															// 맵 범위 벗어나지 않게 보정 시킴
		eat(map);																	// 아이템 먹기
	}
};