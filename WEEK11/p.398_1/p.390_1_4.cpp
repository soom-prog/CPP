#include <cstdio>
#include <iostream>
using namespace std;

class Sample{
    char *name;
    static int count;                                        // Sample의 객체의 개수 저장 함수
public:
    Sample()                                                 // 객체가 생성이 될 때마다 개수 증가
    {
        count++;
        cout << "일반 생성자++" << endl;
    }

    Sample(const Sample& copy)
    {
        count++;
        cout <<"복사 생성자++" << endl;
    }
    static void printCount()
    {
        cout << "객체의 개수: " << count << endl;             // 객체의 개수 라는 글과 숫자까지 화면에 플로팅
    }
};

int Sample::count = 0;

int main(){
    Sample a;                                               // 일반 생성자
    Sample b(a);                                            // 복사 생성자

    Sample::printCount();

    return 0;
}