#pragma once
#if !defined FOOD_HPP
#define FOOD_HPP
#include <prg_interactive.hpp>

#include <string>

using namespace std;


class Food {

public:
        void draw( prg::Canvas& canvas, int r, int g, int b);
        void setposition();
        int getloc_x()const { return loc_x; }
        int getloc_y()const { return loc_y; }
        bool foodcollide( int centrex, int centrey );
        void setfoodID( int ID );
        int getfoodID()const { return foodID; }


private:
        //foodID is to seperate different types of food.
        int loc_x, loc_y, foodID;

};

#endif
