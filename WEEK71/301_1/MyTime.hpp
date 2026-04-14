#pragma once
#include <iostream>

class MyTime
{
private:
    int hour;
    int min;
    int sec;
    
public:
    void convert(double duration);
    void print();
    MyTime add (MyTime t);
    void reset();
    void read();
};