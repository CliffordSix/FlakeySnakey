#pragma once
#if !defined MAIN_GAME_STATE_HPP
#define MAIN_GAME_STATE_HPP
#include "../inc/player.hpp"
#include <prg_interactive.hpp>
#include "../inc/food.hpp"


using namespace prg;

class MainGameState : public IAppState, public ITimerEvent {
public:
    bool onCreate();
    bool onDestroy();
    void onEntry();
    void onExit();
    void onUpdate( );
    void onRender( Canvas& canvas);



    //An array of 5 Food Objects
    Food* FoodArray = new Food[5];
    int score = 0, aiscore  =0;
    void onTimer( Timer& timer ) override;

protected:

    int foodindex;
    Timer timer_ { 0, 50, *this };
    Timer timer2_ { 1, 50, *this };


private:

    AiSnake aiplayer_ = AiSnake(100, 512);
    Player player_ = Player( "Bill Oddie", 924, 512 );

};

class GameOverScreen : public TitleScreen{
public:
    void onEntry();
    void onExit();
    void onRender( Canvas& canvas);
private:
    bool onKey( const KeyEvent & key_event);

};

class PauseState : public MainGameState ,public prg::IKeyEvent{
public:
    void onEntry();
    void onExit();
    void onRender( Canvas& canvas);
    void onTimer( Timer& timer_ ) override;


private:
    AiSnake aiplayer_ = AiSnake(512, 384);
     Timer timer_ { 0, 25, *this };
     bool onKey( const KeyEvent & key_event);
};


#endif
