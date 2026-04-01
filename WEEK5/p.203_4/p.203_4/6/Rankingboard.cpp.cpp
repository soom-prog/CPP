#include "Ranking.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand((unsigned int)time(NULL));

    // 랭킹 로드 (없으면 초기화)
    loadRanking("ranking.bin");
    printRanking();

    // 임의 데이터 추가 (테스트용)
    for (int i = 0; i < 5; i++) {
        int move = rand() % 500 + 1;           // 1~500 이동
        double timeElapsed = (rand() % 1000) * 0.1;  // 0~100초
        addRanking(move, timeElapsed);
    }

    // 랭킹 저장 (이진 파일)
    storeRanking("ranking.bin");

    printRanking(); // 저장 후 결과 확인
    return 0;
}