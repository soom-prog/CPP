#include "MyTime.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

void MyTime::convert(double duration)
{
    hour = (int)(duration / 3600);
    duration -= hour * 3600;
    min = (int)(duration / 60);
    duration -= min * 60;
    sec = (int)(duration / 60);
}

void MyTime::print()
{
    cout << setfill('0')
      << setw(2) << hour << ":"
      << setw(2) << min << ":"
      << setw(2) << sec << endl;
}

MyTime MyTime::add(MyTime t)
{
    MyTime result;

    result.hour = hour + hour;
    result.min  = min + min;
    result.sec  = sec + sec;

    if (result.min >=60)
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

void MyTime::reset()
{
    hour = 0;
    min = 0;
    sec = 0;
}

void MyTime::read()
{
    cout << "시 입력: ";
    cin >> hour;

    cout << "분 입력: ";
    cin >> min;

    cout << "초 입려기 ";
    cin >> sec;
}

int main()
{
    MyTime t1, t2, t3;

    t1.read();
    t2.read();

    t3 = t1.add(t2);

    cout << "합 결과: ";
    t3.print();
}