// Paul Barrett
// Server side of TicTacToe 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <time.h>   //rand
#include <iostream> //cin cout
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#define PORT 8080 
int main(int argc, char const *argv[]) { 
    
    srand(time(0)); //for rand
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    int buffer = -1;
    int receivedMoves[9];   //array of moves played to check against when sending new moves

    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
    
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }

    //wait for next game
    //loop to keep server active and listening after game is won 
    do{
        if (listen(server_fd, 3) < 0) {    //listen for connection
            perror("listen"); 
            exit(EXIT_FAILURE); 
        } 
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { //accept new connection
            perror("accept"); 
            exit(EXIT_FAILURE); 
        }
        printf("\nServer Started ... .. .\n");	
        
        
        int turns = -1; //keep track of number of turns played (starts at -1 because player goes first)
        int move;                      //move to send to client
        bool notuniqueNumber = false;  //boolean to determine if server move hasn't been used
        int playerWon = -2;            //signal sent to server signifying server lost
        int serverWon = -5;            //signal sent to server signifying server won
        int tieGame = -4;              //signal sent to server signifying the game is tied
        int sendJunk = 8;              //in event of tie game, send 1 more message to client to receive tie game signal back
        int leaveLoop = 10;            //signal to leave game loop
        
        do {    //play game
            
            valread = read( new_socket , &buffer, sizeof(&buffer)); //receive move from client
            turns++;                                //update turns
            if(turns == sendJunk){                  //tie game case                      
                send(new_socket , &move , 4 , 0 );  //send whatever
                turns = 0;                          //reset turns
            }
            if(buffer == playerWon){                                //if player won
                printf("\nPlayer won!\n\n");                        //say player won, close connection
                printf("Looking for new connection ... .. .\n");    //leave loop
                close(new_socket);
                turns = leaveLoop;
            } else if (buffer == serverWon){                        //if server won
                printf("\nServer won!\n\n");                        //say server won, close connection
                printf("Looking for new connection ... .. .\n");    //leave loop
                close(new_socket);
                turns = leaveLoop;
            } else if (buffer == tieGame) {                         //if game is tied
                printf("\nTie Game!\n");                            //say game is tied, close connection
                printf("\nLooking for new connection ... .. .\n");  //leave loop
                close(new_socket);
                turns = leaveLoop;
            } else {    //if game isn't lost, won, or tied, play game and send move
                
                int adjustedBuffer = buffer + 1;                                //send buffer in 1-9 format instead of 0-8
                printf("\nMove received from client: %d\n", adjustedBuffer);    //display move
                receivedMoves[turns] = reinterpret_cast<int>(buffer);           //update moves array with int, not *int
                
                do{ //find unused move
                    move = rand() % 9;  //generate random move in range 0-8
                    //use algorithm and find and end to see if random move in in move array and store in boolean
                    notuniqueNumber = std::find(std::begin(receivedMoves), std::end(receivedMoves), move) != std::end(receivedMoves);
                } while (notuniqueNumber == true );    //true if not unique. Loop until it is
                
                int adjustedMove = move + 1;                                        //display move in 1-9 instead of 0-8
                std::cout << "Move sent to client: " << adjustedMove << std::endl;  //display move
                send(new_socket , &move , 4 , 0 );      //send move to client
                turns++;                                //update turns
                receivedMoves[turns] = move;            //update moves array
            }
        } while (turns < leaveLoop);    //loop until turns are less than leaveLoop(10)

    } while (true); //continue listening for a new connection after game ends

    return 0; 
} 
//server