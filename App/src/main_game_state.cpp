    #include "../inc/main_game_state.hpp"
    #include <prg_interactive.hpp>
    #include "../inc/player.hpp"
    #include <iostream>
    #include "../inc/food.hpp"
    #include <cstdlib>

bool MainGameState::onCreate(){

        return true;
}

bool MainGameState::onDestroy(){

        return true;
}

void MainGameState::onEntry(){

    prg::application.addKeyListener( player_ );

    timer_.start();
    timer2_.start();
    //provides each piece of food a location at launch
    for(int i = 0; i< 5; i++){
        FoodArray[i].setposition();
        FoodArray[i].setfoodID(1);
    }
    FoodArray[3].setfoodID(2);
}

void MainGameState::onExit(){

    timer_.stop();
    timer2_.stop();

    prg::application.removeKeyListener( player_ );

}

void MainGameState::onUpdate(){


}

void MainGameState::onRender( Canvas& canvas){
    canvas.clear(Colour(0,0,0));
    canvas.drawLine(0 ,738 ,512 , 738 , Colour(0, 255, 0));
    canvas.drawLine(512 ,738 ,1024, 738 , Colour(0, 100, 255));
    player_.draw( canvas );


    aiplayer_.draw( canvas );

    for(int i = 0; i< 5; i++){
        FoodArray[i].draw( canvas , 255, 255, 255);
         if(FoodArray[i].getfoodID() == 2){

                    FoodArray[i].draw( canvas , 255, 100, 0);

         }
    }
    string Score = static_cast<ostringstream*>(&(ostringstream() << score) ) ->str();
    Font::SMALL.print(canvas, 10, 748, Colour( 0, 255, 0), Score );
    string aiScore = static_cast<ostringstream*>(&(ostringstream() << aiscore) ) ->str();
    Font::SMALL.print(canvas, 1000, 748, Colour( 0, 100, 255), aiScore );

    foodindex = aiplayer_.getindsexOfClosestFood();
   //   canvas.drawLine(aiplayer_.getX() ,aiplayer_.getY() , FoodArray[foodindex].getloc_x() , FoodArray[foodindex].getloc_y() , Colour(255, 255, 255));

}

