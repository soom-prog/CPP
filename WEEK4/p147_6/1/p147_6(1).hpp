#include <cstdio>
#include <cstdlib>      //rand()함수 사용을 위해 라이브러리에서 가져옴
#include <ctime>        //time()함수 사용을 위해 라이브러리에서 가져옴
extern double tElapsed; //게임의 소요시간 계산, extern으로 선언
extern double playSpeedPlus(int nPlay);