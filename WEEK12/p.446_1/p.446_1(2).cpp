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
};

int main() {
    cout << "< Rectangle 에서 width, height 초기화 및 상속 >";
}