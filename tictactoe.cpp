// tictactoe.cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

tictactoe::tictactoe(){
    srand (time(0));
    whoseturn = true;
    for (int i = 0; i < 9; i++)
        pos[i] = " ";
}

void tictactoe::drawBoard(){
    std::cout   << std::endl
                << pos[0] << " │ " << pos[1] << " │ " << pos[2]
                << "\n──┼───┼──\n"
                << pos[3] << " │ " << pos[4] << " │ " << pos[5]
                << "\n──┼───┼──\n"
                << pos[6] << " │ " << pos[7] << " │ " << pos[8]
                << std::endl;
}

int tictactoe::playerMove(){
    std::cout << " #### Enter your move [1-9]" << std::endl;
    int playermove = -1;
    bool tryagain = false;
    do {
        std::cin >> playermove;
        playermove--;
        if (playermove < 0 || playermove > 8){
            std::cout << " #### You must enter a number between 1 and 9!\n";
            std::cout << " #### Try again: ";
            tryagain = true;
        }

    } while (tryagain == true);

    pos[playermove] = "X";
    whoseturn = false;
    return playermove;
}
void tictactoe::serverMove(int move){
    int servermove = move;
    pos[servermove] = "O";
    whoseturn = true;
}

bool tictactoe::whichPlayer(){
    if (whoseturn == true)
        return true;
    else if (whoseturn == false)
        return false;
}

void tictactoe::gameOver(){

}
