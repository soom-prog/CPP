#include <iostream>

struct MyTime
{
    int hour;
    int min;
    int sec;
};

void addTime ( MyTime t1, MyTime t2, MyTime& t3 );
{
    t3.hour = t1.hour + t2.hour;
    t3.min  = t1.min + t2.min;
    t3.sec  = t1.sec + t2.sec;
}

MyTime t3;
addTime(t1, t2, t3);

// 저장 방법의 차이로 t3에 해당하는 메모리에 더한 값을 직접 저장하는 방식