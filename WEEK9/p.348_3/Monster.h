#pragma once
#include "Canvas.h"
#define DIM 40

class Monster {
	string name, icon;	// 몬스터 이름과 화면 출력용 아이콘
	int x, y, nItem;		// 현재 위치와 먹은 아이템의 수
	int nEnergy;			// (1) 에너지 저장함수 추가

	void clip(int maxx, int maxy) {
		if (x < 0) x = 0;
		if (x >= maxx) x = maxx - 1;
		if (y < 0) y = 0;
		if (y >= maxy) y = maxy - 1;
	}
	void eat(int map[DIM][DIM]) {
		if (map[y][x] == 1) {
			map[y][x] = 0;
			nItem++;
			nEnergy += 8;		// (3) 아이템을 먹으면 에너지 8증가
		}
	}
public:
	Monster(string n = "나괴물", string i = "※", int px = 0, int py = 0)
		: name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) {}
	~Monster() { cout << "\t" << name << icon << " 물러갑니다~~~\n"; }
	
	void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
	void move(int map[DIM][DIM], int maxx, int maxy) {
		switch (rand() % 8) {
		case 0: y--; break;
		case 1: x++; y--; break;
		case 2: x++; break;
		case 3: x++; y++; break;
		case 4: y++; break;
		case 5: x--; y++; break;
		case 6: x--; break;
		case 7: x--; y--; break;
		}


		clip(maxx, maxy);

		int beforeItem = nItem;		// 먹기 전의 상태 저장		(3)

		eat(map);

		if (nItem == beforeItem)	// 못먹으면 에너지 -1
			nEnergy--;

		if (nEnergy < 0)			// 에너지의 최소값 0 제한
			nEnergy = 0;
	}
	void print() {
		cout << "\t" << name << icon
			 << " item:" << nItem
			 << " energy:" << nEnergy;

		if (nEnergy >= 80)
			cout << " [HIGH]";
		else if (nEnergy >= 40)
			cout << " [MID]";
		else if (nEnergy > 0)
			cout << " [LOW]";
		else
			cout << " [DEAD]";			//(4) 현재의 에너지 레벨 출력

		cout << endl;
	}
	bool isDead() {
    return nEnergy <= 0;
	}
};