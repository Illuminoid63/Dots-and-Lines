#include "line.hpp"
#include <string>
#include <cmath>
#include <limits>

using namespace std;

//Constructor that takes in two points and assigns them to start and end to make a line
Line::Line(Point start, Point end) : startPoint(0, 0), endPoint(0, 0){
    setStartPoint(start);
    setEndPoint(end);
}

//Returns the start point of the line
Point Line::getStartPoint(){
    return startPoint;
}

//Returns the end point of the line
Point Line::getEndPoint(){
    return endPoint;
}

//Sets the start point of the line and updates the slope and intercept of the line
void Line::setStartPoint(Point start){
    startPoint = start;
    deltaX = endPoint.getX() - startPoint.getX();
    deltaY = endPoint.getY() - startPoint.getY();
    slope = findSlope();
    intercept = findIntercept();
}

//Sets the end point of the line and updates the slope and intercept of the line
void Line::setEndPoint(Point end){
    endPoint = end;
    deltaX = endPoint.getX() - startPoint.getX();
    deltaY = endPoint.getY() - startPoint.getY();
    slope = findSlope();
    intercept = findIntercept();
}

//Calculates the length of the line by using the pythagorean theorem. Returns the length as a double
double Line::calculateLength(){
    double retval = sqrt(pow(deltaY, 2) + pow(deltaX, 2));
    return retval;
}

//Checks to see if the passed in point is on the line. Returns true or false
bool Line::pointOnLine(Point checkPoint){
    double result = (slope * checkPoint.getX()) + intercept;
    bool retval = false;
    double greaterX;
    double lesserX;
    double greaterY;
    double lesserY;
    //Finds the bounds of the line
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
    //Checks to make sure that the passed in point is within the bounds of the line and checks to make sure the Y value of the point matches
    //with the corresponding x value on the line. Uses epsilon to account for precision
    if(checkPoint.getX() <= greaterX && checkPoint.getX() >= lesserX && checkPoint.getY() <= greaterY && checkPoint.getY() >= lesserY){
        if(abs(checkPoint.getY() - result) < __DBL_EPSILON__){
            retval = true;
        }
    }
    return retval;
}

//Checks to see if the line passed in is parallel to the implicit line. Returns true or false
bool Line::lineIsParallel(Line checkLine){
    bool retval = false;
    //Checks to see if either line is vertical
    if(isinf(this->slope) && isinf(checkLine.slope)){
        retval = true;
    }
    //Checks to see if the slopes of the two lines are the same. Uses epsilon to account for precision
    else if(abs(this->slope - checkLine.slope) <= __DBL_EPSILON__ && abs(this->intercept - checkLine.intercept) > __DBL_EPSILON__){
        retval = true;
    }
    return retval;
}

//Checks to see if the line passed in intersects the implicit line. Returns true or false
bool Line::lineIntersects(Line checkLine){
    bool retval = false;
    double newSlope;
    double newIntercept;
    double resultX;
    double resultY;
    
    //Checks to see if the two lines are parallel. Returns false if so
    if(lineIsParallel(checkLine)){
        retval = false;
    }
    //Checks to see if one or both of the lines are vertical
    else if(isinf(this->slope) || isinf(checkLine.slope)){
        //If the implicit line is vertical, finds the intercept and checks if the line intersects the passed in line
        if(isinf(this->slope)){
            double greaterY;
            double lesserY;
            double resultY = (this->getStartPoint().getX() * checkLine.slope) + checkLine.intercept;
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
                retval = checkLine.pointOnLine(result);
            }
        }
        //If the passed in line is vertical, finds the intercept and checks if the line intersects the implicit line
        else{
            double greaterY;
            double lesserY;
            double resultY = (checkLine.getStartPoint().getX() * this->slope) + this->intercept;
            if(checkLine.startPoint.getY() > checkLine.endPoint.getY()){
                greaterY = checkLine.startPoint.getY();
                lesserY = checkLine.endPoint.getY();
            }
            else{
                lesserY = checkLine.startPoint.getY();
                greaterY = checkLine.endPoint.getY();
            }

            Point result(checkLine.getStartPoint().getX(), resultY);
            if(resultY <= greaterY && resultY >= lesserY){
                retval = this->pointOnLine(result);
            }
        }
    }
    //If no vertical lines are present, checks to see if the two lines interesect
    else{
        if(checkLine.slope >= 0){
            newSlope = this->slope - checkLine.slope;
        }
        else{
            newSlope = this->slope + checkLine.slope;
        }
        
        if(this->intercept >= 0){
            newIntercept = checkLine.intercept - this->intercept;
        }
        else{
            newIntercept = checkLine.intercept + this->intercept;
        }
        
        resultX = newIntercept / newSlope;
        resultY = (resultX * this->slope) + this->intercept;
        
        Point result(resultX, resultY);
        
        retval = this->pointOnLine(result) && checkLine.pointOnLine(result);
    }
    return retval;
}

//Returns a string representation of the line
string Line::toString(){
    string retval = "Point 1: [" + startPoint.toString() + "], Point 2: [" + endPoint.toString() + "]";
    return retval;
}

//Finds the slope of the line. Returns the slope as a double
double Line::findSlope(){
    double retval = deltaY/deltaX;
    return retval;
}

//Finds the intercept of the line. Returns the intercept as a double
double Line::findIntercept(){
    return startPoint.getY() - (startPoint.getX() * slope);
}
