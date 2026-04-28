#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;
    Complex(double r=0, double i=0) : real(r), imag(i) {}

    void print() const {
        cout << real << " + " << imag << "i\n";
    }
};

void add(Complex& a, Complex& b, Complex& c) {
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
}

int main() {
    cout << "\n1. 일반 함수, void, 참조 전달\n";
    Complex a(1,2), b(3,4), c;
    add(a,b,c);
    c.print(); // 4 + 6i
}