#pragma once
#include <iostream>
#include <string>
#include "point.h"

using namespace std;

class Line{
    private:
    Point startPoint;
    Point endPoint;
    double slope;
    double deltaY;
    double deltaX;
    double intercept;
    double findSlope();
    double findIntercept();
    public:
    Line(Point x, Point y);
    Point getStartPoint();
    Point getEndPoint();
    void setStartPoint(Point x);
    void setEndPoint(Point x);
    double calculateLength();
    bool pointOnLine(Point x);
    bool lineIsParallel(Line x);
    bool lineIntersects(Line x);
    string toString();
};
