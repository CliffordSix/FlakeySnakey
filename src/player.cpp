#include "../inc/player.hpp"
#include <prg_interactive.hpp>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>
#include <cmath>
#define PI 3.14159265

using namespace std;
using namespace prg;

Player::Player( const std::string& name, int x, int y):pos_x_(x), pos_y_(y), name_(name)
{

    Body.resize(length);


    Body[0].x  = x;
    Body[0].y  = y;
    original_x = x;
    original_y = y;
}

void Player::resetSnake(){

Body.clear();
Body[0].y = original_x;
Body[0].x = original_y;

length = 2;

}

void Player::FlakeSnake()
{
    for(int i = length; i > 0; --i){
        Walls.push_back(Body[i]);
         for(int i = Body.size(); i > 0 ; --i){
                cout << "Stuffs going on here" << endl;
         length = length - 1;
            Body.pop_back();
         }
    }


}

void Player::draw( prg::Canvas& canvas )
{


    canvas.drawCircle( pos_x_, pos_y_, SnakeRadius, Colour(0, 255, 100));
    canvas.drawLine(pos_x_ ,pos_y_ ,pos_x_ + (pos_north_x_ * SnakeRadius) , pos_y_ + (pos_north_y_ * SnakeRadius) , Colour(255, 255, 255));
    for(int i = 0; i < length; i++){
        canvas.drawCircle( Body[i + 1].x, Body[i + 1].y, SnakeRadius,Colour( 0, 255,100));
        //canvas.drawLine(Body[i].x, Body[i].y, Body[i + 1]a.x, Body[i + 1].y, Colour(0, 255, 0))
    }
        for(int i = 0; i < Walls.size(); i++){
        canvas.drawCircle( Walls[i + 1].x, Walls[i + 1].y, SnakeRadius,Colour( 100, 255,100));
        //canvas.drawLine(Body[i].x, Body[i].y, Body[i + 1]a.x, Body[i + 1].y, Colour(0, 255, 0))
    }


    canvas.drawLine(pos_x_ ,pos_y_ ,pos_x_ + (pos_north_x_ * SnakeRadius) , pos_y_ + (pos_north_y_ * SnakeRadius) , Colour(255, 255, 255));

}
void Player::setDirection( int direction )
{
    double angle;
    if(direction == 1){
        angle = 30;}
    else{
        angle = -30;
    }
    angle = angle * (PI/180);
        //rotate the north point vector around 0 by the angle provided
        double new_north_x,  new_north_y;

        new_north_x = cos(angle) * (pos_north_x_) - (sin(angle) * pos_north_y_);
        new_north_y = cos(angle) * (pos_north_y_) + (sin(angle) * pos_north_x_);


        if ( fabs(new_north_x) <= 0.000001 ){

            new_north_x = 0;}

        if ( fabs(new_north_y) <= 0.000001 ){

            new_north_y =  0;}

        pos_north_x_ = new_north_x;
        pos_north_y_ = new_north_y;

}

bool Player::onKey( const KeyEvent & key_event	){

    //checks for key input.
    if( key_event.key_state == KeyEvent::KB_DOWN ) {
        if(key_event.key == 'a'){
            setDirection(1);}
        if(key_event.key == 'd'){
            setDirection(2);}
        if(key_event.key == ' '){
            prg::application.setState("pause");
        }
}
 return true;
}

bool Player::collide(float centre_x, float centre_y, int radius)
{
    float northx = pos_x_ + (pos_north_x_ * 8) ;
    float northy = pos_y_ + (pos_north_y_ * 8) ;

    //checks to see if the north point of the snake head is within the circle at the point (centre_x,centre_y) using pythagoras
    float d = pow(abs( northx - centre_x),2)  + pow(abs( northy - centre_y),2) ;
   // cout << sqrt(d) << "||" << (northx - centre_x) << "||" << ( northy - centre_y) << "||" << centre_x << "||" << centre_y << endl;

    if(( sqrt(d) < radius ) || (sqrt(d) == radius )){
            //std::cout << "Something is happening here!" << endl;
        return true;
    }
return false;
}

void Player::incLength( int l )
{
    //increses the length of the snake by the value provided.
 //   int newlength = length + l;
 // /  Point* resize_arr = new Point[newlength];
  //  for(int i = 0; i < length; i++)
  //  {
  //      resize_arr[i] = Body[i];
  //  }
  for(int i = 0; i < l; i++){
    Body.push_back(Body[1]);
  }
    length = length + l;

 //   delete[] Body;
  //  Body = resize_arr;


}

