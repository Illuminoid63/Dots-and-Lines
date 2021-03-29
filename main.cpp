#include <iostream> 
#include "point.h"
#include "line.hpp"

using namespace std; 
 
#define CATCH_CONFIG_MAIN   
#include "catch.hpp" 
 

 
TEST_CASE("Test Point")  
{ 
    Point mypoint(1.2,3.4);

    SECTION("Getters")
    {
        REQUIRE(mypoint.getX() == 1.2);
        REQUIRE(mypoint.getY() == 3.4);
    }

    SECTION("Setters")
    {
        mypoint.setX(3.4);
        mypoint.setY(1.2);

        REQUIRE(mypoint.getX() == 3.4);
        REQUIRE(mypoint.getY() == 1.2);

        mypoint.setX(-3.4);
        mypoint.setY(-1.2);

        REQUIRE(mypoint.getX() == 0);
        REQUIRE(mypoint.getY() == 0);
    }

    SECTION("toString")
    {
        REQUIRE(mypoint.toString() == "X: 1.2, Y: 3.4");

        Point longDecimal(1.234, 3.543642);
        REQUIRE(longDecimal.toString() == "X: 1.2, Y: 3.5");

        Point wholeNumber(2, 5);
        REQUIRE(wholeNumber.toString() == "X: 2.0, Y: 5.0");

        Point wholeBigNumber(10, 50);
        REQUIRE(wholeBigNumber.toString() == "X: 10.0, Y: 50.0");

        Point wierdDouble(1.05, 3.01);
        REQUIRE(wierdDouble.toString() == "X: 1.0, Y: 3.0");
    }
}

//------------------------------------------------------------------------
TEST_CASE("Test Line")
{
    Point start(1.2, 3.4);
    Point end(5.6, 7.8);
    
    Line myLine(start, end);
    
    SECTION("Getters"){
        REQUIRE(myLine.getStartPoint().getX() == 1.2);
        REQUIRE(myLine.getStartPoint().getY() == 3.4);
        REQUIRE(myLine.getEndPoint().getX() == 5.6);
        REQUIRE(myLine.getEndPoint().getY() == 7.8);
    }
    
    SECTION("Setters"){
        Point testPoint1(3.4, 1.2);
        Point testPoint2(7.8, 5.6);
        myLine.setStartPoint(testPoint1);
        myLine.setEndPoint(testPoint2);
        
        REQUIRE(myLine.getStartPoint().getX() == 3.4);
        REQUIRE(myLine.getStartPoint().getY() == 1.2);
        REQUIRE(myLine.getEndPoint().getX() == 7.8);
        REQUIRE(myLine.getEndPoint().getY() == 5.6);
    }
    
    SECTION("Length"){
        REQUIRE(myLine.calculateLength() - 6.222 < .001);
        
        Point testPoint1(3.4, 1.2);
        Point testPoint2(7.8, 5.6);
        Line testLine1(testPoint1, testPoint2);
        
        REQUIRE(testLine1.calculateLength() - 6.222 < .001);
        
        Point testPoint3(7.8, 5.6);
        Point testPoint4(3.4, 1.2);
        Line testLine2(testPoint3, testPoint4);
        
        REQUIRE(testLine2.calculateLength() - 6.222 < .001);
        
        Point testPoint5(5, 1);
        Point testPoint6(5, 6);
        Line testLine3(testPoint5, testPoint6);
        
        REQUIRE(testLine3.calculateLength() - 5 < .001);
        
        Point testPoint7(1.5, 5.6);
        Point testPoint8(1.5, 5.6);
        Line testLine4(testPoint7, testPoint8);
        
        REQUIRE(testLine4.calculateLength() - 0 < .001);
    }
    
    SECTION("Point on line"){
        Point testPoint1(2, 4.2);
        REQUIRE(myLine.pointOnLine(testPoint1) == true);
        
        Point testPoint2(6, 8.2);
        REQUIRE(myLine.pointOnLine(testPoint2) == false);
        
        Point testPoint3(.5, 2.7);
        REQUIRE(myLine.pointOnLine(testPoint3) == false);
        
        Point testPoint4(1.2, 3.4);
        REQUIRE(myLine.pointOnLine(testPoint4) == true);
        
        Point testPoint5(3, 5);
        REQUIRE(myLine.pointOnLine(testPoint5) == false);
    }
    
    SECTION("Parallel"){
        Point testPoint1(1, 1);
        Point testPoint2(3, 3);
        Line testLine1(testPoint1, testPoint2);
        
        REQUIRE(myLine.lineIsParallel(testLine1) == true);
        
        Point testPoint3(1, 1);
        Point testPoint4(3, 3);
        Line testLine2(testPoint4, testPoint3);
        
        Point testPoint5(1.2, 3.4);
        Point testPoint6(5.6, 7.8);
        Line testLine3(testPoint6, testPoint5);
        
        REQUIRE(testLine3.lineIsParallel(testLine2) == true);
        REQUIRE(myLine.lineIsParallel(testLine3) == true);
        
        Point testPoint7(1, 1);
        Point testPoint8(3, 3);
        Line testLine4(testPoint7, testPoint8);
        
        REQUIRE(testLine4.lineIsParallel(testLine4) == false);
        
        Point testPoint9(1, 1);
        Point testPoint10(1, 3);
        Point testPoint11(2, 1);
        Point testPoint12(2, 3);
        Line testLine5(testPoint9, testPoint10);
        Line testLine6(testPoint11, testPoint12);
        
        REQUIRE(testLine5.lineIsParallel(testLine6) == true);
        
        Point testPoint13(2, 1);
        Point testPoint14(2, 3);
        Line testLine7(testPoint13, testPoint14);
        
        REQUIRE(myLine.lineIsParallel(testLine7) == false);
        
        
    }
    
    SECTION("Intersect"){
        
        Point testPoint1(2.8, 1);
        Point testPoint2(2.8, 8);
        Line testLine1(testPoint1, testPoint2);
        
        REQUIRE(myLine.lineIntersects(testLine1) == true);
        
        Point testPoint3(1, 1);
        Point testPoint4(3, 3);
        Line testLine2(testPoint3, testPoint4);
        
        REQUIRE(myLine.lineIntersects(testLine2) == false);
        
        Point testPoint5(1, 1);
        Point testPoint6(1, 8);
        Line testLine3(testPoint5, testPoint6);
        
        REQUIRE(myLine.lineIntersects(testLine3) == false);
        
        
        Point testPoint7(0, 5);
        Point testPoint8(10, 5);
        Line testLine4(testPoint7, testPoint8);
        
        REQUIRE(myLine.lineIntersects(testLine4) == true);
        
        Point testPoint9(2, 3.4);
        Point testPoint10(5, 3.4);
        Line testLine5(testPoint9, testPoint10);
        
        REQUIRE(myLine.lineIntersects(testLine5) == false);
        
        
    }

    SECTION("toString"){
        REQUIRE(myLine.toString() == "Point 1: [X: 1.2, Y: 3.4], Point 2: [X: 5.6, Y: 7.8]");
        
        Point testPoint1(1, 2);
        Point testPoint2(3, 4);
        Line testLine1(testPoint1, testPoint2);
        
        REQUIRE(testLine1.toString() == "Point 1: [X: 1.0, Y: 2.0], Point 2: [X: 3.0, Y: 4.0]");
    }
}
