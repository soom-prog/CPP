#include <iostream>
using namespace std;

class Point{
private:                                                                                        // protected:를 private:로
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
        cout << x << ", " << y                                                                  // 이 부분에서 오류 발생 - 자식 클래스에서 private로 인해 x, y의 상속을 받지 못함
             << "에 가로 " << width                                                              // note: declared private here 오류
             << " 세로 "  << height
             << " 인 사각형을 그려라\n";
    }
};

int main() {
    Rectangle value(2,3,100,200);
    value.draw();
}

// protected 지정자는 클래스 내에 있는 모든 자식 클래스가 접근 할 수 있게
// 만들어주지만 private는 상속해주지 않는 지정자로 상속이 이루어 지지 않아
// x, y에 해당하는 호출이 이루어지지 않음