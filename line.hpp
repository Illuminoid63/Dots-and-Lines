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
    Line(Point start, Point end);
    Point getStartPoint();
    Point getEndPoint();
    void setStartPoint(Point start);
    void setEndPoint(Point end);
    double calculateLength();
    bool pointOnLine(Point checkPoint);
    bool lineIsParallel(Line checkLine);
    bool lineIntersects(Line checkLine);
    string toString();
};
