/*
Para compilar: 
g++ -o prueba clases.cpp
Para ejecutar: 
./prueba
*/
#include <iostream>
using namespace std;

class Point {
    private:
        int x; // private: only Point
        int y; // may touch these
 public:
    Point(int px, int py) : x(px), y(py) {} // constructor
    void move(int dx, int dy) { // member function
        x += dx; y += dy;
    }
        int getX() const { return x; } // const: cannot modify
    };

    int main() {
        Point p(3, 7); // an object of type Point
        p.move(1, 1); // p is now (4, 8)

        Point* pp = &p; // a pointer to that same object
        pp->move(1, 1); // same call through pp: p is now (5, 9)
        cout << "David M " << p.getX() << endl;
 // p.x = 99; // rejected: x is private
    }
