#pragma once
#include <iostream>

using namespace std; 

class Point{
    private:
    double X;
    double Y;

    public:
    Point(double x, double y);
    double getX();
    double getY();
    void setX(double x);
    void setY(double y);
    string toString();
};