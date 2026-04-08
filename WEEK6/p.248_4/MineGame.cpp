#include "MineGame.hpp"
int main()
{
	int width, height;
	int total;

	printf(" <Mine Game>\n");


	printf("맵 크기 입력 (가로 세로): ");
	scanf("%d %d", &width, &height);
	if (width > 80) width = 80;
	if (height > 40) height = 40;
	if (width <= 0) width = 1;
	if (height <= 0) height = 1;

	nx = width;
	ny = height;

	printf(" 매설할 총 지뢰의 개수 : ");
	scanf("%d", &total);
	playMineSweeper(total);

	return 0;

}