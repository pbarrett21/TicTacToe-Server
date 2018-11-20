Paul Barrett
Tic-Tac-Toe Server

Compilation:
	Server: g++ -std=c++11 socketserver.cpp -o server
	Client: g++ socketclient.cpp tictactoe.cpp -o client
	Note: g++ must be used, not gcc. Also, make sure to compile the server with C++11 for algorithms

How to run the Tic-Tac-Toe game:
	1. Set network preferences in client and server (port and ip can be found in both)
	2. Compile the server and the client
	3. Begin the server [./server]
	4. Begin the client [./client]
	5. Play
	Note: the game board is set up like so
		1 2 3
		4 5 6
		7 8 9

How to play:
	The player starts first. Enter a move in the range from 1 to 9. After your move, the server will play.
	Take turns until the game ends in a tie, you win, or the server wins.
	To play another game, begin the client program again with [./client]

Additional notes:
	Though the server checks if its move has been used yet, the client does not. 
	This means the player could reuse moves if he or she wanted. I did not check for this.
	Per the project description: "the client program should verify that this move is valid before sending it to the server"
	I interpreted this to mean check that the input is in a valid range (1-9). This I did check for.

	The client ends automatically after a game has finished. The server continues listening for another game.
	To end the server connection, use CTRL+c
