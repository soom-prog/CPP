#include <iostream>

struct MyTime
{
    int hour;
    int min;
    int sec;
};

MyTime addTime(MyTime t1, MyTime t2)
{
    MyTime result;
    result.hour = t1.hour + t2.hour;
    result.min  = t1.min + t2.min;
    result.sec  = t1.sec + t2.sec;

    return result;

}

MyTime t3 = addTime(t1, t2);

//t3라는 곳에 return을 이용해 값을 복사하여 결과 도출