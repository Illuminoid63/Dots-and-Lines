#include <iostream> 
#include "point.h"
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