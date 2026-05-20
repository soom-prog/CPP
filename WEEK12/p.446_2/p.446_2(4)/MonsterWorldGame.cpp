#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include <time.h>

void main()
{
	srand((unsigned int)time(NULL));
	int w = 16, h = 8;
	MonsterWorld game(w, h);

	game.add(new Zombie("허접좀비", "§", rand() % w, rand() % h));
	game.add(new Vampire("뱀파이어짱", "★", rand() % w, rand() % h));
	game.add(new KGhost("어쩌다귀신", "♥", rand() % w, rand() % h));
	game.add(new Jiangshi("못먹어도고", "↔", rand() % w, rand() % h, true));
	game.add(new Jiangshi("못먹어세로", "↕", rand() % w, rand() % h, false));
 	game.add(new Smombi("스몸비", "S", rand() % w, rand() % h));

    // 방향 전환 강시
    game.add(new Siangshi("샹시", "X", rand() % w, rand() % h, true, 5));

    // 폭발 몬스터
    game.add(new Bomber("봄버", "B", rand() % w, rand() % h));

    // 게임 실행
    // (최대 이동 횟수, 속도)
    game.play(500, 50);

    printf("\n------ 게임 종료 ------\n");
}	
