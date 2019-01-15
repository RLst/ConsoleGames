//  main.cpp
//  Assessment 1
//  2D Arrays
//  Gomoku (connect 5)
//  Created by Tony Le on 17/2/18.
//  Copyright © 2018 Tony Le. All rights reserved.

#include <iostream>
#include <conio.h>

//const char* IND = "\t";
const int MAX_ROWS = 9;		//Minimum value of 5, default 11, authentic 15
const int MAX_COLS = 9;		//Minimum value of 5, default 11, authentic 15
const int EMPTY = -1;
const int WHITE = 0;
const int BLACK = 1;

struct Point2D {    //For the cursor
    int x,y;
};

//Core functions
void ClearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
void ClearScreen() {
    //system("clear");    //For Mac
    system("cls");    //For Windows
}
void WaitForKey(bool prompt) {
	ClearBuffer();
	if (prompt == true)
		std::cout << "Press ENTER to continue..." << std::endl;
    std::cin.get();
    //std::cin.get();     //2 required for Xcode
}

void DrawInfo(int player);
void DrawGameBoard(int board[MAX_ROWS][MAX_COLS], Point2D cursor);   //Include draw cursor
void LimitCursor(Point2D &aCursor);
bool PlaceMoku(int board[MAX_ROWS][MAX_COLS], Point2D cursor, int player);
bool isFiveInARow(int board[MAX_ROWS][MAX_COLS], int player);
bool gameBoardFull(int mokuAmount);

//main()    ---------------------------------------
int main(int argc, const char * argv[]) {
    //Set up game board and EMPTY gameboard
    int goBoard[MAX_ROWS][MAX_COLS];
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            goBoard[row][col] = EMPTY;
        }
    }
    Point2D cursor = {MAX_ROWS / 2, MAX_COLS / 2};      //Initialise cursor to somewhere in the middle
    int player = 0;             //Always start off with white player (white = 0, black = 1); This will either be 1 or 0
    bool isRunning = true;      //Loop quit flag
    int mokusPlaced = 0;        //Moku counter
    
    ///Start game loop
    do {
        ClearScreen();							//Clears the screen
        DrawInfo(player);                       //Draws title and info
        DrawGameBoard(goBoard,cursor);          //Draws the gameboard, cursor and moku pieces
        
        //Get user input
        //ClearBuffer();
        //char command = 0;
        //std::cin >> command;
		char command = 0;
		command = _getch();

        switch (command) {

			//Move cursor
            case 'w':   //Move cursor up
                cursor.y--;
                break;
            case 's':   //Move cursor down
                cursor.y++;
                break;
            case 'a':   //Move cursor left
                cursor.x--;
                break;
            case 'd':   //Move cursor right
                cursor.x++;
                break;

			//Place a moku down at cursor location; Away from WASD so less chance of accidental placement
			case 32:	//Space
                if (PlaceMoku(goBoard, cursor, player) == true) {   //PlaceMoku() returns true if the cell is empty...
                    mokusPlaced++;	//A moku is placed

                    //Check if current player is a winner
                    if (isFiveInARow(goBoard, player)) {
                        if (player == WHITE) {  //White wins
                            //Redraw board so that it displays the player winning
                            ClearScreen();
                            DrawInfo(player);
                            DrawGameBoard(goBoard,cursor);
                            std::cout << std::endl << "WHITE WINS!!!" << std::endl;
                            isRunning = false;  //End game
                            WaitForKey(true);
                        }
                        else if (player == BLACK) {     //Black wins
                            //Redraw board so that it displays the player winning
                            ClearScreen();
                            DrawInfo(player);
                            DrawGameBoard(goBoard,cursor);
                            std::cout << std::endl << "BLACK WINS!!!" << std::endl;
                            isRunning = false;  //End game
                            WaitForKey(true);
                        }
                    }
                    
                    //If not then switch players if no one has won
                    if (player == 0)             
                        player = 1;
                    else
                        player = 0;
                }
                else {  //Cell is not empty; Let user know their choice is invalid
                    std::cout << "Can't place that there!" << std::endl;
                    WaitForKey(true);
                }
                
                break;

			//Quit game; '/' is out of the way so that you don't accidentally hit it while playing
            case '/':  
                //Confirm if user wants to quit
				while (true) {
					std::cout << "Are you sure you want to quit? (Y/N)" << std::endl;
					ClearBuffer();
					command = 0;
					std::cin >> command;
					if (command == 'y') {
						isRunning = false;
						std::cout << std::endl << "Sorry to see you go. Good bye!" << std::endl;
						WaitForKey(true);
						break;
					}
					else if (command == 'n') {
						break;
					}
					else {
						std::cout << "Invalid input!" << std::endl;
					}
				}
                //break;	//Otherwise just go back to game loop`

            default:    //Do nothing
                break;
        }
        
        //Keep cursor within bounds
        LimitCursor(cursor);
        
        //Quit if the board becomes full
        if (gameBoardFull(mokusPlaced)) {
            isRunning = false;
            std::cout << "Sorry, the board is full. You both SUCK! :D" << std::endl;
            std::cout << "GOODBYE" << std::endl;
            WaitForKey(true);
        }

    } while (isRunning);
    
    return 0;
}



