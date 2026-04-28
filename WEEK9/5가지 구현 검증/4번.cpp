#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;
    Complex(double r=0, double i=0) : real(r), imag(i) {}

    void print() const {
        cout << real << " + " << imag << "i\n";
    }

    Complex add(Complex& b) const {
        return Complex(real + b.real, imag + b.imag);
    }
};

int main() {
    cout << "\n4. 멤버 함수, return, 참조 전달\n";
    Complex a(1,2), b(3,4);
    Complex c = a.add(b);
    c.print(); // 4 + 6i
}