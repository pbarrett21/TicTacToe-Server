// Paul Barrett
// Client side of tictactoe 
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <iostream>
#include "tictactoe.h"
#define PORT 8080 

int main(int argc, char const *argv[]) { 
    //CREATE SOCKET
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    int buffer = -1; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } else {
	    printf(" #### Socket Created\n");
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    // Connect to socket
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } else {
	    printf(" #### Connected\n");
    }

    //IF CONNECTION IS SUCCESSFUL, BEGIN GAME

    // GAME
    tictactoe Game;             //create game
    int playerMove;             //variable for player move choice
    int gameOverSignal = -2;    //signal to be sent to server signifying game is over (player won)
    int tieGame = -4;           //signal to send to server signifying a tie game
    int serverWin = -5;         //signal to send to server signifying the server won
    bool stopLoop = false;      //boolean to decide whether to stop looping through game or not
    
    do {    //begin game

        if(!Game.tieGame()){    //if the game is not tied
            if (Game.whichPlayer() == true){        //player turn
                playerMove = Game.playerMove();     //take in player move and prepare to send to server
                if(Game.gameOver()){                //if player won
                    playerMove = gameOverSignal;    //send game over signal in the place of playerMove to let server know it lost
                    send(sock , &playerMove , sizeof(&playerMove) , 0 );    //send you lost signal to server
                    stopLoop = true;                                        //end game loop
                }
                
                send(sock , &playerMove , sizeof(&playerMove) , 0 ); //send player's move to server if game is not over
                
            } else {    //server turn
                valread = read( sock , &buffer, sizeof(&buffer));   //read server move
                int adjustedServerBuffer = buffer + 1;              //adjust server move to display in range 1-9
                printf("\n #### Move received from server: %d\n", adjustedServerBuffer);    //print server's move
                Game.serverMove(buffer);    //take in server move and update board
                
                if(Game.gameOver()){    //if server won
                    send(sock , &serverWin , sizeof(&serverWin) , 0 );  //send you won to server
                    stopLoop = true;                                    //end game loop
                }
            }
            
            Game.drawBoard();   //draw updated game board after player and server turn
        } else {                //if game is tied
            Game.drawBoard();   //draw board
            valread = read( sock , &buffer, sizeof(&buffer)); //take in server move (not used) 
            send(sock , &tieGame , sizeof(&tieGame) , 0 );    //send back tie game signal
            stopLoop = true;                                  //end game loop
        }
    } while (stopLoop == false);    //continue playing game unless stopLoop is true
    
    return 0; 
} 
//client
