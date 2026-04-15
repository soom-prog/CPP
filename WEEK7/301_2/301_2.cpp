#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAXWORDS 100                            // 최대 단어의 개수 제한 - 프로그램 무한 실행 막기위함

struct WordPair                                 // 영어 단어와 한글 뜻을 하나로 묶는 자료형 (클래스)-(1)
{
    string eng;                                 // 영어단어
    string kor;                                 // 한글 뜻
};

class MyDic
{
    WordPair words[MAXWORDS];
    int nWords;

public:
    MyDic() {
        nWords = 0;                             // 생성 시 단어 개수 초기화
    }

    void add(string eng, string kor)           // 단어를 단어장에 추가
    {
        if (nWords >= MAXWORDS) return;

        words[nWords].eng = eng;
        words[nWords].kor = kor;
        nWords++;
    }

    void load(string filename) {
        ifstream fin(filename);                 // 파일 읽기 전용

        if (!fin)
        {
            cout << "파일 열기 실패\n";
            return;
        }

        nWords = 0;                             // 기존 데이터 초기화

        while (fin >> words[nWords].eng >> words[nWords].kor)
        {
            nWords++;
        }

        fin.close();                            // 파일 닫기
    }

    void store(string filename)
    {
        ofstream fout(filename);                // 파일 "쓰기" 전용

        if (!fout)
        {
            cout << "파일 저장 실패\n";
            return;
        }
        for (int i = 0; i < nWords; ++i)        // cout처럼 파일에 출력 가능
        {
            fout << words[i].eng << " "
                << words[i].kor << endl;
        }

        fout.close();                           // 파일 닫기
    }

    void print()                                // 출력
    {
        for (int i = 0; i < nWords; ++i)
        {
            cout << i << ": "
                << words[i].eng << " - "
                << words[i].kor << endl;
        }
    }
    string getEng(int id)                       // 영어 반환 
    {
        if (id >= 0 && id < nWords)             // 특정 위치 영어단어 꺼내기
            return words[id].eng;
        return "";
    }
     string getKor(int id)                      // 한글 반환
    {
        if (id >= 0 && id < nWords)             // 특정 위치 한글 뜻 꺼냄
            return words[id].kor;
        return "";                              // 잘못된 번호일때 빈 문자 출력
    }
};

int main()
{
    MyDic dic;                                  // 단어장 생성

    cout << "--- 단어 등록 ---\n";
    dic.add("Apple", "사과");
    dic.add("Banana", "바나나");
    dic.add("Melon", "멜론");
    dic.add("Orange", "오렌지");

    cout << "\n--- 현재 단어 ---\n";
    dic.print();

    cout << "\n--- 파일 저장 ---\n";
    dic.store("Dic.txt");

    MyDic dic2;

    cout << "\n--- 파일에서 불러오기 ---\n";
    dic2.load("Dic.txt");                               // Dic 텍스트 파일에 등록했던 단어 저장

    dic2.print();

    cout << "\n--- 특정 단어 확인 ---\n";                 // (숫자)를 통해 저장된 숫자 위치에 단어 및 한글 뜻 추출
    cout << "0번: " << dic2.getEng(0)
        << " - " << dic2.getKor(0) << endl;

    cout << "3번: " << dic2.getEng(3)
        << " - " << dic2.getKor(3) << endl;

    return 0;
}