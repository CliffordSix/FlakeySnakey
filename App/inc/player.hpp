#pragma once
#if !defined PLAYER_HPP
#define PLAYER_HPP
#include <prg_interactive.hpp>

#include <vector>
#include <string>

using namespace std;


class Player : public prg::IKeyEvent{

public:
    Player( const::string& name, int x, int y);
    int getX() const { return pos_x_; }
    int getY() const { return pos_y_; }
    int getNorthX() const { return pos_north_x_; }
    int getNorthY() const { return pos_north_y_; }
    int getLength() const { return length; }
    void incLength( int l );
    void resetSnake();

    void setDirection( int direction );

    bool collide( float centre_x, float centre_y, int radius );

    const string& getName() const { return name_; }

    void FlakeSnake();

    struct Point{

        int x;
        int y;

    };

    vector<Point> Walls;

    vector<Point> Body;

    void move();
    void draw( prg::Canvas& canvas);
  //  Point* Body {nullptr};

protected:

    int length = 2;
    double pos_x_, pos_y_, pos_north_x_= 0, pos_north_y_ = 1;
    int SnakeRadius = 8;

    double original_x, original_y;

    string name_;
private:
   bool onKey( const KeyEvent & key_event);

};

class AiSnake : public Player {
public:
    AiSnake(int pos_x_, int pos_y_):Player( "aisnake", pos_x_,  pos_y_){

    }
    void Closestfood(int x, int y, int index, int curr_x, int curr_y);
    int getindsexOfClosestFood() const { return indexOfClosestFood; }
    void setindexofClosestFood( int index );
    void determineAngle( int x, int y );
    void draw( prg::Canvas& canvas);
    void inteligentcollision(float centre_x, float centre_y, int radius );

private:
    int indexOfClosestFood = 1;


};

#endif
