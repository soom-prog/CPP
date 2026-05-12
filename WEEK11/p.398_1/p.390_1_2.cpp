#include <cstring>
#include <iostream>
using namespace std;

class Sample{
    char *name;

public:
    Sample(const char *name) {
        this->name = new char [name];                      // this 포인터 사용 방법 모르겠음
        strcpy(this->name, name);
    }

    void printName()
    {
        cout << name << endl;             // 객체의 개수 라는 글과 숫자까지 화면에 플로팅
    }
};


int main(){
    Sample a("Sample");
    Sample b(a);
    a.printName();

    return 0;
}