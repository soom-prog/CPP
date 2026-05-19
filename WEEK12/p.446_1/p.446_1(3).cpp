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
public:
    Rectangle(int xx, int yy, int w, int h)
        : Point(xx, yy), width(w), height(h){ }

    void draw() {
        cout << x << ", " << y
             << "에 가로 " << width
             << " 세로 "  << height
             << " 인 사각형을 그려라\n";
    }
};

int main() {
    Rectangle value(2,3,100,200);
    value.draw();
}