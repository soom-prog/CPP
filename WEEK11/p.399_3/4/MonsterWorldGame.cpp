#include "MonsterWorld.h"
#include "Monster.h"

#include <time.h>
#include <cstdlib>
#include <cstdio>

int Monster::nMonsters = 0;

int main()
{
	srand((unsigned int)time(NULL));

	int w = 16;
	int h = 8;

	MonsterWorld game(w, h);

	game.add(new Monster("몬스터",
		"※",
		rand() % w,
		rand() % h));

	game.add(new Monster("도깨비",
		"§",
		rand() % w,
		rand() % h));

	game.add(new Monster("별그대",
		"★",
		rand() % w,
		rand() % h));

	game.add(new Monster("고스트",
		"▼",
		rand() % w,
		rand() % h));

	game.play(500, 10);

	printf("------게임 종료-------------------\n");

	return 0;
}