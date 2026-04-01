#include "Ranking.h"
#include <cstdio>
#include <cstring>
#include <iostream>

#define NUM_MVP 10
static PlayInfo MVP[NUM_MVP];  // 랭킹 배열
static int nMVP = NUM_MVP;     // 배열 크기

// 랭킹 초기화
static void initRanking() {
    PlayInfo noname;
    strcpy(noname.name, "C++ Player");
    noname.nMove = 1000;
    noname.tElapsed = 1000.0;

    for (int i = 0; i < nMVP; i++)
        MVP[i] = noname;
}

// 랭킹 불러오기 (이진 파일)
void loadRanking(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == nullptr) {
        initRanking();
    } else {
        fread(MVP, sizeof(PlayInfo), nMVP, fp);
        fclose(fp);
    }
}

// 랭킹 저장 (이진 파일)
void storeRanking(const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (fp == nullptr) return;
    fwrite(MVP, sizeof(PlayInfo), nMVP, fp);
    fclose(fp);
}

// 랭킹 출력
void printRanking() {
    std::cout << "===== Ranking Board =====\n";
    for (int i = 0; i < nMVP; i++) {
        printf("[%2d]  %4d  %-16s  %5.1f sec\n",
               i + 1, MVP[i].nMove, MVP[i].name, MVP[i].tElapsed);
    }
    std::cout << "=========================\n";
}

// 랭킹 추가
int addRanking(int nMove, double tElap) {
    if (nMove < MVP[nMVP - 1].nMove) { // 마지막보다 작으면 랭킹
        int pos = nMVP - 1;
        for (; pos > 0; pos--) {
            if (nMove >= MVP[pos - 1].nMove) break;
            MVP[pos] = MVP[pos - 1];
        }
        MVP[pos].nMove = nMove;
        MVP[pos].tElapsed = tElap;

        std::cout << "축하합니다! " << pos + 1 << "등입니다. 이름 입력: ";
        scanf("%s", MVP[pos].name);

        return pos + 1;
    }
    return 0;
}