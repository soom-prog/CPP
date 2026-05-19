#include <iostream>
using namespace std;

class Point{
protected:
    int x, y;
public:
    Point(int xx, int yy) : x(xx), y(yy){ }
    void draw() {
        std::cout << x << "," << y << "에 점을 그려라.\n";
    }
};

class Rectangle : public Point{
private:
    int width;
    int height;
};

int main() {
    cout << "< Rectangle 상속> ";
}