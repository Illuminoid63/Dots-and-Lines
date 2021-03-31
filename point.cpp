#include "point.h"
#include <string>
#include <cmath>

using namespace std;

Point::Point(double x, double y)
{
    setX(x);
    setY(y);
}
void Point::setX(double x) 
{
    if(x < 0) //output error message if point is in negative quadrant, 0 is default value
    {
        X = 0;
        cout << "Error, points cannot have negative values" << endl; 
    }
    else{
        X = x;
    }
}
void Point::setY(double y)
{
    if(y < 0)//output error message if point is in negative quadrant, 0 is default value
    {
        Y = 0;
        cout << "Error, points cannot have negative values" << endl; 
    }
    else{
        Y = y;
    }
}
double Point::getX()
{
    return X;
}
double Point::getY()
{
    return Y;
}
string Point::toString() 
{
    string retval = "";
    retval += "X: ";
    string roundedX = to_string(floor(getX() * 10) / 10); //round x to one deciaml point and then converts it to a string
    roundedX.erase(roundedX.find_last_not_of('0') + 1, string::npos); //eliminates tailing zeros after decimal percision

    if(roundedX.at(roundedX.length() - 1) == '.'){ //because we eliminated tailing zeros, whole numbers would return 2. instead of 2.0, so we append a "0" if the last char in the rounded string is "."
        roundedX.append("0");
    }

    retval += roundedX;
    retval += ", Y: ";
    string roundedY = to_string(floor(getY() * 10) / 10);//round x to one deciaml point and then converts it to a string
    roundedY.erase(roundedY.find_last_not_of('0') + 1, string::npos);//eliminates tailing zeros after decimal percision

    if(roundedY.at(roundedY.length() - 1) == '.'){//because we eliminated tailing zeros, whole numbers would return 2. instead of 2.0, so we append a "0" if the last char in the rounded string is "."
        roundedY.append("0");
    }

    retval += roundedY;
    return retval;
}