//-----------------------------------------------------
void DrawInfo(int player) {
    //Draw title etc
	std::cout << std::endl;
    std::cout << "GOMOKU!! Get 5 in a row to win!" << std::endl;
    std::cout << "Use 'WSAD' keys to move cursor. 'Space' to place moku. '/' to quit" << std::endl;
    std::cout << std::endl;
    
    //Display who's turn it is
    switch (player) {
        case 0:
            std::cout << "It is white's (O) turn..." << std::endl;
            break;
        case 1:
            std::cout << "It is black's (X) turn..." << std::endl;
            break;
        default:
            std::cout << "ERROR!" << std::endl;
    }
    std::cout << std::endl;
}
//-----------------------------------------------------
void DrawGameBoard(int board[MAX_ROWS][MAX_COLS], Point2D cursor) {
    for (int row = 0; row < MAX_ROWS; row++) {
        
        //Draw board frame
        for (int frame = 0; frame < MAX_COLS; frame++)
            std::cout << "|---";
        std::cout << "|" << std::endl;  //Last row end frame
        
        for (int col = 0; col < MAX_COLS; col++) {
            //Draw the contents + cursor
            if (cursor.x == col && cursor.y == row) {
                switch (board[row][col]) {
                    case -1:    //Empty
                        std::cout << "|[ ]";
                        break;
                    case 0:     //White player 'O'
                        std::cout << "|[O]";
                        break;
                    case 1:     //Black player '1'
                        std::cout << "|[X]";
                        break;
                    default:    //This should never run
                        std::cout << "|ERR";
                        break;
                }
            }
            //Just draw the contents
            else {
                switch (board[row][col]) {
                    case -1:    //Empty
                        std::cout << "|   ";
                        break;
                    case 0:     //White player 'O'
                        std::cout << "| O ";
                        break;
                    case 1:     //Black player '1'
                        std::cout << "| X ";
                        break;
                    default:    //This should never run
                        std::cout << "|ERR";
                        break;
                }
            }
        }
        //Draw end of frame
        std::cout << "|" << std::endl;
    }
    
    //Draw bottom of frame
    for (int frame = 0; frame < MAX_COLS; frame++)
        std::cout << "|---";
    std::cout << "|" << std::endl;  //Last row end frame
    
}
//-----------------------------------------------------
void LimitCursor(Point2D &mouse) {
    //Keep the cursor inside the game board
    if (mouse.x < 0)
        mouse.x = 0;
    if (mouse.x > MAX_COLS - 1)
        mouse.x = MAX_COLS - 1;
    if (mouse.y < 0)
        mouse.y = 0;
    if (mouse.y > MAX_ROWS - 1)
        mouse.y = MAX_ROWS - 1;
}
//-----------------------------------------------------
bool PlaceMoku(int board[MAX_ROWS][MAX_COLS], Point2D cursor, int player) {
    //Places a moku at the cell where the cursor is. If one already exist then return false, otherwise return true.
    
    //Check if a moku already exists
    if (!(board[cursor.y][cursor.x] == EMPTY)) //ie. if the cell is NOT EMPTY
    {
        return false;
    }
    else {
        //Place a current player's moku down on the board at the cursor position
        board[cursor.y][cursor.x] = player;
        return true;
    }
}
//-----------------------------------------------------
bool isFiveInARow(int board[MAX_ROWS][MAX_COLS], int player) {
    //Horizontal check
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS-4; col++) {
            if (board[row][col] == player &&
                board[row][col+1] == player &&
                board[row][col+2] == player &&
                board[row][col+3] == player &&
                board[row][col+4] == player)
                return true;
        }
    }
    
    //Vertical check
    for (int col = 0; col < MAX_COLS; col++) {
        for (int row = 0; row < MAX_ROWS-4; row++) {
            if (board[row][col] == player &&
                board[row+1][col] == player &&
                board[row+2][col] == player &&
                board[row+3][col] == player &&
                board[row+4][col] == player)
                return true;
        }
    }
    
    //Ascending Diagonal check
    for (int row = 4; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS-4; col++) {
            if (board[row][col] == player &&
                board[row-1][col+1] == player &&
                board[row-2][col+2] == player &&
                board[row-3][col+3] == player &&
                board[row-4][col+4] == player)
                return true;
        }
    }
    
    //Descending Diagonal check
    for (int row = 0; row < MAX_ROWS-4; row++) {
        for (int col = 0; col < MAX_COLS-4; col++) {
            if (board[row][col] == player &&
                board[row+1][col+1] == player &&
                board[row+2][col+2] == player &&
                board[row+3][col+3] == player && 
                board[row+4][col+4] == player)
                return true;
        }
    }
 
    return false;
}
//--------------------------------------------------
bool gameBoardFull(int mokuAmount) {
    //Returns true if the board is full
    if (mokuAmount == MAX_COLS * MAX_ROWS)
        return true;
    else
        return false;
}
