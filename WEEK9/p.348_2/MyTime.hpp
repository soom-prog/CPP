#pragma once
#include <iostream>

class MyTime
{
private:
    int hour;
    int min;
    int sec;
    int ms;
    
public:

    MyTime();                                   //기본 생성자

    MyTime(int h, int m, int s, int ms);        //매개변수 생성자

    MyTime(double duration);                    // 헤더파일에 생성자 추가

    void convert(double duration);
    void print();
    MyTime add (MyTime t);
    void reset();
    void read();
};