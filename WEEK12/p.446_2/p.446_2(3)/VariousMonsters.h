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

	virtual void move(int** map, int maxx, int maxy) {
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

	virtual void move(int** map, int maxx, int maxy) {
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

	virtual void move(int** map, int maxx, int maxy) {
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

	virtual void move(int** map, int maxx, int maxy) {										// 이동 함수
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

class Siangshi : public Jiangshi {

    int moveCount;												// 현재 이동 횟수

    int changePeriod;											// 방향 변경 주기

public:

    Siangshi(string n = "샹시", string i = "※",					// 생성자
        int x = 0, int y = 0,
        bool bH = true,
        int period = 5)

        : Jiangshi(n, i, x, y, bH) {

        moveCount = 0;
        changePeriod = period;
    }

    ~Siangshi() {												// 소멸자
        cout << " Siangshi";
    }

    virtual void move(int** map, int maxx, int maxy) {					// 이동 함수

        moveCount++;											// 이동 횟수 증가

        if (moveCount % changePeriod == 0)						// 일정 횟수마다 이동 방향 변경
            bHori = !bHori;										// true <-> false 전환

        Jiangshi::move(map, maxx, maxy);						// 부모 클래스의 move 사용
    }
};

class Bomber : public Monster {

	int turnCount;												// 이동 횟수 저장

public:
	Bomber(string n = "봄버", string i = "ⓑ", int x = 0, int y = 0)		// 생성자
		:Monster(n, i, x, y) {

		turnCount = 0;
	}

	~Bomber() {															// 소멸자
		cout << "Bomber";
	}

    void explode(int** map, int maxx, int maxy) {						// 십자 폭발 함수

		int dx[5] = {0, -1, 1, 0, 0};							// 현재위치 포함
		int dy[5] = {0, 0, 0, -1, 1};							// 좌 우 상 하 방향

		for (int i = 0; i < 5; i++){
			int nx = x + dx[i];									// 폭발 위치 계산
			int ny = y + dy[i];

		if (nx >= 0 && nx < maxx &&
                ny >= 0 && ny < maxy) {

                if (map[ny][nx] == 1) {							// 아이템이 있으면 제거

                    map[ny][nx] = 0;

                    nItem++;									// 먹은 아이템 개수 증가
                }
            }
        }
    }

	virtual void move(int** map, int maxx, int maxy) {

        // 랜덤 방향 선택
        int dir = rand() % 4;

        // 이동
        if (dir == 0)
            x++;

        else if (dir == 1)
            x--;

        else if (dir == 2)
            y++;

        else
            y--;

        // 범위 보정
        clip(maxx, maxy);

        // 현재 위치 아이템 먹기
        eat(map);

        // 이동 횟수 증가
        turnCount++;

        // 5턴마다 폭발
        if (turnCount % 5 == 0)
            explode(map, maxx, maxy);
    }
};