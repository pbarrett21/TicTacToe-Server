// Paul Barrett
// Server side of TicTacToe 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <sstream>
#include <string.h>
#include <time.h>
#include <iostream>
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    srand (time(0));
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    int buffer = -1; 
    //char *hello = "Hello from server"; 
    
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
    
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }
    printf("Server Started ... .. .\n");	
    
    int receivedMoves[9];
    int turns = 0;
    int move;
    bool uniqueNumber = false;
    do {
        //receive move from client
        valread = read( new_socket , &buffer, 1024); 
        printf("Received: %d\n", buffer++ );
        move = rand() % 9;
        std::cout << "move =" << move << std::endl;
        send(new_socket , &move , 4 , 0 );
        turns++;
    } while (turns < 9);
    return 0; 
} 
//server