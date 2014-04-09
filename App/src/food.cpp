#include "../inc/food.hpp"
#include <prg_interactive.hpp>
#include <iostream>
#include <cstdlib>

using namespace prg;

void Food::draw( prg::Canvas& canvas, int r, int g, int b )
{
    canvas.drawCircle( loc_x, loc_y, 8, Colour(r, g, b));

}

void Food::setposition()
{
   loc_x  = rand() % 994 + 30;
   loc_y  = rand() % 698 + 30;

}

//A check to see a piece of food is overlapping another piece of food.
bool Food::foodcollide( int centrex, int centrey )
{
    //a^2 + b^2 = h^2
    //x distance between the two points
    float xdist = loc_x - centrex;
    //y distance between the two points
    float ydist = loc_y - centrey;
    //The distance between the food and the provided object
    float pointdist = pow(xdist,2) + pow(ydist,2);

    if(( sqrt(pointdist) < 32 ) || ( sqrt(pointdist) == 32 )){
       setposition();
       }
    return true;

}

void Food::setfoodID( int ID ){

foodID = ID;

}
