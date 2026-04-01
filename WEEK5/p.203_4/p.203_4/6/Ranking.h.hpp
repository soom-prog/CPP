#pragma once
#include <cstdio>
#include <cstdlib>

struct PlayInfo {
    char    name[200];   // 플레이어 이름
    int     nMove;       // 이동 횟수
    double  tElapsed;    // 경과 시간
};

extern void loadRanking(const char* filename);
extern void storeRanking(const char* filename);
extern void printRanking();
extern int addRanking(int nMove, double tElap);