void Player::move()
{

    int i;
    //moves the midpoint of the head of the snake through the array.
    for(i = length; i > 0; i--){

    Body[i].x = Body[i - 1].x;
    Body[i].y = Body[i - 1].y;
    }

    //adds the new angle vector to the mid point of the circle thus redrawing the circle at the new posistion
    pos_x_ = (pos_x_ + (pos_north_x_ * (SnakeRadius * 2))) ;
    pos_y_ = (pos_y_ + (pos_north_y_ * (SnakeRadius * 2))) ;

    Body[0].x  = pos_x_;
    Body[0].y  = pos_y_;

  //  cout << Body[1].y << "||" << Body[2].y << endl;


    //checks if the snake has gone out of bounds and moves it to the opposide side of the canvas.
     if(pos_x_ > 1024){

               pos_x_ = 0;
    }
    if(pos_x_ < 0){

               pos_x_ = 1024;
    }
    if(pos_y_ > 738){
               pos_y_ = 0;
    }
    if(pos_y_ < 0){

               pos_y_ = 738;
    }

}

void AiSnake::Closestfood(int x, int y, int index, int curr_x, int curr_y)
{

    //Calculate the distence between the snake and the currently tageted food object
    float curr_xdist = abs(pow(curr_x - pos_x_,2));
    float curr_ydist = abs(pow(curr_y - pos_x_,2));
    float curr_pointdist = sqrt(curr_xdist + curr_ydist);


    float xdist = abs(pow(x - pos_x_,2));
    //y distance between the two points
    float ydist = abs(pow(y - pos_y_,2));
    //The distance between the food and the provided object
    float pointdist = sqrt(xdist + ydist);

    // compare the current distance to the distance of the other food objects

    if(pointdist < curr_pointdist){
    //if the current point distance is larger than the distance between the snake and the
    //food object we are looking at set the target index to that of the new food.
        setindexofClosestFood( index );
    }

}

void AiSnake::setindexofClosestFood( int index )
{

    indexOfClosestFood  = index;


}


void AiSnake::determineAngle( int x, int y )
{

    // x and y passed to this function should be the mid point of the food we want the aisnake to travel towards

   // calculating the north point of the snake using the vector pos_north_x_ and pos_north_y
    float northx = pos_x_ + (pos_north_x_ * 8) ;
    float northy = pos_y_ + (pos_north_y_ * 8) ;

    float vectora = sqrt(pow( pos_x_ - northx,  2) + pow(pos_y_ - northy, 2));
    float vectorb = sqrt(pow( pos_x_ - x,  2) + pow(pos_y_ - y, 2));
    float vectorc = sqrt(pow( northx - x,  2) + pow(northy - y, 2));

    float angle = acos(( pow(vectora,2) + pow(vectorb,2) - pow(vectorc,2))/(2*vectora * vectorb));
    angle = angle * (180/PI);
   // cout << angle << endl;
    if( angle > 30){
        setDirection(rand() % 2 + 1 );
    }


}
void AiSnake::inteligentcollision(float centre_x, float centre_y, int radius)
{
    //looks one posistion in front of itself to check if there is anything there, if so the snake moves.
    float northx = pos_x_ + (pos_north_x_ * 16) ;
    float northy = pos_y_ + (pos_north_y_ * 16) ;

    //checks to see if the north point of the snake head is within the circle at the point (centre_x,centre_y) using pythagoras
    float d = pow(abs( northx - centre_x),2)  + pow(abs( northy - centre_y),2) ;
   // cout << sqrt(d) << "||" << (northx - centre_x) << "||" << ( northy - centre_y) << "||" << centre_x << "||" << centre_y << endl;

    if(( sqrt(d) < radius ) || (sqrt(d) == radius )){
        //if the point in front of the aisnake is occupided by another circle then the snake will turn away.
        setDirection(2);
    }
}

void AiSnake::draw( prg::Canvas& canvas )
{
    //loops through the array Body and draws circles at the (x,y) points at each location in the array.

    canvas.drawCircle( pos_x_, pos_y_, SnakeRadius, Colour(rand() % 254 + 1, rand() % 254 + 1, rand() % 254 + 1));
    canvas.drawLine(pos_x_ ,pos_y_ ,pos_x_ + (pos_north_x_ * SnakeRadius) , pos_y_ + (pos_north_y_ * SnakeRadius) , Colour(255, 255, 255));
    for(int i = 0; i < length; i++){
        canvas.drawCircle( Body[i + 1].x, Body[i + 1].y, SnakeRadius,Colour( rand() % 254 + 1, rand() % 254 + 1,rand() % 254 + 1));
      //  canvas.drawLine(Body[i].x, Body[i].y, Body[i + 1].x, Body[i + 1].y, Colour(0, 255, 0));
    }
    for(int i = 0; i < Walls.size(); i++){
        canvas.drawCircle( Body[i + 1].x, Body[i + 1].y, SnakeRadius,Colour( 100, 100,255));
    }
     //draws the head of the snake and the the line connecting the midpoint to the northern point.

    canvas.drawLine(pos_x_ ,pos_y_ ,pos_x_ + (pos_north_x_ * SnakeRadius) , pos_y_ + (pos_north_y_ * SnakeRadius) , Colour(255, 255, 255));


}