void MainGameState::onTimer( Timer& t ){
    switch(t.getID()){
        //called every 0.2 seconds
    case 0:

       //calls the collide function to check if the snake head has collided with a piece of food.
    for(int i = 0; i< 5; i++){
        if ( player_.collide(FoodArray[i].getloc_x(), FoodArray[i].getloc_y(), 16))
       {
           //if the function returns true then the length of the snake is incresed by 1 and the location of the food is changed to a new random point.
            if(FoodArray[i].getfoodID() == 2){

                player_.FlakeSnake();
                score = score + 3;
                FoodArray[i].setposition();
            }
            else{
                player_.incLength( 1 );
                score++;
                FoodArray[i].setposition();
            }
            for(int j = 0; j< 5; j++){
                FoodArray[i].foodcollide(FoodArray[j].getloc_x(),FoodArray[j].getloc_y());
            }
            for(int j = 0; j < player_.getLength(); j++){
                FoodArray[i].foodcollide(player_.Body[j].x,player_.Body[j].y);
            }
       }
        if ( aiplayer_.collide(FoodArray[i].getloc_x(), FoodArray[i].getloc_y(), 16))
       {
           //if the function returns true then the length of the snake is incresed by 1 and the location of the food is changed to a new random point.
            if(FoodArray[i].getfoodID() == 2){

                aiplayer_.FlakeSnake();
                aiscore = aiscore + 3;
                FoodArray[i].setposition();
            }
            else{
                aiplayer_.incLength( 1 );
                aiscore++;
                 FoodArray[i].setposition();
            }
            for(int j = 0; j< 5; j++){
                FoodArray[i].foodcollide(FoodArray[j].getloc_x(),FoodArray[j].getloc_y());
            }
            for(int j = 0; j < player_.getLength(); j++){
                FoodArray[i].foodcollide(player_.Body[j].x,player_.Body[j].y);
            }
            for(int i = 0; i< 5; i++){
             aiplayer_.Closestfood(FoodArray[i].getloc_x(),FoodArray[i].getloc_y(), i, FoodArray[foodindex].getloc_x(),FoodArray[foodindex].getloc_y());
            }

       }
    }

    //checks to see if the snake has collided with itself or if the ai player collides with the player.
    for(int i = 1; i < player_.getLength(); i++)
    {
        if( player_.collide(player_.Body[i].x,player_.Body[i].y, 16))
        {
            prg::application.exit();
            return;
        }
        if( aiplayer_.collide(player_.Body[i].x,player_.Body[i].y, 16))
        {
            prg::application.exit();
            return;
        }

    }
        for(int i = 1; i < aiplayer_.getLength(); i++)
    {
        if( aiplayer_.collide(aiplayer_.Body[i].x,aiplayer_.Body[i].y, 16))
        {
            prg::application.exit();
            return;
        }
        if( player_.collide(aiplayer_.Body[i].x,aiplayer_.Body[i].y, 16))
        {
            prg::application.exit();
            return;
        }

    }
    for(int i = 1; i < aiplayer_.getLength(); i++)
    {
        aiplayer_.inteligentcollision(aiplayer_.Body[i].x,aiplayer_.Body[i].y, 16);
    }
    //checks to see if the snakes have collided with any of the walls left by the player snake
    for(int i = 0; i < player_.Walls.size();i++)
    {
            if(player_.collide(player_.Walls[i].x, player_.Walls[i].y, 16)){
                cout << "you have collided with a wall you made!" <<  endl;
            }
            if(aiplayer_.collide(player_.Walls[i].x, player_.Walls[i].y, 16)){
                cout << "the computer has collided with a wall you made!"<<  endl;
            }
    }
    //checks to see if the snakes have collided with walls left by the ai snake
     for(int i = 0; i < aiplayer_.Walls.size();i++)
    {
            if(player_.collide(aiplayer_.Walls[i].x, aiplayer_.Walls[i].y, 16)){
                cout << "you have collided with a wall left by the ai!"<<  endl;
            }
            if(aiplayer_.collide(aiplayer_.Walls[i].x, aiplayer_.Walls[i].y, 16)){
                cout << "the computer has collided with a wall it made!"<<  endl;
            }
    }


    aiplayer_.determineAngle(FoodArray[foodindex].getloc_x(), FoodArray[foodindex].getloc_y());
    //moves the snake forward by 32px
    aiplayer_.move();
    player_.move();

    break;
    case 1:

    break;
    }

}


void PauseState::onRender( Canvas& canvas){


        canvas.clear(Colour(0,0,0));
        canvas.drawLine(0 ,738 ,1024, 738 , Colour(0, 100, 255));

        aiplayer_.draw( canvas );

    for(int i = 0; i< 5; i++){
        FoodArray[i].draw( canvas , 255, 255, 255);
         if(FoodArray[i].getfoodID() == 2){

                    FoodArray[i].draw( canvas , 255, 100, 0);

         }
    }

        string aiScore = static_cast<ostringstream*>(&(ostringstream() << aiscore) ) ->str();
        Font::SMALL.print(canvas, 1000, 748, Colour( 0, 100, 255), aiScore );
        Font::LARGE.print(canvas, 450, 360, Colour( 255, 255, 255), "Paused" );
        Font::MEDIUM.print(canvas, 340, 340, Colour( 255, 255, 255), "Press Space to resume game" );

        foodindex = aiplayer_.getindsexOfClosestFood();
        //canvas.drawLine(aiplayer_.Body[aiplayer_.getLength()].x,aiplayer_.Body[aiplayer_.getLength()].y , FoodArray[foodindex].getloc_x() , FoodArray[foodindex].getloc_y() , Colour(255, 255, 255));

}

