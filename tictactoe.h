// tictactoe.h
#ifndef TICTACTOE_H
#define TICTACTOE_H

class tictactoe{
    private:
        const char *pos[9];   //positions on the tictactoe board
        bool whoseturn; //determine if player or server turn, true for player, false for server
    public:
        tictactoe();
        void drawBoard();
        int playerMove();
        void serverMove(int move);
        void gameOver();
        bool whichPlayer();
};

#endif // TICTACTOE_Hs