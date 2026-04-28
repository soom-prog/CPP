#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;
    Complex(double r=0, double i=0) : real(r), imag(i) {}

    void print() const {
        cout << real << " + " << imag << "i\n";
    }

    void add(Complex& a, Complex& b); // 선언
};

// 정의
void Complex::add(Complex& a, Complex& b) {
    real = a.real + b.real;
    imag = a.imag + b.imag;
}

int main() {
    cout << "\n3. 멤버 함수, void, 참조 전달\n";

    Complex a(1,2), b(3,4), c;
    c.add(a,b);

    c.print(); // 4 + 6i
}