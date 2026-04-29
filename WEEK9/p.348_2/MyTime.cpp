#include "MyTime.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

MyTime::MyTime() : hour(0), min(0), sec(0), ms(0) {}    // 멤버 초기화 리스트 사용

MyTime::MyTime(int h, int m, int s, int ms)
    : hour(h), min(m), sec(s), ms(ms)
{
    sec += this->ms / 1000;
    this->ms %= 1000;

    min += sec / 60;
    sec %= 60;

    hour += min / 60;
    min %= 60;
}

MyTime::MyTime(double duration)
{
    // 시간
    hour = (int)(duration / 3600);
    duration -= hour * 3600;

    // 분
    min = (int)(duration / 60);
    duration -= min * 60;

    // 초
    sec = (int)duration;
    duration -= sec;

    // 밀리초
    ms = (int)((duration - sec) * 1000);
}

void MyTime::print()
{
    cout << setfill('0')                            // 입출력 조작자를 사용해 빈자리 자릿수 0으로 만듦
      << setw(2) << hour << ":"                     // 00:00:00을 위한 시간, 분 뒤에 ':' 표시
      << setw(2) << min << ":"
      << setw(2) << sec << ":"
      << setw(3) << ms << endl;
}

MyTime MyTime::add(MyTime t)
{
    MyTime result;

    result.hour = hour + t.hour;
    result.min  = min + t.min;
    result.sec  = sec + t.sec;
    result.ms   = ms  + t.ms;

    if (result.ms >= 1000)
    {
        result.sec += result.ms / 1000;
        result.ms %= 1000;
    }

    if (result.sec >= 60)                           // 값이 60 이상이면
    {
        result.min += result.sec / 60;              // 60으로 나눈 몫을 시간에 더함  
        result.sec %= 60;                           // 나눈 나머지는 분에 저장
    }

    if (result.min >= 60)
    {
        result.hour += result.min / 60;
        result.min %= 60;
    }

    return result;
}

void MyTime::reset()                                // 실행시 설정시간 초기화
{
    hour = 0;
    min = 0;
    sec = 0;
    ms = 0;
}

void MyTime::read()                                 // 헤더에서 void read()를 포함시켜 시간 입력할 수 있게 해줌
{
    cout << "시 입력: ";
    cin >> hour;

    cout << "분 입력: ";
    cin >> min;

    cout << "초 입력: ";
    cin >> sec;

    cout << "밀리초 입력: ";
    cin >> ms;
}

int main()                                          // main 함수를 사용해 호출
{
    MyTime t1, t2, t3;

    t1.read();
    t2.read();

    t3 = t1.add(t2);

    cout << "합 결과: ";
    t3.print();
}