#include <iostream>

struct MyTime
{
    int hour;
    int min;
    int sec;
};

void addTime ( MyTime t1, MyTime t2, MyTime* pt );
{
    pt->hour = t1.hour + t2.hour;
    pt->min  = t1.min + t2.min;
    pt->sec  = t1.sec + t2.sec;
}

MyTime t3;
addTime(t1, t2, &t3);           // &t3는 포인터 변수인 주소를 나타내는 곳에서 값을 추출

// t3에 해당하는 주소의 복사를 통해 주소에 데이터를 저장