// Client side C/C++ program to demonstrate Socket programming 
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

int main(int argc, char const *argv[]) 
{ 
    //CREATE SOCKET
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    //char *hello = "Hello from client"; 
    int buffer = -1; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } else {
	printf(" #### Socket Created\n");
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } else {
	printf(" #### Connected\n");
    }

    //IF CONNECTION IS SUCCESSFUL, BEGIN GAME

    // GAME
    int count = 0;
    tictactoe yee;
    do {
        int playerMove = -1;
        yee.drawBoard();
        if (yee.whichPlayer() == true){
            playerMove = yee.playerMove();
        } else {
            //receive server's move
            valread = read( sock , &buffer, 1024); 
            printf(" #### Move received by server: %d\n", buffer );
            yee.serverMove(buffer);
        }
        //send player's move to server
        send(sock , &playerMove , sizeof(playerMove) , 0 ); 

        count++;
    } while (count < 9);
    return 0; 
} 
//client