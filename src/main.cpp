#include <stdexcept>
#include <iostream>
#include "../inc/main_game_state.hpp"
#include <prg_interactive.hpp>


int main()
{
    try {
        MainGameState main_game_state;
        PauseState pause_state;
        TitleScreen title_state;

        prg::application.addState("title", title_state);
        prg::application.addState("main", main_game_state);
        prg::application.addState("pause", pause_state);



        prg::application.run( 1024, 768, "Flakey Snakey Aplha 0.0.1", "n3031077" );
    }
    catch( std::exception& error ) {
        std::cerr << "An error caused the program to terminate: " << error.what() << std::endl;
    }

    return 0;
}

