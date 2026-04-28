#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;
    Complex(double r=0, double i=0) : real(r), imag(i) {}

    void print() const {
        cout << real << " + " << imag << "i\n";
    }

    Complex operator+(const Complex& b) const {
        return Complex(real + b.real, imag + b.imag);
    }
};

int main() {
    cout << "\n5. 연산자 오버로딩\n";
    Complex a(1,2), b(3,4);
    Complex c = a+b;
    c.print(); // 4 + 6i
}