void PauseState::onTimer( Timer& t ){

    switch(t.getID()){
    case 0:

        for(int i = 1; i < aiplayer_.getLength(); i++)
        {
            if( aiplayer_.collide(aiplayer_.Body[i].x,aiplayer_.Body[i].y, 16))
            {
                aiscore = 0;
                aiplayer_.resetSnake();
                aiplayer_.Body.clear();
                std::cout << aiplayer_.Body[5].x << aiplayer_.Body[5].y << std::endl;
                score = 0;
                 for(int i = 0; i< 5; i++){
                     FoodArray[i].setposition();
                 }
            }

        }

        for(int i = 0; i< 5; i++){
            if ( aiplayer_.collide(FoodArray[i].getloc_x(), FoodArray[i].getloc_y(), 16))
            {
                //if the function returns true then the length of the snake is incresed by 1 and the location of the food is changed to a new random point.
            if(FoodArray[i].getfoodID() == 2){

                aiplayer_.FlakeSnake();
                aiscore = aiscore + 3;
                FoodArray[i].setposition();
            }
            else{
                aiplayer_.incLength( 3 );
                aiscore++;
                FoodArray[i].setposition();
            }
                for(int j = 0; j< 5; j++){
                    FoodArray[i].foodcollide(FoodArray[j].getloc_x(),FoodArray[j].getloc_y());
                }
                for(int i = 0; i< 5; i++){
                    aiplayer_.Closestfood(FoodArray[i].getloc_x(),FoodArray[i].getloc_y(), i, FoodArray[foodindex].getloc_x(),FoodArray[foodindex].getloc_y());
                }

            }
        }
    for(int i = 1; i < aiplayer_.getLength(); i++)
    {
        aiplayer_.inteligentcollision(aiplayer_.Body[i].x,aiplayer_.Body[i].y, 16);
    }
         aiplayer_.determineAngle(FoodArray[foodindex].getloc_x(), FoodArray[foodindex].getloc_y());

        aiplayer_.move();

    break;
    }
}

bool PauseState::onKey( const KeyEvent & key_event	){

    //checks for key input.
    if( key_event.key_state == KeyEvent::KB_UP ) {
        if(key_event.key == ' '){
            prg::application.setState("main");
        }

}
 return true;
}

void PauseState::onEntry(){

    prg::application.addKeyListener( *this );

    for(int i = 0; i< 5; i++){
        FoodArray[i].setposition();
        FoodArray[i].setfoodID(1);
    }
    timer_.start();

}

void PauseState::onExit(){

    timer_.stop();

    prg::application.removeKeyListener( *this );

}


void TitleScreen::onEntry(){

    prg::application.addKeyListener( *this );

}

void TitleScreen::onExit(){


    prg::application.removeKeyListener( *this );

}

void TitleScreen::onRender( Canvas& canvas){

    Font::LARGE.print(canvas, 375, 570, Colour( 255, 255, 255), "Flakey Snakey" );
    Font::MEDIUM.print(canvas, 360, 540, Colour( 255, 255, 255), "Press p to start game" );
    Font::MEDIUM.print(canvas, 30, 100, Colour( 255, 255, 255), "Controls:" );
    Font::MEDIUM.print(canvas, 30, 80, Colour( 255, 255, 255), "A and D -- move left and right" );
    Font::MEDIUM.print(canvas, 30, 60, Colour( 255, 255, 255), "Space -- Pause" );
    Font::MEDIUM.print(canvas, 365, 510, Colour( 255, 255, 255), "Press escape to quit" );
}

bool TitleScreen::onKey( const KeyEvent & key_event	){

    //checks for key input.
    if( key_event.key_state == KeyEvent::KB_UP ) {
        if(key_event.key == KeyEvent::KB_ESC_KEY){
            prg::application.exit();}
        if(key_event.key == 'p'){
            prg::application.setState("main");
        }
}
 return true;

}





