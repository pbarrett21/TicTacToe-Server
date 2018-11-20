// Paul Barrett
// tictactoe.h
#ifndef TICTACTOE_H
#define TICTACTOE_H

class tictactoe{    //class for tictactoe
    private:
        const char *pos[9];   //positions on the tictactoe board
        bool whoseturn;       //determine if player or server turn, true for player, false for server
        int totalTurns;       //keep track of total number of turns played
    public:
        tictactoe();                //constructor
        void drawBoard();           //draw the board
        bool tieGame();             //determine if it is a tie game
        int playerMove();           //do player move
        void serverMove(int move);  //do server move
        bool gameOver();            //determing if game is won and by whom
        bool whichPlayer();         //determing whose turn it is
};

#endif // TICTACTOE_H