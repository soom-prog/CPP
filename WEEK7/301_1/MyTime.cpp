#include "MyTime.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

void MyTime::convert(double duration)
{
    hour = (int)(duration / 3600);                  // sec * 3600 = hour
    duration -= hour * 3600;
    min = (int)(duration / 60);                     // sec * 60 = min
    duration -= min * 60;
    sec = (int)(duration / 60);                     // 남은 시간
}

void MyTime::print()
{
    cout << setfill('0')                            // 입출력 조작자를 사용해 빈자리 자릿수 0으로 만듦
      << setw(2) << hour << ":"                     // 00:00:00을 위한 시간, 분 뒤에 ':' 표시
      << setw(2) << min << ":"
      << setw(2) << sec << endl;
}

MyTime MyTime::add(MyTime t)
{
    MyTime result;                                  // 지난주 발표했던 내용인 add -> 임의로 선택한 두 시간의 덧셈

    result.hour = hour + hour;
    result.min  = min + min;
    result.sec  = sec + sec;

    if (result.min >=60)                            // 시간을 제외한 분, 초가 60을 넘기면 60초는 1분, 60분은 1시간으로 if문을 사용해서 지정해줌
    {
        result.min -= 60;
        result.hour++;
    }
    if (result.sec >=60)
    {
        result.sec -= 60;
        result.min++;
    }

    return result;
}

void MyTime::reset()                                // 실행시 설정시간 초기화
{
    hour = 0;
    min = 0;
    sec = 0;
}

void MyTime::read()                                 // 헤더에서 void read()를 포함시켜 시간 입력할 수 있게 해줌
{
    cout << "시 입력: ";
    cin >> hour;

    cout << "분 입력: ";
    cin >> min;

    cout << "초 입려기 ";
    cin >> sec;
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