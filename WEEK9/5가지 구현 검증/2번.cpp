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

Complex add(Complex a, Complex b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}

int main() {
    cout << "\n2. 일반 함수, return, 값 전달\n";
    Complex a(1,2), b(3,4);
    Complex c = add(a,b);
    c.print(); // 4 + 6i
}