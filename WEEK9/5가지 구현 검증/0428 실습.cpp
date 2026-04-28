#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;

    Complex(double r=0, double i=0) : real(r), imag(i) {}

    void print() const {
        cout << real << " + " << imag << "i\n";
    }

    // 3. 멤버 함수 (void)
    void add(Complex a, Complex b) {
        real = a.real + b.real;
        imag = a.imag + b.imag;
    }

    // 4. 멤버 함수 (return)
    Complex add(Complex b) const {
        return Complex(real + b.real, imag + b.imag);
    }

    // 5. 연산자 오버로딩
    Complex operator+(Complex b) const {
        return Complex(real + b.real, imag + b.imag);
    }
};

int main() {

    cout << "\n1. 일반 함수, void\n";
    Complex a1(1,2), b1(3,4), c1;
    c1.real = a1.real + b1.real;
    c1.imag = a1.imag + b1.imag;
    c1.print();

    cout << "\n2. 일반 함수, return\n";
    Complex a2(1,2), b2(3,4);
    Complex c2( a2.real + b2.real, a2.imag + b2.imag );
    c2.print();

    cout << "\n3. 멤버 함수, void\n";
    Complex a3(1,2), b3(3,4), c3;
    c3.add(a3, b3);
    c3.print();

    cout << "\n4. 멤버 함수, return\n";
    Complex a4(1,2), b4(3,4);
    Complex c4 = a4.add(b4);
    c4.print();

    cout << "\n5. 연산자 오버로딩\n";
    Complex a5(1,2), b5(3,4);
    Complex c5 = a5 + b5;
    c5.print();

    return 0;
}