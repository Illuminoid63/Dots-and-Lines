#include "line.hpp"
#include <string>
#include <cmath>
#include <limits>

using namespace std;

Line::Line(Point x, Point y) : startPoint(0, 0), endPoint(0, 0){
    setStartPoint(x);
    setEndPoint(y);
}

Point Line::getStartPoint(){
    return startPoint;
}

Point Line::getEndPoint(){
    return endPoint;
}

void Line::setStartPoint(Point x){
    startPoint = x;
    deltaX = endPoint.getX() - startPoint.getX();
    deltaY = endPoint.getY() - startPoint.getY();
    slope = findSlope();
    intercept = findIntercept();
}

void Line::setEndPoint(Point x){
    endPoint = x;
    deltaX = endPoint.getX() - startPoint.getX();
    deltaY = endPoint.getY() - startPoint.getY();
    slope = findSlope();
    intercept = findIntercept();
}

double Line::calculateLength(){
    double retval = sqrt(pow(deltaY, 2) + pow(deltaX, 2));
    return retval;
}

bool Line::pointOnLine(Point x){
    double result = (slope * x.getX()) + intercept;
    bool retval = false;
    double greaterX;
    double lesserX;
    double greaterY;
    double lesserY;
    if(startPoint.getX() > endPoint.getX()){
        greaterX = startPoint.getX();
        lesserX = endPoint.getX();
    }
    else{
        lesserX = startPoint.getX();
        greaterX = endPoint.getX();
    }
    if(startPoint.getY() > endPoint.getY()){
        greaterY = startPoint.getY();
        lesserY = endPoint.getY();
    }
    else{
        lesserY = startPoint.getY();
        greaterY = endPoint.getY();
    }
    if(x.getX() <= greaterX && x.getX() >= lesserX && x.getY() <= greaterY && x.getY() >= lesserY){
        if(abs(x.getY() - result) < __DBL_EPSILON__){
            retval = true;
        }
    }
    return retval;
}

bool Line::lineIsParallel(Line x){
    bool retval = false;
    if(isinf(this->slope) && isinf(x.slope)){
        retval = true;
    }
    else if(abs(this->slope - x.slope) <= __DBL_EPSILON__ && abs(this->intercept - x.intercept) > __DBL_EPSILON__){
        retval = true;
    }
    return retval;
}

bool Line::lineIntersects(Line x){
    bool retval = false;
    double newSlope;
    double newIntercept;
    double resultX;
    double resultY;
    
    if(lineIsParallel(x)){
        retval = false;
    }
    else if(isinf(this->slope) || isinf(x.slope)){
        if(isinf(this->slope)){
            double greaterY;
            double lesserY;
            double resultY = (this->getStartPoint().getX() * x.slope) + x.intercept;
            if(startPoint.getY() > endPoint.getY()){
                greaterY = startPoint.getY();
                lesserY = endPoint.getY();
            }
            else{
                lesserY = startPoint.getY();
                greaterY = endPoint.getY();
            }

            Point result(this->getStartPoint().getX(), resultY);
            if(resultY <= greaterY && resultY >= lesserY){
                retval = x.pointOnLine(result);
            }
        }
        else{
            double greaterY;
            double lesserY;
            double resultY = (x.getStartPoint().getX() * this->slope) + this->intercept;
            if(x.startPoint.getY() > x.endPoint.getY()){
                greaterY = x.startPoint.getY();
                lesserY = x.endPoint.getY();
            }
            else{
                lesserY = x.startPoint.getY();
                greaterY = x.endPoint.getY();
            }

            Point result(x.getStartPoint().getX(), resultY);
            if(resultY <= greaterY && resultY >= lesserY){
                retval = this->pointOnLine(result);
            }
        }
    }
    else{
        if(x.slope >= 0){
            newSlope = this->slope - x.slope;
        }
        else{
            newSlope = this->slope + x.slope;
        }
        
        if(this->intercept >= 0){
            newIntercept = x.intercept - this->intercept;
        }
        else{
            newIntercept = x.intercept + this->intercept;
        }
        
        resultX = newIntercept / newSlope;
        resultY = (resultX * this->slope) + this->intercept;
        
        Point result(resultX, resultY);
        
        retval = this->pointOnLine(result) && x.pointOnLine(result);
    }
    return retval;
}

string Line::toString(){
    string retval = "Point 1: [" + startPoint.toString() + "], Point 2: [" + endPoint.toString() + "]";
    return retval;
}

double Line::findSlope(){
    double retval = deltaY/deltaX;
    return retval;
}

double Line::findIntercept(){
    return startPoint.getY() - (startPoint.getX() * slope);
}
