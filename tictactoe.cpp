// Paul Barrett
// tictactoe.cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

tictactoe::tictactoe(){ //initialize tictactoe game and set private variables
    whoseturn = true;
    totalTurns = 0;
    for (int i = 0; i < 9; i++) //make game board empty
        pos[i] = " ";
}

void tictactoe::drawBoard(){    //draw the game board
    std::cout   << std::endl
                << pos[0] << " │ " << pos[1] << " │ " << pos[2]
                << "\n──┼───┼──\n"
                << pos[3] << " │ " << pos[4] << " │ " << pos[5]
                << "\n──┼───┼──\n"
                << pos[6] << " │ " << pos[7] << " │ " << pos[8]
                << std::endl;
}

int tictactoe::playerMove(){    //do players move
    std::cout << "\n #### Enter your move [1-9]: ";
    int playermove = -1;
    bool tryagain = false;
    do {
        std::cin >> playermove;     //receive user input
        playermove--;               //allow player to enter 1-9 instead of 0-8
        if (playermove < 0 || playermove > 8){      //check if input is in valid range, prompt user if not
            std::cout << "\n #### You must enter a number between 1 and 9!\n";
            std::cout << " #### Try again: ";
            tryagain = true;
        } else {
            tryagain = false;
        }

    } while (tryagain == true); //if the user inputs something invalid, try again

    pos[playermove] = "X";  //place player move on board
    whoseturn = false;      //make it server turn
    totalTurns++;           //update total turns played
    return playermove;      //return player move to be sent to server so server doesn't repeat
}
void tictactoe::serverMove(int move){   //do server's turn
    int servermove = move;              //receive server move
    pos[servermove] = "O";              //place server move on board
    totalTurns++;                       //update total turns played
    whoseturn = true;                   //make it player turn
}

bool tictactoe::whichPlayer(){  //determine whose turn it is
    if (whoseturn == true)      //return true for player turn, false for server turn
        return true;
    else if (whoseturn == false)
        return false;
}

bool tictactoe::gameOver(){ //determine if the game has been won and by whom

    int winboard[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}}; // winning options

    for (int i = 0; i < 8; i++) { // iterate through possibilities
        if ((pos[winboard[i][0]] == pos[winboard[i][1]]) && (pos[winboard[i][1]] == pos[winboard[i][2]]) && pos[winboard[i][0]] != " "){
            if (pos[winboard[i][0]] == "X"){
                std::cout << "\n #### Player wins!\n";     //say who won
            } else if (pos[winboard[i][0]] == "O"){
                std::cout << "\n #### Server wins!\n";
            }

            return true;    // return true if someone won
        }
    }

    return false;   // return false if neither won
}

bool tictactoe::tieGame(){      //determine if there is a tie game
    if (totalTurns == 9){       //if 9 turns have been played, say it's a tie
        std::cout << "\n #### It's a tie game!\n";
        return true;
    } else {
        return false;       //return true if it was a tie, false if not
    }
}