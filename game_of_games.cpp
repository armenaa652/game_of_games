/*
	Adam A. Armendariz & Zach Chairez & Seth Ponce & Happen Patel
	Course: COSC 1436.001 Programming Fundamentals
	Lab #8:  A game of games, included is plinko, tic-tac-toe, chess, battleship,
	and connect four
	Due Date: August 14, 2017
	Instructor: Korinne Caruso

	Purpose: This program is to provide the user and friend
	a good time with a copious amount of games such as
	plinko, tic-tac-toe, chess, battleship, and connect four

	Input:

	1. Press the number 1 - 6 to begin the plinko fall, then follow each programs
	specific instructions
	Chess: Enter column and then row of the initial and final place of the piece
	you'd like to move
	Connect four: Enter a number from 1 - 7 where you would like to have the disk fall
	too
	Tic-tac-toe: Press the number from 1 - 9 to place corresponding X or O
	Battleship: Enter column and then row as instructed

	2. The input for all cases are set to be a char input, which is a single character
	value. In cases such as battleship or chess, there is multiple chars being asked for
	all at once

	3. The program recieves the input as a cin. The program also recieves instructions
	from a file for chess, connect four, and battleship

	4. The input should be on a range of what is allowed on each repspective board
	Plinko: 1-6 or the letters for the games
	Chess: a-h and 1-8 for the 8x8 board
	Tic-tac-toe: 1-9 for 3x3 board
	Connect Four:1-7 for each column in the game

	Output: Output is in the form of a cout statement of each updated move of on the board
	In chess it also creates a file called "Score Sheet.txt"
*/

#ifdef __cplusplus__
  #include <windows.h>
#else
  #include <unistd.h>
#endif
#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void mySleep(int);
void blankSpaces();
void plinkoBoard(int);
char plinkoStart();
void plinkoFaller();
void plinkoDeleter();
char plinkoFinal();
char plinko[12][6];
int p, q;

int chess();
void chessStartup();
void whiteboardSetup();
void blackboardSetup();
void pieceEliminator();
char pieceIdentifier();
bool piecePlacer(char);
bool moveChecker(char);
bool winCheck();
bool drawCheck(bool&);
void scoreSheet(char);
char matrix[8][8];
char column, row, column2, row2;            //global variables for initial piece chosen and final destination of piece
static int i, j;
string player;

int ticTacToe();
char ttt[3][3];
void tttSetup();
void tttBoard();
char X = 'X';
char O = 'O';
void inPut2();
void inPut3();
bool weaner();
bool inputC4(int);

int connectFour();
void boardinitializer();
void boardbuilder();
bool winc4();
char movecolumn();
void boardupdater(char, bool&);
char bit;
bool win;
char board[6][7];

int battleship();
void CoinFlip();//Function prototype which creates a random coin flip
void MenuOutline();//Function prototype which creates the initial board for each player with instructions
//Function prototype which establishes ship locations for Player 1 and utilizes the function HitOrMiss1
void GameOutlinePlayer1(char, char, char, char, char, char, char ,char ,char , char , char , char, char, char, char, char, char, char, char, char);
//Function prototype which establishes ship locations for Player 2 and utilizes the function HitOrMiss2
void GameOutlinePlayer2(char, char, char, char, char, char, char ,char ,char , char , char , char, char, char, char, char, char, char, char, char);
bool HitOrMiss1(char, char);//Function prototype used for the detecting of hits or misses from Player 1 to Player 2
bool HitOrMiss2(char, char);//Function prototype used for the detecting of hits or misses from Player 2 to Player 1
void EmptyBoard();//Function prototype used to create an empty board for Player 1 to attack Player 2
void EmptyBoard2();//Function prototype used to create an empty board for Player 2 to attack Player 1
void Limbo();//Function prototype which creates a "limbo" screen in between Player's attacks
bool Victory();//Function prototype which recognizes whether Player 1/Player 2 wins
char POOP1[10][10];//Empty array established for Player 1 to enter their ship locations
char POOP2[10][10];//Empty array established for Player 2 to enter their ship locations
char POOP_Empty[10][10];//Empty array established for Player 1 to attack Player 2
char POOP_Empty2[10][10];//Empty array established for Player 2 to attack Player 1
char r, c;//Global row and column variables to create empty boards and menu outline
bool victory = false;//Victory Switch established as off
//Player 1 hits on Player 2 turned on
bool a = false, b = false, z = false, d = false, e = false, f = false, g = false, h = false, u = false, v = false;
//Player 2 hits on Player 1 turned on
bool k = false, l = false, m = false, n = false, o = false, w = false, x = false, y = false, s = false, t = false;
//Inputs for Player 1 to hand the screen off to Player 2 and vice versa
int player1, player2;
//Variable that is asked to be inputted by user who wins to play again, initialized as something not equal to yes
char GameOver = '0';
void battleSpaces();

int main()
{
    ifstream dataIn;
    string line;
    bool plinkoExit = false;
    char choice;
    do
    {
        int cnt = 0;
        blankSpaces();          //initializes board
        plinkoBoard(cnt);           //prints board
        choice = plinkoStart();         //user input of choice
        cnt++;
        if(choice == 'z')
            plinkoBoard(cnt);           //shows users choice on board

        for(; cnt <= 11 and choice == 'z'; cnt++)
        {
            plinkoDeleter();            //deletes old space
            plinkoFaller();        //randomizes new space
            plinkoBoard(cnt);           //updates board with new location
        }
        if(choice != 'z')
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if(choice == 'z')
            choice = plinkoFinal();         //whenever the disk hits the bottom, this identifies the choice

        switch(choice)
        {
            case 'a':
            case 'A':   if (system("CLS")) system("clear");
                        cout << endl;
                        dataIn.open("HowToChess.txt");          //opens file
                        while(getline(dataIn, line))
                            cout << setw(5) << "" << line << endl;
                        dataIn.close();
                        cin.get();
                        chess();            //begins chess game
                        plinkoExit = false;
                        break;
            case 'b':
            case 'B':   if (system("CLS")) system("clear");
                        cout << endl;
                        dataIn.open("connect four rules.txt");          //opens file
                        while(getline(dataIn, line))
                            cout << setw(7) << "" << line << endl;
                        dataIn.close();
                        cin.get();
                        connectFour();          //begins connect four game
                        plinkoExit = false;
                        break;
            case 'c':
            case 'C':   if (system("CLS")) system("clear");
                        dataIn.open("BattleShip.txt");
                        while(getline(dataIn, line))
                            cout << setw(6) << "" << line << endl;
                        dataIn.close();
                        cin.get();
                        battleship();
                        plinkoExit = false;
                        break;
            case 'd':
            case 'D':   if (system("CLS")) system("clear");
                        dataIn.open("TicTacToe.txt");
                        while(getline(dataIn, line))
                            cout << setw(6) << "" << line << endl;
                        dataIn.close();
                        cin.get();
                        ticTacToe();
                        plinkoExit = false;
                        break;
            case 'e':
            case 'E':   plinkoExit = false;
                        break;
            case 'x':
            case 'X':   if (system("CLS")) system("clear");
                        plinkoExit = true;
                        break;
        }
    } while (plinkoExit == false);
    return 0;
}

/*
This function is to make the sleep function cross platform
the sleep function is to create a pause for the disk to
fall

Return Value
------------
This is a nonvalue returning function

Function Parameters
----------------
int     sleepMs     how long to sleep

Local Variables
---------------
no local variables
*/

void mySleep(int sleepMs)
{
#ifdef __cplusplus__
  Sleep(sleepMs);
#else
  usleep(sleepMs * 1000);           // usleep takes sleep time in us (1 millionth of a second)
#endif
}

/*
This function initializes all of the spaces to be
either a blank space or a letter for choice

Return Value
------------
This is a nonvalue returning function

Function Parameters
----------------
No parameters

Local Variables
---------------
int     y       y axis for creating board
int     x       x axis for creating board
char    letter  for bottom choices in board
*/

void blankSpaces()
{
    int y, x;
    char letter = 'A';
    for(y = 0; y < 11; y++)
    {
        for(x = 0; x < 6; x++)
        {
            plinko[y][x] = ' ';         //makes all spaces within the matrix a ' '
        }
    }
    for(x = 0; x < 12; x++)
        {
            plinko[y][x] = letter++;            //makes the bottom spaces letters from 'A' to 'E'
        }
}

/*
This function prints the board to screen

Return Value
------------
This is a nonvalue returning function

Function Parameters
----------------
int     num     decides how many times the function has been called

Local Variables
---------------
int     y       y axis for creating board
int     x       x axis for creating board
*/

void plinkoBoard(int num)
{
    if(num > 0)
    mySleep(350);
    if (system("CLS")) system("clear");
    int y, x;
    cout << endl << setw(23) << "" << "WELCOME TO THE GAME SELECTOR!" << endl;
    for(y = 0; y < 12; y++)
    {
        if(y == 0)
        {
            cout << endl << setw(22) << "" << "1  |  2  |  3  |  4  |  5  |  6" << endl;
            cout << setw(21) << "" << "- - - - - - - - - - - - - - - - -" << endl;
        }
        cout << setw(18) << "";
        if(y == 0 or y % 2 == 0)
            for(x = 0; x < 6; x++)
            {
                if(x == 0)
                cout << "  # ";
                if(x < 5)
                    cout << plinko[y][x] << "  *  ";
                else
                    cout << plinko[y][x];
                if(x == 5)
                cout << " #";
            }
        else
            for(x = 0; x < 5; x++)
            { if(x == 0)
                cout << "  # #";
                if(x == 0)
                    cout << "  ";

                if(x < 4)
                    cout << plinko[y][x] << "  *  ";
                else
                    cout << plinko[y][x];
                if(x == 4)
                cout << "  # #";
            }
        if(y < 11)
            cout << endl << setw(20) << "" << "#                                 #" << endl;
        else
            cout << endl;
    }
    cout << setw(20) << "" << "# # # # # # # # # # # # # # # # # #"<< endl;
}

/*
This function asks the user what column they'd like to drop their
disk or to exit

Return Value
------------
char        a,b,c,d,e,x, or z   users choice

Function Parameters
----------------
No parameters

Local Variables
---------------
int     num     to put in for the matrix
char    choice  for the users input
*/

char plinkoStart()
{
    int num;
    char choice;
    cout << setw(15) << "" << "Select number to drop disk (Press X to QUIT): ";
    cin >> choice;

    while ((choice > '6' or choice < '1') and (choice != 'a' and choice != 'A' and
            choice != 'b' and choice != 'B' and choice != 'c' and choice != 'C' and
            choice != 'd' and choice != 'D' and choice != 'e' and choice != 'E'
            and choice != 'x' and choice != 'X'))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter a number between 1 and 6" << endl;
        cin >> choice;
    }
    if(choice == 'a' or choice == 'A' or choice == 'b' or choice == 'B' or
       choice == 'c' or choice == 'C' or choice == 'd' or choice == 'D' or
       choice == 'e' or choice == 'E' or choice == 'x' or choice == 'X')
        return choice;
    num = choice - '0';
    p = 0, q = num - 1;
    plinko [p][q] = 'o';
    return 'z';
}

/*
The logic that allows the disk to fall and
look correct with no sudden jumps across the board

Return Value
------------
This is a nonvalue returning function

Function Parameters
----------------
No parameters

Local Variables
---------------
int     num     random number from 1 to 2
*/

void plinkoFaller()
{
    srand(time(0));
    int num;
    num =  rand() % 2 + 1;          // assign random numbers
    //cout << num << endl;
    if(q == 0 and (p == 0 or p == 2 or p == 4 or p == 6 or p == 8 or p == 10))
        q = 0;
    else if(q == 5 and (p == 0 or p == 2 or p == 4 or p == 6 or p == 8 or p == 10))
        q -= 1;
    else
    {
        if(p == 0 or p == 2 or p == 4 or p == 6 or p == 8 or p == 10)
        {
            if(num == 1)
                q = q;
            else
                q -= 1;
        }
        else
        {
            if(num == 1)
                q = q;
            else
                q += 1;
        }
    }
    p += 1;
    plinko [p][q] = 'o';
}

/*
Deletes the old location of the disk so it
looks like its moving

Return Value
------------
This is a nonvalue returning function

Function Parameters
----------------
No parameters

Local Variables
---------------
no local variables
*/

void plinkoDeleter()
{
    plinko [p][q] = ' ';
}

/*
Once the disk hits the bottom of the board
this function decides whice piece it hit
and makes that the choice

Return Value
------------
char    choice     where the disk finally hit

Function Parameters
----------------
No parameters

Local Variables
---------------
no local variables
*/

char plinkoFinal()
{
    if(plinko[11][0] != 'A')
    {
        cout << endl << setw(25) << "" << "Chess it is! PRESS ENTER" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        return 'a';
    }
    else if(plinko[11][1] != 'B')
    {
        cout << endl << setw(22) << "" << "Connect Four it is! PRESS ENTER";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        return 'b';
    }
    else if(plinko[11][2] != 'C')
    {
        cout << endl << setw(23) << "" << "Battleship it is! PRESS ENTER";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        return 'c';
    }
    else if(plinko[11][3] != 'D')
    {
        cout << endl << setw(22) << "" << "Tic-Tac-Toe it is! PRESS ENTER";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        return 'd';
    }
    else if(plinko[11][4] != 'E')
    {
        cout << endl << setw(25) << "" << "Plinko it is! PRESS ENTER";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        return 'e';
    }
    else
    {
        return 'e';
    }
}

int chess()
{
    chessStartup();
    ofstream dataOut;

    dataOut.open("Score Sheet.txt");
    dataOut << "      Move Notation" << endl;
    dataOut << "      -------------" << endl;

    char piece;         //piece chosen to move
    bool gameExit = false, input ,error = false, gameDraw = false, asked;
    int cnt , movenum = 1;
    whiteboardSetup();
    for (cnt = 2; gameExit == false and gameDraw == false; cnt ++)
    {

        if (cnt % 2 == 0)
            player = "White";           //player is chosen to be white
        else if (cnt % 2 == 1)
            player = "Black";           //player is chosen to be black
        piece = 'x';            //initializes choice
        column = 'x';
        column2 = 'x';
        row = '0';
        row2 = '0';
        if (player == "White")
        {
            do
            {
                do
                {
                    do
                    {
                        piece = pieceIdentifier();          //calls function to identify piece
                        if ((piece <= 'Z' and piece >= 'A') or ((column == 'd' or column == 'D') and (row == 'r' or row == 'R')))          //checks if piece chosen is white's piece
                            error = false;
                        else            //error check
                        {
                            whiteboardSetup();
                            cout << setw(20) << "" << "Move not legal! (EX. WRITTEN AS: e2 e4)" << endl;
                            error = true;
                        }
                    }while (error == true);
                    error = true;
                    input = true;
                    asked = false;
                    input = piecePlacer(piece);         //error check + places piece
                    if((column == 'd' or column == 'D') and (row == 'r' or row == 'R') and (column2 == 'a' or column2 == 'A') and (row2 == 'w' or row2 == 'W'))
                        asked = true;
                    if (input == true and asked == false)
                        pieceEliminator();          //replaces old space with either a ' ' or a '#' to "move" the piece
                } while (input == false);
                blackboardSetup();          //reprints board
                gameDraw = drawCheck(asked);
            }while (asked == true);
            gameExit = winCheck();          //checks if player won
        }
        if (player == "Black")
        {
            do
            {
                do
                {
                    do
                    {
                        piece = pieceIdentifier();          //calls function to identify piece
                        if (piece <= 'z' and piece >= 'a')          //checks if piece chosen is white's piece
                            error = false;
                        else            //error check
                        {
                            blackboardSetup();
                            cout << setw(20) << "" << "Move not legal! (EX. WRITTEN AS: e2 e4)" << endl;
                            error = true;
                        }
                    }while (error == true);
                    error = true;
                    input = true;
                    asked = false;
                    input = piecePlacer(piece);         //error check + places piece
                    if((column == 'd' or column == 'D') and (row == 'r' or row == 'R') and (column2 == 'a' or column2 == 'A') and (row2 == 'w' or row2 == 'W'))
                        asked = true;
                    if (input == true and asked == false)
                        pieceEliminator();          //replaces old space with either a ' ' or a '#' to "move" the piece
                } while (input == false);
                whiteboardSetup();          //reprints board
                gameDraw = drawCheck(asked);
            }while (asked == true);
            gameExit = winCheck();          //checks if player won

        }
        dataOut << player << "'s Move #" << movenum << ": " << piece << column << row << " - " << column2 << row2 << endl;
        if(player == "Black")
            movenum ++;
    }
    if(gameExit == true)
        cout << setw(23) << "" << player << " wins the game!  PRESS ENTER" << endl;
    if(gameDraw == true)
        cout << setw(24) << "" << "It's a drawn game!  PRESS ENTER" << endl;
    cout << setw(15) << "" << "A file has been created called \"Score Sheet.txt\""<< endl;
    cout <<setw(17) << "" << "that has recoreded the moves from this game"<< endl;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    return 0;
}

/*
This function initializes all pieces in matrix

Return Value
------------
This is a nonvalue returning function

Function Parameters
----------------
No parameters

Local Variables
---------------
no local variables
*/

void chessStartup()
{
    matrix[0][0] = 'r';
    matrix[0][1] = 'n';
    matrix[0][2] = 'b';
    matrix[0][3] = 'k';
    matrix[0][4] = 'q';
    matrix[0][5] = 'b';
    matrix[0][6] = 'n';
    matrix[0][7] = 'r';
    matrix[1][0] = 'p';
    matrix[1][1] = 'p';
    matrix[1][2] = 'p';
    matrix[1][3] = 'p';
    matrix[1][4] = 'p';
    matrix[1][5] = 'p';
    matrix[1][6] = 'p';
    matrix[1][7] = 'p';
    matrix[2][0] = '#';
    matrix[2][1] = ' ';
    matrix[2][2] = '#';
    matrix[2][3] = ' ';
    matrix[2][4] = '#';
    matrix[2][5] = ' ';
    matrix[2][6] = '#';
    matrix[2][7] = ' ';
    matrix[3][0] = ' ';
    matrix[3][1] = '#';
    matrix[3][2] = ' ';
    matrix[3][3] = '#';
    matrix[3][4] = ' ';
    matrix[3][5] = '#';
    matrix[3][6] = ' ';
    matrix[3][7] = '#';
    matrix[4][0] = '#';
    matrix[4][1] = ' ';
    matrix[4][2] = '#';
    matrix[4][3] = ' ';
    matrix[4][4] = '#';
    matrix[4][5] = ' ';
    matrix[4][6] = '#';
    matrix[4][7] = ' ';
    matrix[5][0] = ' ';
    matrix[5][1] = '#';
    matrix[5][2] = ' ';
    matrix[5][3] = '#';
    matrix[5][4] = ' ';
    matrix[5][5] = '#';
    matrix[5][6] = ' ';
    matrix[5][7] = '#';
    matrix[6][0] = 'P';
    matrix[6][1] = 'P';
    matrix[6][2] = 'P';
    matrix[6][3] = 'P';
    matrix[6][4] = 'P';
    matrix[6][5] = 'P';
    matrix[6][6] = 'P';
    matrix[6][7] = 'P';
    matrix[7][0] = 'R';
    matrix[7][1] = 'N';
    matrix[7][2] = 'B';
    matrix[7][3] = 'K';
    matrix[7][4] = 'Q';
    matrix[7][5] = 'B';
    matrix[7][6] = 'N';
    matrix[7][7] = 'R';
}

/*
This function creates the board for white's turn and shows updates of the pieces
after they have moved

Return Value
------------
This is a nonvalue returning function

Function Parameters
----------------
No parameters

Local Variables
---------------
int     number     numbers on the side of the board
int     cnt     to decide even or odd
int     x       checks matrix
int     y       checks matrix
*/

void whiteboardSetup()
{
    int number = 8;
    int cnt = 2;
    static int i;
    if (system("CLS")) system("clear");
    for(int y = 0; y < 8; y++)          //loop and nested loop that prints entire board
    {
        if (y == 0)
        {
            cout << endl << setw(15) << "" << "       A    B    C    D    E    F    G    H  " << endl;          //aesthetic
            cout << setw(15) << "" << "     - - - - - - - - - - - - - - - - - - - - " << endl;
        }
        if(cnt % 2 == 0)
            cout << setw(15) << "" << "   | # # #     # # #     # # #     # # #     " << endl;
        else if(cnt % 2 == 1)
            cout << setw(15) << "" << "   |      # # #     # # #     # # #     # # #" << endl;
            cout << setw(15) << "";
        for(int x = 0; x < 8; x++)
        {

            if(x == 0)
                cout << number-- << "  | ";
            if(cnt % 2 == 0)
            {
                cout << "# " << matrix[y][x] << " #";
                x++;
                cout << "  " << matrix[y][x] << "  ";
            }
            else if(cnt % 2 == 1)
            {
                cout << "  " << matrix[y][x] << "  ";
                x++;
                cout << "# " << matrix[y][x] << " #";
            }
        }
        if(cnt % 2 == 0)
            cout << endl << setw(15) << "" << "   | # # #     # # #     # # #     # # #     " << endl;
        else if(cnt % 2 == 1)
            cout << endl << setw(15) << "" << "   |      # # #     # # #     # # #     # # #" << endl;
        cnt ++;
    }
}

/*
This function creates the board for blacks's turn and shows updates of the pieces
after they have moved

Return Value
------------
This is a nonvalue returning function

Function Parameters
----------------
No parameters

Local Variables
---------------
int     number     numbers on the side of the board
int     cnt     to decide even or odd
int     x       checks matrix
int     y       checks matrix
*/

void blackboardSetup()
{
    int number = 1;
    int cnt = 2;
    if (system("CLS")) system("clear");
    for(int y = 7; y >= 0; y--)          //loop and nested loop that prints entire board
    {

        if (y == 7)
        {
            cout << endl << setw(15) << "" << "       H    G    F    E    D    C    B    A  " << endl;          //aesthetic
            cout << setw(15) << "" << "     - - - - - - - - - - - - - - - - - - - - " << endl;
        }
        if(cnt % 2 == 0)
            cout << setw(15) << "" << "   | # # #     # # #     # # #     # # #     " << endl;
        else if(cnt % 2 == 1)
            cout << setw(15) << "" << "   |      # # #     # # #     # # #     # # #" << endl;
            cout << setw(15) << "";
        for(int x = 7; x >= 0; x--)
        {
            if(x == 7)
                cout << number++ << "  | ";
            if(cnt % 2 == 0)
            {
                {
                    cout << "# " << matrix[y][x] << " #";
                    x--;
                    cout << "  " << matrix[y][x] << "  ";
                }
            }
            else if(cnt % 2 == 1)
            {
                cout << "  " << matrix[y][x] << "  ";
                x--;
                cout << "# " << matrix[y][x] << " #";
            }
        }
        if(cnt % 2 == 0)
            cout << endl << setw(15) << "" << "   | # # #     # # #     # # #     # # #     " << endl;
        else if(cnt % 2 == 1)
            cout << endl << setw(15) << "" << "   |      # # #     # # #     # # #     # # #" << endl;
        cnt ++;
    }
}

/*
This function allows the player to input their beginning coordinate to select a specific piece, it also
allows the rest of the program to identify the chosen piece using the coordinates and storing the location
within the matrix

Return Value
------------
char    matrix[y][x]    returns the selected piece

Function Parameters
----------------
No parameters

Local Variables
---------------
no local variables
*/

char pieceIdentifier()
{
    cout << setw(35) << player << " to move: ";
    cin >> column >> row;           //user input to select initial space

    if (column == 'a' or column == 'A')     //identifies piece
    {
        if (row == '1')
        {
            i = 7;
            j = 0;
            return matrix[7][0];
        }
        else if (row == '2')
        {
            i = 6;
            j = 0;
            return matrix[6][0];
        }
        else if (row == '3')
        {
            i = 5;
            j = 0;
            return matrix[5][0];
        }
        else if (row == '4')
        {
            i = 4;
            j = 0;
            return matrix[4][0];
        }
        else if (row == '5')
        {
            i = 3;
            j = 0;
            return matrix[3][0];
        }
        else if (row == '6')
        {
            i = 2;
            j = 0;
            return matrix[2][0];
        }
        else if (row == '7')
        {
            i = 1;
            j = 0;
            return matrix[1][0];
        }
        else if (row == '8')
        {
            i = 0;
            j = 0;
            return matrix[0][0];
        }
        else
            return 'x';
    }
    else if (column == 'b' or column == 'B')
    {
        if (row == '1')
        {
            i = 7;
            j = 1;
            return matrix[7][1];
        }
        else if (row == '2')
        {
            i = 6;
            j = 1;
            return matrix[6][1];
        }
        else if (row == '3')
        {
            i = 5;
            j = 1;
            return matrix[5][1];
        }
        else if (row == '4')
        {
            i = 4;
            j = 1;
            return matrix[4][1];
        }
        else if (row == '5')
        {
            i = 3;
            j = 1;
            return matrix[3][1];
        }
        else if (row == '6')
        {
            i = 2;
            j = 1;
            return matrix[2][1];
        }
        else if (row == '7')
        {
            i = 1;
            j = 1;
            return matrix[1][1];
        }
        else if (row == '8')
        {
            i = 0;
            j = 1;
            return matrix[0][1];
        }
        else
            return 'x';
    }
    else if (column == 'c' or column == 'C')
    {
        if (row == '1')
        {
            i = 7;
            j = 2;
            return matrix[7][2];
        }
        else if (row == '2')
        {
            i = 6;
            j = 2;
            return matrix[6][2];
        }
        else if (row == '3')
        {
            i = 5;
            j = 2;
            return matrix[5][2];
        }
        else if (row == '4')
        {
            i = 4;
            j = 2;
            return matrix[4][2];
        }
        else if (row == '5')
        {
            i = 3;
            j = 2;
            return matrix[3][2];
        }
        else if (row == '6')
        {
            i = 2;
            j = 2;
            return matrix[2][2];
        }
        else if (row == '7')
        {
            i = 1;
            j = 2;
            return matrix[1][2];
        }
        else if (row == '8')
        {
            i = 0;
            j = 2;
            return matrix[0][2];
        }
        else
            return 'x';
    }
    else if (column == 'd' or column == 'D')
    {
        if (row == '1')
        {
            i = 7;
            j = 3;
            return matrix[7][3];
        }
        else if (row == '2')
        {
            i = 6;
            j = 3;
            return matrix[6][3];
        }
        else if (row == '3')
        {
            i = 5;
            j = 3;
            return matrix[5][3];
        }
        else if (row == '4')
        {
            i = 4;
            j = 3;
            return matrix[4][3];
        }
        else if (row == '5')
        {
            i = 3;
            j = 3;
            return matrix[3][3];
        }
        else if (row == '6')
        {
            i = 2;
            j = 3;
            return matrix[2][3];
        }
        else if (row == '7')
        {
            i = 1;
            j = 3;
            return matrix[1][3];
        }
        else if (row == '8')
        {
            i = 0;
            j = 3;
            return matrix[0][3];
        }
        else
            return 'x';
    }
    else if (column == 'e' or column == 'E')
    {
        if (row == '1')
        {
            i = 7;
            j = 4;
            return matrix[7][4];
        }
        else if (row == '2')
        {
            i = 6;
            j = 4;
            return matrix[6][4];
        }
        else if (row == '3')
        {
            i = 5;
            j = 4;
            return matrix[5][4];
        }
        else if (row == '4')
        {
            i = 4;
            j = 4;
            return matrix[4][4];
        }
        else if (row == '5')
        {
            i = 3;
            j = 4;
            return matrix[3][4];
        }
        else if (row == '6')
        {
            i = 2;
            j = 4;
            return matrix[2][4];
        }
        else if (row == '7')
        {
            i = 1;
            j = 4;
            return matrix[1][4];
        }
        else if (row == '8')
        {
            i = 0;
            j = 4;
            return matrix[0][4];
        }
        else
            return 'x';
    }
    else if (column == 'f' or column == 'F')
    {
        if (row == '1')
        {
            i = 7;
            j = 5;
            return matrix[7][5];
        }
        else if (row == '2')
        {
            i = 6;
            j = 5;
            return matrix[6][5];
        }
        else if (row == '3')
        {
            i = 5;
            j = 5;
            return matrix[5][5];
        }
        else if (row == '4')
        {
            i = 4;
            j = 5;
            return matrix[4][5];
        }
        else if (row == '5')
        {
            i = 3;
            j = 5;
            return matrix[3][5];
        }
        else if (row == '6')
        {
            i = 2;
            j = 5;
            return matrix[2][5];
        }
        else if (row == '7')
        {
            i = 1;
            j = 5;
            return matrix[1][5];
        }
        else if (row == '8')
        {
            i = 0;
            j = 5;
            return matrix[0][5];
        }
        else
            return 'x';
    }
    else if (column == 'g' or column == 'G')
    {
        if (row == '1')
        {
            i = 7;
            j = 6;
            return matrix[7][6];
        }
        else if (row == '2')
        {
            i = 6;
            j = 6;
            return matrix[6][6];
        }
        else if (row == '3')
        {
            i = 5;
            j = 6;
            return matrix[5][6];
        }
        else if (row == '4')
        {
            i = 4;
            j = 6;
            return matrix[4][6];
        }
        else if (row == '5')
        {
            i = 3;
            j = 6;
            return matrix[3][6];
        }
        else if (row == '6')
        {
            i = 2;
            j = 6;
            return matrix[2][6];
        }
        else if (row == '7')
        {
            i = 1;
            j = 6;
            return matrix[1][6];
        }
        else if (row == '8')
        {
            i = 0;
            j = 6;
            return matrix[0][6];
        }
        else
            return 'x';
    }
    else if (column == 'h' or column == 'H')
    {
        if (row == '1')
        {
            i = 7;
            j = 7;
            return matrix[7][7];
        }
        else if (row == '2')
        {
            i = 6;
            j = 7;
            return matrix[6][7];
        }
        else if (row == '3')
        {
            i = 5;
            j = 7;
            return matrix[5][7];
        }
        else if (row == '4')
        {
            i = 4;
            j = 7;
            return matrix[4][7];
        }
        else if (row == '5')
        {
            i = 3;
            j = 7;
            return matrix[3][7];
        }
        else if (row == '6')
        {
            i = 2;
            j = 7;
            return matrix[2][7];
        }
        else if (row == '7')
        {
            i = 1;
            j = 7;
            return matrix[1][7];
        }
        else if (row == '8')
        {
            i = 0;
            j = 7;
            return matrix[0][7];
        }
        else
            return 'x';
    }
    else
        return 'x';
}

/*
This function replaces the initial space chosen by the user with either a '#' or a ' "

Return Value
------------
This is a nonvalue returning function

Function Parameters
----------------
No parameters

Local Variables
---------------
no local variables
*/

void pieceEliminator()
{
    if(i == 0 or i == 2 or i == 4 or i == 6)        // narrows down the board
    {
        if(j == 0 or j == 2 or j == 4 or j == 6)
            matrix[i][j] = '#';
        else
            matrix[i][j] = ' ';
    }
    else
    {
        if(j == 0 or j == 2 or j == 4 or j == 6)
            matrix[i][j] = ' ';
        else
            matrix[i][j] = '#';
    }
}

/*
This function places the initial piece in a new location

Return Value
------------
bool    error    error check

Function Parameters
----------------
char    piece    passes along the piece information for move check and places piece

Local Variables
---------------
bool    error    error check
*/

bool piecePlacer(char piece)
{
    bool error;
    //cout << "Enter the column and then row of where you'd like to move too" << endl;
    cin >> column2 >> row2;         //user input to decide where the piece should go
    if((column == 'd' or column == 'D') and (row == 'r' or row == 'R') and (column2 == 'a' or column2 == 'A') and (row2 == 'w' or row2 == 'W'))
        return true;
    error = moveChecker(piece);
    if (error == false)         //error check
    {

        if(player == "White")
            whiteboardSetup();

        else if(player == "Black")
            blackboardSetup();
        cout << setw(20) << "" << "Move not legal! (EX. WRITTEN AS: e2 e4)" << endl;
        return false;
    }
    if (column2 == 'a' or column2 == 'A')           //places piece in new place
    {
        if (row2 == '1')
            matrix[7][0] = piece;
        else if (row2 == '2')
            matrix[6][0] = piece;
        else if (row2 == '3')
            matrix[5][0] = piece;
        else if (row2 == '4')
            matrix[4][0] = piece;
        else if (row2 == '5')
            matrix[3][0] = piece;
        else if (row2 == '6')
            matrix[2][0] = piece;
        else if (row2 == '7')
            matrix[1][0] = piece;
        else if (row2 == '8')
            matrix[0][0] = piece;
    }
    else if (column2 == 'b' or column2 == 'B')
    {
        if (row2 == '1')
            matrix[7][1] = piece;
        else if (row2 == '2')
            matrix[6][1] = piece;
        else if (row2 == '3')
            matrix[5][1] = piece;
        else if (row2 == '4')
            matrix[4][1] = piece;
        else if (row2 == '5')
            matrix[3][1] = piece;
        else if (row2 == '6')
            matrix[2][1] = piece;
        else if (row2 == '7')
            matrix[1][1] = piece;
        else if (row2 == '8')
            matrix[0][1] = piece;
    }
    else if (column2 == 'c' or column2 == 'C')
    {
        if (row2 == '1')
            matrix[7][2] = piece;
        else if (row2 == '2')
            matrix[6][2] = piece;
        else if (row2 == '3')
            matrix[5][2] = piece;
        else if (row2 == '4')
            matrix[4][2] = piece;
        else if (row2 == '5')
            matrix[3][2] = piece;
        else if (row2 == '6')
            matrix[2][2] = piece;
        else if (row2 == '7')
            matrix[1][2] = piece;
        else if (row2 == '8')
            matrix[0][2] = piece;
    }
    else if (column2 == 'd' or column2 == 'D')
    {
        if (row2 == '1')
            matrix[7][3] = piece;
        else if (row2 == '2')
            matrix[6][3] = piece;
        else if (row2 == '3')
            matrix[5][3] = piece;
        else if (row2 == '4')
            matrix[4][3] = piece;
        else if (row2 == '5')
            matrix[3][3] = piece;
        else if (row2 == '6')
            matrix[2][3] = piece;
        else if (row2 == '7')
            matrix[1][3] = piece;
        else if (row2 == '8')
            matrix[0][3] = piece;
    }
    else if (column2 == 'e' or column2 == 'E')
    {
        if (row2 == '1')
            matrix[7][4] = piece;
        else if (row2 == '2')
            matrix[6][4] = piece;
        else if (row2 == '3')
            matrix[5][4] = piece;
        else if (row2 == '4')
            matrix[4][4] = piece;
        else if (row2 == '5')
            matrix[3][4] = piece;
        else if (row2 == '6')
            matrix[2][4] = piece;
        else if (row2 == '7')
            matrix[1][4] = piece;
        else if (row2 == '8')
            matrix[0][4] = piece;
    }
    else if (column2 == 'f' or column2 == 'F')
    {
        if (row2 == '1')
            matrix[7][5] = piece;
        else if (row2 == '2')
            matrix[6][5] = piece;
        else if (row2 == '3')
            matrix[5][5] = piece;
        else if (row2 == '4')
            matrix[4][5] = piece;
        else if (row2 == '5')
            matrix[3][5] = piece;
        else if (row2 == '6')
            matrix[2][5] = piece;
        else if (row2 == '7')
            matrix[1][5] = piece;
        else if (row2 == '8')
            matrix[0][5] = piece;
    }
    else if (column2 == 'g' or column2 == 'G')
    {
        if (row2 == '1')
            matrix[7][6] = piece;
        else if (row2 == '2')
            matrix[6][6] = piece;
        else if (row2 == '3')
            matrix[5][6] = piece;
        else if (row2 == '4')
            matrix[4][6] = piece;
        else if (row2 == '5')
            matrix[3][6] = piece;
        else if (row2 == '6')
            matrix[2][6] = piece;
        else if (row2 == '7')
            matrix[1][6] = piece;
        else if (row2 == '8')
            matrix[0][6] = piece;
    }
    else if (column2 == 'h' or column2 == 'H')
    {
        if (row2 == '1')
            matrix[7][7] = piece;
        else if (row2 == '2')
            matrix[6][7] = piece;
        else if (row2 == '3')
            matrix[5][7] = piece;
        else if (row2 == '4')
            matrix[4][7] = piece;
        else if (row2 == '5')
            matrix[3][7] = piece;
        else if (row2 == '6')
            matrix[2][7] = piece;
        else if (row2 == '7')
            matrix[1][7] = piece;
        else if (row2 == '8')
            matrix[0][7] = piece;
    }
    return true;
}

/*
This VERY LONG function is to check if the new location chosen by the user is
a legal chess move

Return Value
------------
bool    true/false    if the move was legal or not

Function Parameters
----------------
char    piece   to check possible moves

Local Variables
---------------
char    test    copy of global variable of row
char    test2[8]    copy of global variable of row2
char    check    copy of global variable of column
char    check2[8]    copy of global variable of column2
*/

bool moveChecker(char piece)
{
    char test, test2[8], check, check2[8];
    if (piece == 'p')
    {
        if (row == '7')
        {
            if (row2 == '5' and column == column2)      //initial double jump of pawn
                return true;
        }
        test = row;
        test2[0] = row2 + 1;
        check = column;
        check2[0] = column2 + 1;
        check2[1] = column2 - 1;
        if (column == column2 and test == test2[0])
        {
            if(matrix[i+1][j] == '#' or matrix[i+1][j] == ' ')          //if the pawn moved foward with no piece in front of it
                return true;
            else return false;
        }
        else if (check == check2[0])
        {
            if (test == test2[0])
            {
                if(matrix[i+1][j-1] <= 'Z' and matrix[i+1][j-1] >= 'A')         //if the pawn captured another enemy piece
                    return true;
                else return false;
            }
            else return false;
        }
        else if (check == check2[1])
        {
            if (test == test2[0])
            {
                if(matrix[i+1][j+1] <= 'Z' and matrix[i+1][j+1] >= 'A')         //if the pawn captured another enemy piece
                    return true;
                else return false;
            }
            else return false;
        }
        else return false;
    }
    if (piece == 'P')
    {
        if (row == '2')
        {
            if (row2 == '4' and column == column2)      //initial double jump of pawn
                return true;
        }
        test = row;
        test2[0] = row2 - 1;
        check = column;
        check2[0] = column2 + 1;
        check2[1] = column2 - 1;
        if (column == column2 and test == test2[0])
        {
            if(matrix[i-1][j] == '#' or matrix[i-1][j] == ' ')          //if the pawn moved foward with no piece in front of it
                return true;
            else return false;
        }
        else if (check == check2[0])
        {
            if (test == test2[0])
            {
                if(matrix[i-1][j-1] <= 'z' and matrix[i-1][j-1] >= 'a')         //if the pawn captured another enemy piece
                    return true;
                else return false;
            }
            else return false;
        }
        else if (check == check2[1])
        {
            if (test == test2[0])
            {
                if(matrix[i-1][j+1] <= 'z' and matrix[i-1][j+1] >= 'a')         //if the pawn captured another enemy piece
                    return true;
                else return false;
            }
            else return false;
        }
        else return false;
    }
    if (piece == 'n')
    {
        test = row;
        check = column;
        test2[0] = row2 - 2;
        test2[1] = row2 - 1;
        test2[2] = row2 + 1;
        test2[3] = row2 + 2;
        check2[0] = column2 - 1;
        check2[1] = column2 - 2;
        check2[2] = column2 + 1;
        check2[3] = column2 + 2;
        bool error;
        if (check == check2[0] and test == test2[0])
            {
                if(matrix[i-2][j+1] < 'a' or matrix[i-2][j+1] > 'z')            //checks two spaces in one direction and 1 space in another and checks if player is not capturing his own piece
                    return true;
            }
        if (check == check2[0] and test == test2[3])
            {
                if(matrix[i+2][j+1] < 'a' or matrix[i+2][j+1] > 'z')
                    return true;
            }
        if (check == check2[1] and test == test2[1])
            {
                if(matrix[i-1][j+2] < 'a' or matrix[i-1][j+2] > 'z')
                    return true;
            }
        if (check == check2[1] and test == test2[2])
            {
                if(matrix[i+1][j+2] < 'a' or matrix[i+1][j+2] > 'z')
                    return true;
            }
        if (check == check2[2] and test == test2[0])
            {
                if(matrix[i-2][j-1] < 'a' or matrix[i-2][j-1] > 'z')
                    return true;
            }
        if (check == check2[2] and test == test2[3])
            {
                if(matrix[i+2][j-1] < 'a' or matrix[i+2][j-1] > 'z')
                    return true;
            }
        if (check == check2[3] and test == test2[1])
            {
                if(matrix[i-1][j-2] < 'a' or matrix[i-1][j-2] > 'z')
                    return true;
            }
        if (check == check2[3] and test == test2[2])
            {
                if(matrix[i+1][j-2] < 'a' or matrix[i+1][j-2] > 'z')
                    return false;
            }
        return false;
    }
    if (piece == 'N')
    {
        test = row;
        check = column;
        test2[0] = row2 - 2;
        test2[1] = row2 - 1;
        test2[2] = row2 + 1;
        test2[3] = row2 + 2;
        check2[0] = column2 - 1;
        check2[1] = column2 - 2;
        check2[2] = column2 + 1;
        check2[3] = column2 + 2;
        bool error;
        if (check == check2[0] and test == test2[0])
            {
                if(matrix[i-2][j+1] < 'A' or matrix[i-2][j+1] > 'Z')            //checks two spaces in one direction and 1 space in another and checks if player is not capturing his own piece
                    return true;
            }
        if (check == check2[0] and test == test2[3])
            {
                if(matrix[i+2][j+1] < 'A' or matrix[i+2][j+1] > 'Z')
                    return true;
            }
        if (check == check2[1] and test == test2[1])
            {
                if(matrix[i-1][j+2] < 'A' or matrix[i-1][j+2] > 'Z')
                    return true;
            }
        if (check == check2[1] and test == test2[2])
            {
                if(matrix[i+1][j+2] < 'A' or matrix[i+1][j+2] > 'Z')
                    return true;
            }
        if (check == check2[2] and test == test2[0])
            {
                if(matrix[i-2][j-1] < 'A' or matrix[i-2][j-1] > 'Z')
                    return true;
            }
        if (check == check2[2] and test == test2[3])
            {
                if(matrix[i+2][j-1] < 'A' or matrix[i+2][j-1] > 'Z')
                    return true;
            }
        if (check == check2[3] and test == test2[1])
            {
                if(matrix[i-1][j-2] < 'A' or matrix[i-1][j-2] > 'Z')
                    return true;
            }
        if (check == check2[3] and test == test2[2])
            {
                if(matrix[i+1][j-2] < 'A' or matrix[i+1][j-2] > 'Z')
                    return true;
            }
        return false;
    }
    if(piece == 'b')
    {
        int cnt;
        bool exit = false, upleft = false, upright = false, downleft = false, downright = false;
        test = row;
        check = column;
        test2[0] = row2;
        test2[1] = row2;
        test2[2] = row2;
        test2[3] = row2;
        test2[4] = row2;
        check2[0] = column2;
        check2[1] = column2;
        check2[2] = column2;
        check2[3] = column2;
        check2[4] = column2;
        for (cnt = 0; exit == false and cnt < 8; cnt ++)         //checks if the final position is diagonal to the beginning position
        {
            test2[1]++;
            check2[1]++;
            test2[2]++;
            check2[2]--;
            test2[3]--;
            check2[3]++;
            test2[4]--;
            check2[4]--;
            if(test == test2[1] and check == check2[1])
            {
                downleft = true;
                exit = true;
            }
            if(test == test2[2] and check == check2[2])
            {
                downright = true;
                exit = true;
            }
            if(test == test2[3] and check == check2[3])
            {
                upleft = true;
                exit = true;
            }
            if(test == test2[4] and check == check2[4])
            {
                upright = true;
                exit = true;
            }
        }
        if (exit == true)
        {
            int num;
            if (downleft == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j-num] != ' ' and matrix[i+num][j-num] != '#')
                        return false;
                }
                if(matrix[i+num][j-num] < 'a' or matrix[i+num][j-num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (downright == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j+num] != ' ' and matrix[i+num][j+num] != '#')
                        return false;
                }
                if(matrix[i+num][j+num] < 'a' or matrix[i+num][j+num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (upleft == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j-num] != ' ' and matrix[i-num][j-num] != '#')
                        return false;
                }
                if(matrix[i-num][j-num] < 'a' or matrix[i-num][j-num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (upright == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j+num] != ' ' and matrix[i-num][j+num] != '#')
                        return false;
                }
                if(matrix[i-num][j+num] < 'a' or matrix[i-num][j+num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            return false;
        }
        return false;
    }
    if(piece == 'B')
    {
        int cnt;
        bool exit = false, upleft = false, upright = false, downleft = false, downright = false;
        test = row;
        check = column;
        test2[0] = row2;
        test2[1] = row2;
        test2[2] = row2;
        test2[3] = row2;
        test2[4] = row2;
        check2[0] = column2;
        check2[1] = column2;
        check2[2] = column2;
        check2[3] = column2;
        check2[4] = column2;
        for (cnt = 0; exit == false and cnt < 8; cnt ++)         //checks if the final position is diagonal to the beginning position
        {
            test2[1]++;
            check2[1]++;
            test2[2]++;
            check2[2]--;
            test2[3]--;
            check2[3]++;
            test2[4]--;
            check2[4]--;
            if(test == test2[1] and check == check2[1])
            {
                downleft = true;
                exit = true;
            }
            if(test == test2[2] and check == check2[2])
            {
                downright = true;
                exit = true;
            }
            if(test == test2[3] and check == check2[3])
            {
                upleft = true;
                exit = true;
            }
            if(test == test2[4] and check == check2[4])
            {
                upright = true;
                exit = true;
            }
        }
        if (exit == true)
        {
            int num;
            if (downleft == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j-num] != ' ' and matrix[i+num][j-num] != '#')
                        return false;
                }
                if(matrix[i+num][j-num] < 'A' or matrix[i+num][j-num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (downright == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j+num] != ' ' and matrix[i+num][j+num] != '#')
                        return false;
                }
                if(matrix[i+num][j+num] < 'A' or matrix[i+num][j+num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (upleft == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j-num] != ' ' and matrix[i-num][j-num] != '#')
                        return false;
                }
                if(matrix[i-num][j-num] < 'A' or matrix[i-num][j-num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (upright == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j+num] != ' ' and matrix[i-num][j+num] != '#')
                        return false;
                }
                if(matrix[i-num][j+num] < 'A' or matrix[i-num][j+num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            return false;
        }
        return false;
    }
    if (piece == 'r')
    {
        int cnt;
        bool exit = false, up = false, right = false, left = false, down = false;
        test = row;
        check = column;
        test2[0] = row2;
        test2[1] = row2;
        test2[2] = row2;
        test2[3] = row2;
        test2[4] = row2;
        check2[0] = column2;
        check2[1] = column2;
        check2[2] = column2;
        check2[3] = column2;
        check2[4] = column2;
        for (cnt = 0; exit == false and cnt < 8; cnt ++)
        {
            test2[1]++;
            check2[2]--;
            test2[3]--;
            check2[4]++;
            if(test == test2[1] and check == check2[1])
            {
                down = true;
                exit = true;
            }
            if(test == test2[2] and check == check2[2])
            {
                right = true;
                exit = true;
            }
            if(test == test2[3] and check == check2[3])
            {
                up = true;
                exit = true;
            }
            if(test == test2[4] and check == check2[4])
            {
                left = true;
                exit = true;
            }
        }
        if(exit == true)
        {
            int num;
            if (down == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j] != ' ' and matrix[i+num][j] != '#')
                        return false;
                }
                if(matrix[i+num][j] < 'a' or matrix[i+num][j] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (up == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j] != ' ' and matrix[i-num][j] != '#')
                        return false;
                }
                if(matrix[i-num][j] < 'a' or matrix[i-num][j] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (right == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i][j+num] != ' ' and matrix[i][j+num] != '#')
                        return false;
                }
                if(matrix[i][j+num] < 'a' or matrix[i][j+num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (left == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i][j-num] != ' ' and matrix[i][j-num] != '#')
                        return false;
                }
                if(matrix[i][j-num] < 'a' or matrix[i][j-num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else return false;
        }
        return false;
    }
    if (piece == 'R')
    {
        int cnt;
        bool exit = false, up = false, right = false, left = false, down = false;
        test = row;
        check = column;
        test2[0] = row2;
        test2[1] = row2;
        test2[2] = row2;
        test2[3] = row2;
        test2[4] = row2;
        check2[0] = column2;
        check2[1] = column2;
        check2[2] = column2;
        check2[3] = column2;
        check2[4] = column2;
        for (cnt = 0; exit == false and cnt < 8; cnt ++)
        {
            test2[1]++;
            check2[2]--;
            test2[3]--;
            check2[4]++;
            if(test == test2[1] and check == check2[1])
            {
                down = true;
                exit = true;
            }
            if(test == test2[2] and check == check2[2])
            {
                right = true;
                exit = true;
            }
            if(test == test2[3] and check == check2[3])
            {
                up = true;
                exit = true;
            }
            if(test == test2[4] and check == check2[4])
            {
                left = true;
                exit = true;
            }
        }
        if(exit == true)
        {
            int num;
            if (down == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j] != ' ' and matrix[i+num][j] != '#')
                        return false;
                }
                if(matrix[i+num][j] < 'A' or matrix[i+num][j] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (up == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j] != ' ' and matrix[i-num][j] != '#')
                        return false;
                }
                if(matrix[i-num][j] < 'A' or matrix[i-num][j] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (right == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i][j+num] != ' ' and matrix[i][j+num] != '#')
                        return false;
                }
                if(matrix[i][j+num] < 'A' or matrix[i][j+num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (left == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i][j-num] != ' ' and matrix[i][j-num] != '#')
                        return false;
                }
                if(matrix[i][j-num] < 'A' or matrix[i][j-num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else return false;
        }
        return false;
    }
    if(piece == 'q')
    {
        int cnt;
        bool exit = false, up = false, right = false, left = false, down = false;
        test = row;
        check = column;
        test2[0] = row2;
        test2[1] = row2;
        test2[2] = row2;
        test2[3] = row2;
        test2[4] = row2;
        check2[0] = column2;
        check2[1] = column2;
        check2[2] = column2;
        check2[3] = column2;
        check2[4] = column2;
        for (cnt = 0; exit == false and cnt < 8; cnt ++)         //checks if the final position is diagonal to the beginning position
        {
            test2[1]++;
            check2[2]--;
            test2[3]--;
            check2[4]++;
            if(test == test2[1] and check == check2[1])
            {
                down = true;
                exit = true;
            }
            if(test == test2[2] and check == check2[2])
            {
                right = true;
                exit = true;
            }
            if(test == test2[3] and check == check2[3])
            {
                up = true;
                exit = true;
            }
            if(test == test2[4] and check == check2[4])
            {
                left = true;
                exit = true;
            }
        }
        if(exit == true)
        {
            int num;
            if (down == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j] != ' ' and matrix[i+num][j] != '#')
                        return false;
                }
                if(matrix[i+num][j] < 'a' or matrix[i+num][j] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (up == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j] != ' ' and matrix[i-num][j] != '#')
                        return false;
                }
                if(matrix[i-num][j] < 'a' or matrix[i-num][j] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (right == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i][j+num] != ' ' and matrix[i][j+num] != '#')
                        return false;
                }
                if(matrix[i][j+num] < 'a' or matrix[i][j+num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (left == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i][j-num] != ' ' and matrix[i][j-num] != '#')
                        return false;
                }
                if(matrix[i][j-num] < 'a' or matrix[i][j-num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else return false;
        }
        exit = false;
        bool upleft = false, upright = false, downleft = false, downright = false;
        test = row;
        check = column;
        test2[0] = row2;
        test2[1] = row2;
        test2[2] = row2;
        test2[3] = row2;
        test2[4] = row2;
        check2[0] = column2;
        check2[1] = column2;
        check2[2] = column2;
        check2[3] = column2;
        check2[4] = column2;
        for (cnt = 0; exit == false and cnt < 8; cnt ++)
        {
            test2[1]++;
            check2[1]++;
            test2[2]++;
            check2[2]--;
            test2[3]--;
            check2[3]++;
            test2[4]--;
            check2[4]--;
            if(test == test2[1] and check == check2[1])
            {
                downleft = true;
                exit = true;
            }
            if(test == test2[2] and check == check2[2])
            {
                downright = true;
                exit = true;
            }
            if(test == test2[3] and check == check2[3])
            {
                upleft = true;
                exit = true;
            }
            if(test == test2[4] and check == check2[4])
            {
                upright = true;
                exit = true;
            }
        }
        if (exit == true)
        {
            int num;
            if (downleft == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j-num] != ' ' and matrix[i+num][j-num] != '#')
                        return false;
                }
                if(matrix[i+num][j-num] < 'a' or matrix[i+num][j-num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (downright == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j+num] != ' ' and matrix[i+num][j+num] != '#')
                        return false;
                }
                if(matrix[i+num][j+num] < 'a' or matrix[i+num][j+num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (upleft == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j-num] != ' ' and matrix[i-num][j-num] != '#')
                        return false;
                }
                if(matrix[i-num][j-num] < 'a' or matrix[i-num][j-num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (upright == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j+num] != ' ' and matrix[i-num][j+num] != '#')
                        return false;
                }
                if(matrix[i-num][j+num] < 'a' or matrix[i-num][j+num] > 'z')            //checks if final destination is occupied by players piece
                    return true;
            }
            return false;
        }
        return false;
    }
    if(piece == 'Q')
    {
        int cnt;
        bool exit = false, up = false, right = false, left = false, down = false;
        test = row;
        check = column;
        test2[0] = row2;
        test2[1] = row2;
        test2[2] = row2;
        test2[3] = row2;
        test2[4] = row2;
        check2[0] = column2;
        check2[1] = column2;
        check2[2] = column2;
        check2[3] = column2;
        check2[4] = column2;
        for (cnt = 0; exit == false and cnt < 8; cnt ++)         //checks if the final position is diagonal to the beginning position
        {
            test2[1]++;
            check2[2]--;
            test2[3]--;
            check2[4]++;
            if(test == test2[1] and check == check2[1])
            {
                down = true;
                exit = true;
            }
            if(test == test2[2] and check == check2[2])
            {
                right = true;
                exit = true;
            }
            if(test == test2[3] and check == check2[3])
            {
                up = true;
                exit = true;
            }
            if(test == test2[4] and check == check2[4])
            {
                left = true;
                exit = true;
            }
        }
        if(exit == true)
        {
            int num;
            if (down == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j] != ' ' and matrix[i+num][j] != '#')
                        return false;
                }
                if(matrix[i+num][j] < 'A' or matrix[i+num][j] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (up == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j] != ' ' and matrix[i-num][j] != '#')
                        return false;
                }
                if(matrix[i-num][j] < 'A' or matrix[i-num][j] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (right == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i][j+num] != ' ' and matrix[i][j+num] != '#')
                        return false;
                }
                if(matrix[i][j+num] < 'A' or matrix[i][j+num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (left == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i][j-num] != ' ' and matrix[i][j-num] != '#')
                        return false;
                }
                if(matrix[i][j-num] < 'A' or matrix[i][j-num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else return false;
        }
        exit = false;
        bool upleft = false, upright = false, downleft = false, downright = false;
        test = row;
        check = column;
        test2[0] = row2;
        test2[1] = row2;
        test2[2] = row2;
        test2[3] = row2;
        test2[4] = row2;
        check2[0] = column2;
        check2[1] = column2;
        check2[2] = column2;
        check2[3] = column2;
        check2[4] = column2;
        for (cnt = 0; exit == false and cnt < 8; cnt ++)
        {
            test2[1]++;
            check2[1]++;
            test2[2]++;
            check2[2]--;
            test2[3]--;
            check2[3]++;
            test2[4]--;
            check2[4]--;
            if(test == test2[1] and check == check2[1])
            {
                downleft = true;
                exit = true;
            }
            if(test == test2[2] and check == check2[2])
            {
                downright = true;
                exit = true;
            }
            if(test == test2[3] and check == check2[3])
            {
                upleft = true;
                exit = true;
            }
            if(test == test2[4] and check == check2[4])
            {
                upright = true;
                exit = true;
            }
        }
        if (exit == true)
        {
            int num;
            if (downleft == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j-num] != ' ' and matrix[i+num][j-num] != '#')
                        return false;
                }
                if(matrix[i+num][j-num] < 'A' or matrix[i+num][j-num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (downright == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i+num][j+num] != ' ' and matrix[i+num][j+num] != '#')
                        return false;
                }
                if(matrix[i+num][j+num] < 'A' or matrix[i+num][j+num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (upleft == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j-num] != ' ' and matrix[i-num][j-num] != '#')
                        return false;
                }
                if(matrix[i-num][j-num] < 'A' or matrix[i-num][j-num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            else if (upright == true)
            {
                for(num = 1; num != cnt; num++)         //checks if pieces between intial and final are occupied or not
                {
                    if(matrix[i-num][j+num] != ' ' and matrix[i-num][j+num] != '#')
                        return false;
                }
                if(matrix[i-num][j+num] < 'A' or matrix[i-num][j+num] > 'Z')            //checks if final destination is occupied by players piece
                    return true;
            }
            return false;
        }
        return false;
    }
    if(piece == 'k')
    {
        bool exit = false, up = false, right = false, left = false, down = false;
        bool upleft = false, upright = false, downleft = false, downright = false;
        test = row;
        check = column;
        test2[0] = row2;
        check2[0] = column2;
        test2[1] = row + 1;
        test2[2] = row - 1;
        check2[1] = column + 1;
        check2[2] = column - 1;
        if(check2[1] == check2[0] and test == test2[0])         //checks if move is 1 square in any direction
        {
            right = true;
            exit = true;
        }
        if(check2[2] == check2[0] and test == test2[0])
        {
            left = true;
            exit = true;
        }
        if(check == check2[0] and test2[0] == test2[1])
        {
            up = true;
            exit = true;
        }
        if(check == check2[0] and test2[0] == test2[2])
        {
            down = true;
            exit = true;
        }
        if(check2[2] == check2[0] and test2[0] == test2[2])
        {
            downleft = true;
            exit = true;
        }
        if(check2[1] == check2[0] and test2[0] == test2[2])
        {
            downright = true;
            exit = true;
        }
        if(check2[2] == check2[0] and test2[0] == test2[1])
        {
            upleft = true;
            exit = true;
        }
        if(check2[1] == check2[0] and test2[0] == test2[1])
        {
            upright = true;
            exit = true;
        }
        if(exit == true)            //checks if final destination is players piece
        {
            if(up == true)
            {
                if(matrix[i-1][j] < 'a' or matrix[i-1][j] > 'z')
                    return true;
            }
            if(right == true)
            {
                if(matrix[i][j+1] < 'a' or matrix[i][j+1] > 'z')
                    return true;
            }
            if(left == true)
            {
                if(matrix[i][j-1] < 'a' or matrix[i][j-1] > 'z')
                    return true;
            }
            if(down == true)
            {
                if(matrix[i+1][j] < 'a' or matrix[i+1][j] > 'z')
                    return true;
            }
            if(upright == true)
            {
                if(matrix[i-1][j+1] < 'a' or matrix[i-1][j+1] > 'z')
                    return true;
            }
            if(downright == true)
            {
                if(matrix[i+1][j+1] < 'a' or matrix[i+1][j+1] > 'z')
                    return true;
            }
            if(upleft == true)
            {
                if(matrix[i-1][j-1] < 'a' or matrix[i-1][j-1] > 'z')
                    return true;
            }
            if(downleft == true)
            {
                if(matrix[i+1][j-1] < 'a' or matrix[i+1][j-1] > 'z')
                    return true;
            }
        }
        return false;
    }
    if(piece == 'K')
    {
        bool exit = false, up = false, right = false, left = false, down = false;
        bool upleft = false, upright = false, downleft = false, downright = false;
        test = row;
        check = column;
        test2[0] = row2;
        check2[0] = column2;
        test2[1] = row + 1;
        test2[2] = row - 1;
        check2[1] = column + 1;
        check2[2] = column - 1;
        if(check2[1] == check2[0] and test == test2[0])         //checks if move is 1 square in any direction
        {
            right = true;
            exit = true;
        }
        if(check2[2] == check2[0] and test == test2[0])
        {
            left = true;
            exit = true;
        }
        if(check == check2[0] and test2[0] == test2[1])
        {
            up = true;
            exit = true;
        }
        if(check == check2[0] and test2[0] == test2[2])
        {
            down = true;
            exit = true;
        }
        if(check2[2] == check2[0] and test2[0] == test2[2])
        {
            downleft = true;
            exit = true;
        }
        if(check2[1] == check2[0] and test2[0] == test2[2])
        {
            downright = true;
            exit = true;
        }
        if(check2[2] == check2[0] and test2[0] == test2[1])
        {
            upleft = true;
            exit = true;
        }
        if(check2[1] == check2[0] and test2[0] == test2[1])
        {
            upright = true;
            exit = true;
        }
        if(exit == true)            //checks if final destination is players piece
        {
            if(up == true)
            {
                if(matrix[i-1][j] < 'A' or matrix[i-1][j] > 'Z')
                    return true;
            }
            if(right == true)
            {
                if(matrix[i][j+1] < 'A' or matrix[i][j+1] > 'Z')
                    return true;
            }
            if(left == true)
            {
                if(matrix[i][j-1] < 'A' or matrix[i][j-1] > 'Z')
                    return true;
            }
            if(down == true)
            {
                if(matrix[i+1][j] < 'A' or matrix[i+1][j] > 'Z')
                    return true;
            }
            if(upright == true)
            {
                if(matrix[i-1][j+1] < 'A' or matrix[i-1][j+1] > 'Z')
                    return true;
            }
            if(downright == true)
            {
                if(matrix[i+1][j+1] < 'A' or matrix[i+1][j+1] > 'Z')
                    return true;
            }
            if(upleft == true)
            {
                if(matrix[i-1][j-1] < 'A' or matrix[i-1][j-1] > 'Z')
                    return true;
            }
            if(downleft == true)
            {
                if(matrix[i+1][j-1] < 'A' or matrix[i+1][j-1] > 'Z')
                    return true;
            }
        }
        return false;
    }
    return false;
}

/*
This function checks if there is only one king and if so, then the player wins

Return Value
------------
bool    true/false    wins game

Function Parameters
----------------
No parameters

Local Variables
---------------
int    y    checks matrix
int    x    checks matrix
int    num      counts the kings
*/

bool winCheck()
{
    int y, x, num = 0;
    for(y = 0; y < 8; y++)          //checks if there are two kings
    {
        for(x = 0; x < 8; x++)
        {
            if (matrix[y][x] == 'k' or matrix[y][x] == 'K')
                num++;
        }
    }
    if(num == 2)
        return false;
    else if(num == 1)
        return true;
    else return false;
}

/*
This function is an option for if the players would like to agree to a draw or not

Return Value
------------
bool    true/false    if a draw has been decided then the function returns true

Function Parameters
----------------
bool    ask    this value decides if a drawn as asked for

Local Variables
---------------
char   choice   decision between
*/


bool drawCheck(bool& ask)
{
    char choice;
    bool error;
    if((column == 'd' or column == 'D') and (row == 'r' or row == 'R') and (column2 == 'a' or column2 == 'A') and (row2 == 'w' or row2 == 'W'))
    {
        if(player == "White")
            blackboardSetup();
        else if(player == "Black")
            whiteboardSetup();
        do
        {
            cout << setw(16) << "" << "Would you like to agree to a draw? (Y/N): ";
            cin >> choice;
            if(choice == 'y' or choice == 'Y')
            {
                ask = false;
                return true;
            }
            else if(choice == 'n' or choice == 'N')
            {
                ask = true;
                error = false;
            }
            else error = true;
        } while (error == true);
        if(player == "White")
            whiteboardSetup();
        else if(player == "Black")
            blackboardSetup();
        return false;
    }
    ask = false;
    return false;
}


int ticTacToe()
{
    bool exit2;
    bool win;
    char choice;
    tttSetup();

    {
//display options
        cout <<"+-------------------------------------------------+"<<endl;
        cout <<"|              Welcome to Tic Tac Toe.            |"<<endl;
        cout <<"+-------------------------------------------------+"<<endl;
        cout <<"|           Choose one of the following.          |"<<endl;
        cout <<"|               A. One Player.                    |"<<endl;
        cout <<"|               B. Two Players.                   |"<<endl;
        cout <<"|               C. Three Players.                 |"<<endl;
        cout <<"|               D. Instructions.                  |"<<endl;
        cout <<"+-------------------------------------------------+"<<endl;


        do
        {
            cin >> choice;  //get choice
            switch (choice) //switch statement for user to choose options A-D
            {
//option a displays message from option a
                case 'A':
                case 'a': if (system("CLS")) system("clear");  //clears screen
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|           Choose one of the following.          |"<<endl;
                    cout <<"|               A. One Player.                    |"<<endl;
                    cout <<"|               B. Two Players.                   |"<<endl;
                    cout <<"|               C. Three Players.                 |"<<endl;
                    cout <<"|               D. Instructions.                  |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|               Sorry, this is only               |"<<endl;
                    cout <<"|                a two player game.               |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|             Please choose A, B, C, D.           |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    exit2 = true;
                    break;
//option b displayes board and determines winner/loser/drawer
                case 'B':
                case 'b':tttBoard();        //displays inital board
                    for (int z=2; z < 12; z++)
                    {

                        if(z%2==0)
                        {
                            inPut2();           //error check function for X
                            tttBoard();         //displays board
                            win = weaner ();    //fucntion checks for winner
                            if (win == 1)
                            {
                                cout <<"|                     X WINS                      |"<<endl;
                                cout <<"+-------------------------------------------------+"<<endl;
                                z = 12;
                            }
                        }
                        else if (z == 11)       //determines if players draw. if loop runs runs 9 times with no winner then draw.
                        {
                            cout <<"|                      DRAW                       |"<<endl;
                            cout <<"+-------------------------------------------------+"<<endl;
                        }
                        else
                        {
                            inPut3();           //error check function for O
                            tttBoard();         //displays board
                            win = weaner ();    //function check for winner
                            if(win == 1)
                            {
                                cout <<"|                     O WINS                      |"<<endl;
                                cout <<"+-------------------------------------------------+"<<endl;
                                z = 12;
                            }

                        }

                    }
                    exit2 = false;
                    break;
//Option C displays message
                case 'c':
                case 'C': if (system("CLS")) system("clear");   //clears screen
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|           Choose one of the following.          |"<<endl;
                    cout <<"|               A. One Player.                    |"<<endl;
                    cout <<"|               B. Two Players.                   |"<<endl;
                    cout <<"|               C. Three Players.                 |"<<endl;
                    cout <<"|               D. Instructions.                  |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|                     Sorry !                     |"<<endl;
                    cout <<"|          TTT is only a two player game.         |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|             Please choose A, B, C, D.           |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    exit2 = true;
                    break;
//option D displays instuction on how to play game.
                case 'd':
                case 'D': if (system("CLS")) system("clear");   //clears screen
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|           Choose one of the following.          |"<<endl;
                    cout <<"|               A. One Player.                    |"<<endl;
                    cout <<"|               B. Two Players.                   |"<<endl;
                    cout <<"|               C. Three Players.                 |"<<endl;
                    cout <<"|               D. Instructions.                  |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|             The Point of Tic Tac Toe            |"<<endl;
                    cout <<"|             is to get three in a row.           |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|             Please choose A, B, C, D.           |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    exit2 = true;
                    break;
//if anything else inputted then suggested error message pops out.
                default: if (system("CLS")) system("clear");    //clears screen
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|           Choose one of the following.          |"<<endl;
                    cout <<"|               A. One Player.                    |"<<endl;
                    cout <<"|               B. Two Players.                   |"<<endl;
                    cout <<"|               C. Three Players.                 |"<<endl;
                    cout <<"|               D. Instructions.                  |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    cout <<"|             Please choose A, B, C, D.           |"<<endl;
                    cout <<"+-------------------------------------------------+"<<endl;
                    exit2 = true;
                    break;
            }
        } while (exit2 == true);
        cout << "               PRESS ENTER TO CONTINUE" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        return 0;
    }
}



void tttSetup()
{
    char letter = '1';
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 3; x++)
        {
            ttt[y][x] = letter;
            letter ++;
        }
    }
}


//  *********************************************************************************  //
//                                  inPut2                                             //
//                                                                                     //
//   task:      The purpose of this function is to make sure the user does not enter   //
//              anything else but what is asked. So if the user enters 'a' it will     //
//              output an error.                                                       //
//                                                                                     //
//   data in:   the data user enters                                                   //
//   data out:  Displays error if error                                                //
//                                                                                     //
//   ********************************************************************************  //

void inPut2 ()
{
    bool errorC4;

    {
        do {
            int a;

            cout <<"|                X Enter A Number:                |"<<endl;
            cout <<"+-------------------------------------------------+"<<endl;
            cin >> a;

            if ((a != 1 && a != 2 &&  a != 3 &&  a != 4 &&  a != 5 &&  a != 6 &&  a != 7 &&  a != 8 &&  a != 9) || inputC4(a) == true)
            {
                if (system("CLS")) system("clear");    //clears screen
                tttBoard();
                cout <<"|          Error Only Enter Numbers 1-9           |"<<endl;
                cout <<"+-------------------------------------------------+"<<endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                errorC4 = true;
            }
            else
            {
                if      (a == 1)
                    ttt[0][0] = 'X';
                else if (a == 2)
                    ttt[0][1] = 'X';
                else if (a == 3)
                    ttt[0][2] = 'X';
                else if (a == 4)
                    ttt[1][0] = 'X';
                else if (a == 5)
                    ttt[1][1] = 'X';
                else if (a == 6)
                    ttt[1][2] = X;
                else if (a == 7)
                    ttt[2][0] = X;
                else if (a == 8)
                    ttt[2][1] = X;
                else if (a == 9)
                    ttt[2][2] = X;

                errorC4 = false;
            }
        } while (errorC4 == true);


    }

}

//  *********************************************************************************  //
//                                  inPut3                                             //
//                                                                                     //
//   task:      The purpose of this function is to make sure the user does not enter   //
//              anything else but what is asked. So if the user enters 'a' it will     //
//              output an error.                                                       //
//                                                                                     //
//   data in:   the data user enters                                                   //
//   data out:  Displays error if error                                                //
//                                                                                     //
//   ********************************************************************************  //

void inPut3 ()
{
    bool errorC4;

    {
        do {
            int a;

            cout <<"|                O Enter A Number:                |"<<endl;
            cout <<"+-------------------------------------------------+"<<endl;
            cin >> a;  //get A

            if ((a != 1 && a != 2 &&  a != 3 &&  a != 4 &&  a != 5 &&  a != 6 &&  a != 7 &&  a != 8 &&  a != 9 ) || inputC4(a) == true)  //Error check. User can only input numbers (1-9)
            {
                if (system("CLS")) system("clear");     //clears screen
                tttBoard();
                cout <<"|          Error Only Enter Numbers 1-9           |"<<endl;
                cout <<"+-------------------------------------------------+"<<endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                errorC4 = true;
            }
            else
            {
                if      (a == 1)
                    ttt[0][0] = 'O';
                else if (a == 2)
                    ttt[0][1] = 'O';
                else if (a == 3)
                    ttt[0][2] = 'O';
                else if (a == 4)
                    ttt[1][0] = 'O';
                else if (a == 5)
                    ttt[1][1] = 'O';
                else if (a == 6)
                    ttt[1][2] = O;
                else if (a == 7)
                    ttt[2][0] = O;
                else if (a == 8)
                    ttt[2][1] = O;
                else if (a == 9)
                    ttt[2][2] = O;

                errorC4 = false;
            }
        } while (errorC4 == true);
    }

}

//  *********************************************************************************  //
//                                  tttBoard                                           //
//                                                                                     //
//   task:      The purpose of this function is to create the board and input a        //
//              X or O in the correct places                                           //
//                                                                                     //
//   data in:   X or O is inputed with poop[][]                                        //
//   data out:  displays the board                                                     //
//                                                                                     //
//   ********************************************************************************  //

void tttBoard()
{
    if (system("CLS")) system("clear"); //clears screen
    cout <<endl<<endl;                  //Adds blank lines
    cout <<"+-------------------------------------------------+"<<endl;
    cout <<"|                   TIC TAC TOE                   |"<<endl;
    cout <<"+-------------------------------------------------+"<<endl;
    cout <<"|                                                 |"<<endl;
    cout <<"|                     |     |                     |"<<endl;     //function poop is called to update the board with X or O
    cout <<"|                  "<<ttt[0][0]<<"  |  "<<ttt[0][1]<<"  |  "<<ttt[0][2]<<"                  |"<<endl;
    cout <<"|                _____|_____|_____                |"<<endl;
    cout <<"|                     |     |                     |"<<endl;
    cout <<"|                  "<<ttt[1][0]<<"  |  "<<ttt[1][1]<<"  |  "<<ttt[1][2]<<"                  |"<<endl;
    cout <<"|                _____|_____|_____                |"<<endl;
    cout <<"|                     |     |                     |"<<endl;
    cout <<"|                  "<<ttt[2][0]<<"  |  "<<ttt[2][1]<<"  |  "<<ttt[2][2]<<"                  |"<<endl;
    cout <<"|                     |     |                     |"<<endl;
    cout <<"|                                                 |"<<endl;
    cout <<"+-------------------------------------------------+"<<endl;
}


//  *********************************************************************************  //
//                                  weaner                                             //
//                                                                                     //
//   task:      The purpose of this function is to decide or choose the winner of      //
//              Tic Tac Toe by using if statemnts to check if there are 3 in a row.    //
//                                                                                     //
//   data in:   none                                                                   //
//   data out:  displays the board                                                     //
//                                                                                     //
//   ********************************************************************************  //

bool weaner()
{
    if (ttt[0][0] == ttt[0][1] and ttt[0][1] == ttt[0][2])     //checks row 1 for 3 in a row
        return true;
    else if (ttt[1][0] == ttt[1][1] and ttt[1][1] == ttt[1][2]) //checks row 2
        return true;
    else if (ttt[2][0] == ttt[2][1] and ttt[2][1] == ttt[2][2])  //checks row 3
        return true;
    else if (ttt[0][0] == ttt[1][0] and ttt[1][0] == ttt[2][0])   //checks column 1
        return true;
    else if (ttt[0][1] == ttt[1][1] and ttt[1][1] == ttt[2][1])    //checks column 2
        return true;
    else if (ttt[0][2] == ttt[1][2] and ttt[1][2] == ttt[2][2])     //checks column 3
        return true;
    else if (ttt[0][0] == ttt[1][1] and ttt[1][1] == ttt[2][2])      //checks across
        return true;
    else if (ttt[2][0] == ttt[1][1] and ttt[1][1] == ttt[0][2])       //checks across
        return true;
    else return false;
}


//  *********************************************************************************  //
//                                  inputC4                                            //
//                                                                                     //
//   task:      The purpose of this function is to make sure the player does not       //
//              enter a X or O where there is already a X or O.                        //
//                                                                                     //
//   data in:   none                                                                   //
//   data out:  none                                                                   //
//                                                                                     //
//   ********************************************************************************  //

bool inputC4(int b)
{
    int x=0,y=0;    //inialize x and y for error check
    char c = '0';
    switch(b)
    {
        case 9:   x++;
        case 8:   x++;
        case 7:   y++;
                  y++;
            break;
        case 6:   x++;
        case 5:   x++;
        case 4:   y++;
            break;
        case 3:   x++;
        case 2:   x++;
        case 1:     break;
    }
    c += b;
    if(b >= 1 and b <= 9)
    {
        if (ttt[y][x] == c)
            return false;
        else
            return true;
    }
    else
    {
        return true;
    }
}


int connectFour()
{
    bool continuegame=false, redo = true;
    char column;
    int count;


   boardinitializer();
   for (count= 2; continuegame==false && count < 44 ;count++) //game continues if no one has won and under 42 moves has taken place.
   {
    if (count % 2==0) //Determines players turn
        bit='X';
    else if (count % 2==1) //Determines players turn
        bit='O';



   do
   {

        boardbuilder();
        column = movecolumn();
        boardupdater(column,redo);
        continuegame = winc4();

   }
while (redo == true); // if the game is still going keep re building the board
boardbuilder();
}
if(continuegame==true)
        cout << bit << " wins the game! PRESS ENTER" << endl;
    else
    cout << "It is a draw! PRESS ENTER" << endl;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
return 0;
}

//********************************************************************************
// The board initializer function initializes the width of 7 and the height of 6 *
// to have characters printed to.                                                *
//********************************************************************************
void boardinitializer()
{
    for(int y=0; y<6; y++) //establishes a width of 7
    {
        for (int x=0; x<7;x++) //establishes a height of 6
        {
            board [y][x]= ' ';
        }
    }
}

//*********************************************************************************************************************
//                                                     Boardbuilder                                                   *
// task: The board builder function creates the board.                                                                *
// This function prints the board builder characters to the established boundaries from the board initializer function*
//                                                                                                                    *
// Data in: none                                                                                                      *
// Data out: displays board                                                                                           *
//*********************************************************************************************************************
void boardbuilder()
{
    if (system("CLS")) system("clear");
    int y, x;
    cout << setw(20) << "" << "       -----------------" << endl;
    cout << setw(20) << "" << "       |CONNECT 4 GAME!|" << endl;
    cout << setw(20) << "" << "       -----------------" << endl;
    cout << setw(20) << "" << " " << endl;
    cout << setw(20) << "" << "   1   2   3   4   5   6   7";
    //this for loop creates the horizontal boundaries in the board
    for(int y=0; y<6; y++)
    {

        cout << endl << setw(20) << "" << " -----------------------------" << endl;
        //this for loop creates the vertical boundaries in the board
        for(int x=0; x<7;x++)
        {
            if(x==0)
                cout << setw(20) << "" << " | " << board [y][x]; // establishes a width of 20 for the | characters in the board
            else
            cout <<" | " << board [y][x];
        }
        cout << " |";
        if(y == 5)
            cout << endl << setw(20) << "" << " -----------------------------" << endl;
    }
}
//***************************************************************************************************
//                                              movecolumn                                          *
// task: This function gathers the column selection from the user.                                  *
//          This data is stored as a char. The function then checks to see if the entry is in range.*
//          Lastly, the function checks for a draw.                                                 *
//                                                                                                  *
// Data in: keyboard input                                                                          *
// Data out: none                                                                                   *
//***************************************************************************************************
char movecolumn()
{
    char sel;
    bool redo = true;
    int count=0;
    int total=0;
 do
{
    cout << "                " "Select the column you would like to play." << endl;
 cin >> sel;
//This if statement checks if the user types 1-7
  if (sel!= '1' && sel!= '2' && sel!= '3' && sel!='4' && sel!='5' && sel!='6' && sel!='7')
 {
     cout << "ERROR, you have entered an invalid move" << endl;
     redo=true; //marks if an error has taken place
 }
 else
 {
     redo=false;
 }
 }
while(redo==true);

return sel;
}
//********************************************************************************
//                                    Boardupdater                               *
// task: This function updates the board columns based on the user input.        *
//                                                                               *
// Input: Data is inputed from main as char                                      *
// Output: Displays X or O to user on chart.                                     *
//********************************************************************************
void boardupdater(char col, bool& error)
{
    int j;
    char keep;
    error = false;
 if (col == '1') //takes user input and assigns it to the column 0+
    j=0;

 if (col == '2')//takes user input and assigns it to the column 1
    j=1;

 if (col == '3') //takes user input and assigns it to the column 2
    j=2;

 if (col == '4') //takes user input and assigns it to the column 3
    j=3;

 if (col == '5') //takes user input and assigns it to the column 4
    j=4;

 if (col == '6') //takes user input and assigns it to the column 5
    j=5;

 if (col == '7') //takes user input and assigns it to the column 6
    j=6;

 if(board[6][j] == ' ') // establishes the lowest point on the column to print to
    board[6][j] = bit;
 else if(board[5][j] == ' ') // establishes the lowest point on the column to print to
    board[5][j] = bit;
 else if(board[4][j] == ' ') // establishes the lowest point on the column to print to
    board[4][j] = bit;
 else if(board[3][j] == ' ') // establishes the lowest point on the column to print to
    board[3][j] = bit;
 else if(board[2][j] == ' ') // establishes the lowest point on the column to print to
    board[2][j] = bit;
 else if(board[1][j] == ' ') // establishes the lowest point on the column to print to
    board[1][j] = bit;
 else if(board[0][j] == ' ') // establishes the lowest point on the column to print to
    board[0][j] = bit;
else
{
    cout << "ERROR, column is fully occupied" << endl;
    cin.clear(); // clears previous answer if the column selected was occupied.
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // clears buffer
    cin.get(); //pauses for the user to input another selection
    error = true;
}
if (error != true)
    error = false;

}
//******************************************************************************
//                                   winc4                                     *
// task: The winc4 function checks for four consecutive X's or O's in a row.   *
//                                                                             *
// Input: Global variable board builder                                        *
// Output: Bool data type is returned back to main                                 *
//******************************************************************************
bool winc4()
{
    int i, j;
    for(i = 0; i < 6; i++)
    {
        for(j = 0; j < 7; j++)
        {
            if(j <= 3)
            if(board[i][j] == bit && board[i][j+1] == bit and board[i][j+2] == bit and board[i][j+3] == bit) //searches for 4 characters in a row
                return true;
            if(i <= 2)
            if(board[i][j] == bit and board[i+1][j] == bit and board[i+2][j] == bit and board[i+3][j] == bit)
                return true;
            if(j <= 3 && i <= 2)
            if(board[i][j] == bit and board[i+1][j+1] == bit and board[i+2][j+2] == bit and board[i+3][j+3] == bit)
                return true;
            if(j >= 3 && i <= 2)
            if(board[i][j] == bit and board[i+1][j-1] == bit and board[i+2][j-2] == bit and board[i+3][j-3] == bit)
                return true;
        }
    }
    return false;
}


int battleship()//void zach()
    {
        battleSpaces();
        //Variable to initialize Player 1 to attack 1st
        int TURN = 2;

        //PLAYER 1 COORDINATES
        char ship1row, ship1column;//Coordinates of Ship 1
        char ship2_1_row, ship2_1_column, ship2_2_row, ship2_2_column;//Coordinates of Ship 2
        char ship3_1_row, ship3_1_column, ship3_2_row, ship3_2_column, ship3_3_row, ship3_3_column;//Coordinates of Ship 3
        char ship4_1_row, ship4_1_column, ship4_2_row, ship4_2_column, ship4_3_row, ship4_3_column, ship4_4_row, ship4_4_column;//Coordinates of Ship 4

        //PLAYER 2 COORDINATES
        char ship1row_2, ship1column_2;//Coordinates for Ship 1
        char ship2_1_row_2, ship2_1_column_2, ship2_2_row_2, ship2_2_column_2;//Coordinates for Ship 2
        char ship3_1_row_2, ship3_1_column_2, ship3_2_row_2, ship3_2_column_2, ship3_3_row_2, ship3_3_column_2;//Coordinates of Ship 3
        char ship4_1_row_2, ship4_1_column_2, ship4_2_row_2, ship4_2_column_2, ship4_3_row_2, ship4_3_column_2, ship4_4_row_2, ship4_4_column_2;//Coordinates for Ship 4

        //1st screen
        /* ************************************************************ */
        cout << endl << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\tWELCOME TO BATTLESHIP!" << endl << endl;
        cout << "\t\t\t\t\t\t  Let's get started!" << endl << endl;
        cout << "\t\t\t\t\t      Press 'ENTER' to continue!" << endl;
        /* ************************************************************ */
        cin.ignore();
        if (system("CLS")) system("clear");//Clears Screen

        //2nd screen
        /* ***************************************************************************************** */
        cout << endl << endl << endl << endl;
        cout << "\t\t\t\t\t  This game is Player vs Player" << endl << endl;
        cout << "\t\t\t\t        Let's establish Player 1 and Player 2" << endl << endl;
        cout << "\t\t\t\t\t\tLET'S FLIP A COIN!" << endl << endl;
        cout << "\t\t\t\t\tHave someone call 'Heads' or 'Tails'" << endl << endl;
        cout << "\t\t\t    Now, press 'ENTER' to flip a coin! The winner will be Player 1!" << endl;
        /* ****************************************************************************************** */
        cin.ignore();
        CoinFlip();//Calls Coin Flip function which creates a heads/tails output randomly

        //3rd screen which moves on to Player 1 initializing his/her ship locations
        /* ******************************************************************** */
        cout << "\t\t\t\t\t\tPress '1' to begin!" << endl;
        cin >> player1;
            while(player1 != 1)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\t\t\t\t\t Invalid, press '1' to continue" << endl;
                cin >> player1;
            }
        if (system("CLS")) system("clear");
        /* ********************************************************************* */

        do
            {

                    //If statement which clears the screen if Players decided to play again
                    if(GameOver == 'Y' || GameOver == 'y')
                        if (system("CLS")) system("clear");

                    /* ************************************************************************************************************ */
                    //PLAYER 1 CHOOSES SHIP LOCATIONS
                    MenuOutline();//Menu function is called

                    cin >> ship1row >> ship1column;//Ship 1 location for Player 1 is asked from user

                    if(ship1row >= 'a' && ship1row <= 'j')//Lower case letters to Upper Case letters
                                ship1row -= 32;

                    while((ship1row < 'A' || ship1row > 'J') || (ship1column < '0' || ship1column > '9'))//Input Error Check
                        {
                            cin.ignore(10000, '\n');
                            cout << "Invalid coordinate, try again" << endl;
                            cin >> ship1row >> ship1column;
                            if(ship1row >= 'a' && ship1row <= 'j')
                                ship1row -= 32;

                        }

                    if (system("CLS")) system("clear");//Clears screen

                    GameOutlinePlayer1(ship1row, ship1column,
                                ship2_1_row, ship2_1_column, ship2_2_row, ship2_2_column,
                                ship3_1_row,  ship3_1_column , ship3_2_row , ship3_2_column, ship3_3_row, ship3_3_column,
                                ship4_1_row, ship4_1_column, ship4_2_row, ship4_2_column, ship4_3_row, ship4_3_column, ship4_4_row, ship4_4_column);

                    cout << "Now enter 2 adjacent coordiates for Ship 2" << endl;

                    cin >> ship2_1_row >> ship2_1_column >> ship2_2_row >> ship2_2_column;//Ship 2 locations of Player 1 is asked from user

                    if(ship2_1_row >= 'a' && ship2_1_row <= 'j')//Lower case letters to Upper Case letters
                                ship1row -= 32;
                    if(ship2_2_row >= 'a' && ship2_2_row <= 'j')
                                ship1row -= 32;
                    while(   ((ship2_1_row < 'A' || ship2_1_row > 'J') || (ship2_1_column < '0' || ship2_1_column > '9'))//Ship 2 Player 1 input error check
                       ||((ship2_2_row < 'A' || ship2_2_row > 'J') || (ship2_2_column < '0' || ship2_2_column > '9'))   )
                        {
                            cin.ignore(10000, '\n');
                            cout << "Invalid coordinates, try again" << endl;
                            cin >> ship2_1_row >> ship2_1_column >> ship2_2_row >> ship2_2_column ;
                            if(ship2_1_row >= 'a' && ship2_1_row <= 'j')
                                ship2_1_row -= 32;
                            if(ship2_2_row >= 'a' && ship2_2_row <= 'j')
                                ship2_2_row -= 32;
                        }


                    if (system("CLS")) system("clear");//Clears screen

                    GameOutlinePlayer1(ship1row, ship1column,
                                ship2_1_row, ship2_1_column, ship2_2_row, ship2_2_column,
                                ship3_1_row,  ship3_1_column , ship3_2_row , ship3_2_column, ship3_3_row, ship3_3_column,
                                ship4_1_row, ship4_1_column, ship4_2_row, ship4_2_column, ship4_3_row, ship4_3_column, ship4_4_row, ship4_4_column);

                    cout << "Enter 3 adjacent coordinates for Ship 3" << endl;
                    cin >> ship3_1_row >> ship3_1_column >> ship3_2_row >> ship3_2_column >> ship3_3_row >> ship3_3_column;//Ship 3 locations is asked from user

                    if(ship3_1_row >= 'a' && ship3_1_row <= 'j')//Lower case letters to Upper Case letters
                                ship3_1_row -= 32;
                    if(ship3_2_row >= 'a' && ship3_2_row <= 'j')
                                ship3_2_row -= 32;
                    if(ship3_3_row >= 'a' && ship3_3_row <= 'j')
                                ship3_3_row -= 32;

                    while(   ((ship3_1_row < 'A' || ship3_1_row > 'J') || (ship3_1_column < '0' || ship3_1_column > '9'))//Ship 3 Player 1 input error check
                       ||((ship3_2_row < 'A' || ship3_2_row > 'J') || (ship3_2_column < '0' || ship3_2_column > '9'))
                       ||((ship3_3_row < 'A' || ship3_3_row > 'J') || (ship3_3_column < '0' || ship3_3_column > '9'))   )
                        {
                            cin.ignore(10000, '\n');
                            cout << "Invalid coordinates, try again" << endl;
                            cin >> ship3_1_row >> ship3_1_column >> ship3_2_row >> ship3_2_column >> ship3_3_row >> ship3_3_column;
                            if(ship3_1_row >= 'a' && ship3_1_row <= 'j')
                                ship3_1_row -= 32;
                            if(ship3_2_row >= 'a' && ship3_3_row <= 'j')
                                ship3_2_row -= 32;
                            if(ship3_3_row >= 'a' && ship3_3_row <= 'j')
                                ship3_3_row -= 32;
                        }


                    if (system("CLS")) system("clear");//Clears screen

                    GameOutlinePlayer1(ship1row, ship1column,
                                ship2_1_row, ship2_1_column, ship2_2_row, ship2_2_column,
                                ship3_1_row,  ship3_1_column , ship3_2_row , ship3_2_column, ship3_3_row, ship3_3_column,
                                ship4_1_row, ship4_1_column, ship4_2_row, ship4_2_column, ship4_3_row, ship4_3_column, ship4_4_row, ship4_4_column);

                    cout << "Finally, 4 adjacent coordinates for Ship 4" << endl;
                    cin >> ship4_1_row >> ship4_1_column >> ship4_2_row >> ship4_2_column >> ship4_3_row >> ship4_3_column >> ship4_4_row >> ship4_4_column;

                    if(ship4_1_row >= 'a' && ship4_1_row <= 'j')//Lower case to upper case
                                ship4_1_row -= 32;
                    if(ship4_2_row >= 'a' && ship4_2_row <= 'j')
                                ship4_2_row -= 32;
                    if(ship4_3_row >= 'a' && ship4_3_row <= 'j')
                                ship4_3_row -= 32;
                    if(ship4_4_row >= 'a' && ship4_4_row <= 'j')
                                ship4_4_row -= 32;

                    while(   ((ship4_1_row < 'A' || ship4_1_row > 'J') || (ship4_1_column < '0' || ship4_1_column > '9'))//Ship 4 Player 1 input error check
                       ||((ship4_2_row < 'A' || ship4_2_row > 'J') || (ship4_2_column < '0' || ship4_2_column > '9'))
                       ||((ship4_3_row < 'A' || ship4_3_row > 'J') || (ship4_3_column < '0' || ship4_3_column > '9'))
                       ||((ship4_4_row < 'A' || ship4_4_row > 'J') || (ship4_4_column < '0' || ship4_4_column > '9')))
                        {
                            cin.ignore(10000, '\n');
                            cout << "Invalid coordinates, try again" << endl;
                            cin >> ship4_1_row >> ship4_1_column >> ship4_2_row >> ship4_2_column >> ship4_3_row >> ship4_3_column >> ship4_4_row >> ship4_4_column;
                            if(ship4_1_row >= 'a' && ship4_1_row <= 'j')
                                ship4_1_row -= 32;
                            if(ship4_2_row >= 'a' && ship4_2_row <= 'j')
                                ship4_2_row -= 32;
                            if(ship4_3_row >= 'a' && ship4_3_row <= 'j')
                                ship4_3_row -= 32;
                            if(ship4_4_row >= 'a' && ship4_4_row <= 'j')
                                ship4_4_row -= 32;
                        }


                    if (system("CLS")) system("clear");//Clears Screen
                    GameOutlinePlayer1(ship1row, ship1column
                         ,ship2_1_row, ship2_1_column, ship2_2_row, ship2_2_column,
                        ship3_1_row,  ship3_1_column , ship3_2_row , ship3_2_column, ship3_3_row, ship3_3_column,
                        ship4_1_row, ship4_1_column, ship4_2_row, ship4_2_column, ship4_3_row, ship4_3_column, ship4_4_row, ship4_4_column);

                    if (system("CLS")) system("clear");//Clears Screen
                    Limbo();

                    if (system("CLS")) system("clear");//Clears Screen

                    /* ********************************************************************************************************************** */
                    //PLAYER 2 CHOOSES SHIP LOCATIONS

                    MenuOutline();

                    cin >> ship1row_2 >> ship1column_2;//Ship 1 location asked from user

                    if(ship1row_2 >= 'a' && ship1row_2 <= 'j')//Lower case letters to Upper Case letters
                                ship1row_2 -= 32;

                    while((ship1row_2 < 'A' || ship1row_2 > 'J') || (ship1column_2 < '0' || ship1column_2 > '9'))//Input Error Check
                        {
                            cin.ignore(10000, '\n');
                            cout << "Invalid coordinate, try again" << endl;
                            cin >> ship1row_2 >> ship1column_2;
                            if(ship1row_2 >= 'a' && ship1row_2 <= 'j')
                                ship1row_2 -= 32;

                        }

                    if (system("CLS")) system("clear");
                    GameOutlinePlayer2(ship1row_2, ship1column_2,
                                ship2_1_row_2, ship2_1_column_2, ship2_2_row_2, ship2_2_column_2,
                                ship3_1_row_2,  ship3_1_column_2 , ship3_2_row_2 , ship3_2_column_2, ship3_3_row_2, ship3_3_column_2,
                                ship4_1_row_2, ship4_1_column_2, ship4_2_row_2, ship4_2_column_2, ship4_3_row_2, ship4_3_column_2, ship4_4_row_2, ship4_4_column_2);
                    cout << "Now enter 2 adjacent coordiates for Ship 2" << endl;
                    cin >> ship2_1_row_2 >> ship2_1_column_2 >> ship2_2_row_2 >> ship2_2_column_2;


                    if(ship2_1_row_2 >= 'a' && ship2_1_row_2 <= 'j')//Lower case letters to Upper Case letters
                                ship2_1_row_2 -= 32;
                    if(ship2_2_row_2 >= 'a' && ship2_2_row_2 <= 'j')
                                ship2_2_row_2 -= 32;
                    while(   ((ship2_1_row_2 < 'A' || ship2_1_row_2 > 'J') || (ship2_1_column_2 < '0' || ship2_1_column_2 > '9'))//Ship 2 Player 1 input error check
                       ||((ship2_2_row_2 < 'A' || ship2_2_row_2 > 'J') || (ship2_2_column_2 < '0' || ship2_2_column_2 > '9'))   )
                        {
                            cin.ignore(10000, '\n');
                            cout << "Invalid coordinates, try again" << endl;
                            cin >> ship2_1_row_2 >> ship2_1_column_2 >> ship2_2_row_2 >> ship2_2_column_2 ;
                            if(ship2_1_row_2 >= 'a' && ship2_1_row_2 <= 'j')
                                ship2_1_row_2 -= 32;
                            if(ship2_2_row_2 >= 'a' && ship2_2_row_2 <= 'j')
                                ship2_2_row_2 -= 32;


                        }


                    if (system("CLS")) system("clear");
                    GameOutlinePlayer2(ship1row_2, ship1column_2,
                                ship2_1_row_2, ship2_1_column_2, ship2_2_row_2, ship2_2_column_2,
                                ship3_1_row_2,  ship3_1_column_2 , ship3_2_row_2 , ship3_2_column_2, ship3_3_row_2, ship3_3_column_2,
                                ship4_1_row_2, ship4_1_column_2, ship4_2_row_2, ship4_2_column_2, ship4_3_row_2, ship4_3_column_2, ship4_4_row_2, ship4_4_column_2);

                    cout << "Enter 3 adjacent coordinates for Ship 3" << endl;
                    cin >> ship3_1_row_2 >> ship3_1_column_2 >> ship3_2_row_2 >> ship3_2_column_2 >> ship3_3_row_2 >> ship3_3_column_2;

                    if(ship3_1_row_2 >= 'a' && ship3_1_row_2 <= 'j')//Lower case letters to Upper Case letters
                                ship3_1_row_2 -= 32;
                    if(ship3_2_row_2 >= 'a' && ship3_2_row_2 <= 'j')
                                ship3_2_row_2 -= 32;
                    if(ship3_3_row_2 >= 'a' && ship3_3_row_2 <= 'j')
                                ship3_3_row_2 -= 32;

                    while(   ((ship3_1_row_2 < 'A' || ship3_1_row_2 > 'J') || (ship3_1_column_2 < '0' || ship3_1_column_2 > '9'))//Ship 2 Player 1 input error check
                       ||((ship3_2_row_2 < 'A' || ship3_2_row_2 > 'J') || (ship3_2_column_2 < '0' || ship3_2_column_2 > '9'))
                       ||((ship3_3_row_2 < 'A' || ship3_3_row_2 > 'J') || (ship3_3_column_2 < '0' || ship3_3_column_2 > '9'))   )
                        {
                            cin.ignore(10000, '\n');
                            cout << "Invalid coordinates, try again" << endl;
                            cin >> ship3_1_row_2 >> ship3_1_column_2 >> ship3_2_row_2 >> ship3_2_column_2 >> ship3_3_row_2 >> ship3_3_column_2;

                            if(ship3_1_row_2 >= 'a' && ship3_1_row_2 <= 'j')//Lowesr case to upper case
                                ship2_1_row_2 -= 32;
                            if(ship3_2_row_2 >= 'a' && ship3_2_row_2 <= 'j')
                                ship2_2_row_2 -= 32;
                            if(ship3_2_row_2 >= 'a' && ship3_3_row_2 <= 'j')
                                ship2_2_row_2 -= 32;


                        }



                    if (system("CLS")) system("clear");
                    GameOutlinePlayer2(ship1row_2, ship1column_2,
                                ship2_1_row_2, ship2_2_column_2, ship2_2_row_2, ship2_2_column_2,
                                ship3_1_row_2,  ship3_1_column_2 , ship3_2_row_2 , ship3_2_column_2, ship3_3_row_2, ship3_3_column_2,
                                ship4_1_row_2, ship4_1_column_2, ship4_2_row_2, ship4_2_column_2, ship4_3_row_2, ship4_3_column_2, ship4_4_row_2, ship4_4_column_2);

                    cout << "Finally, 4 adjacent coordinates for Ship 4" << endl;
                    cin >> ship4_1_row_2 >> ship4_1_column_2 >> ship4_2_row_2 >> ship4_2_column_2 >> ship4_3_row_2 >> ship4_3_column_2 >> ship4_4_row_2 >> ship4_4_column_2;


                    if(ship4_1_row_2 >= 'a' && ship4_1_row_2 <= 'j')//Lower case letters to Upper Case letters
                                ship4_1_row_2 -= 32;
                    if(ship4_2_row_2 >= 'a' && ship4_2_row_2 <= 'j')
                                ship4_2_row_2 -= 32;
                    if(ship4_3_row_2 >= 'a' && ship4_3_row_2 <= 'j')
                                ship4_3_row_2 -= 32;
                    if(ship4_4_row_2 >= 'a' && ship4_4_row_2 <= 'j')
                                ship4_4_row_2 -= 32;

                    while(   ((ship4_1_row_2 < 'A' || ship4_1_row_2 > 'J') || (ship4_1_column_2 < '0' || ship4_1_column_2 > '9'))//Ship 2 Player 1 input error check
                       ||((ship4_2_row_2 < 'A' || ship4_2_row_2 > 'J') || (ship4_2_column_2 < '0' || ship4_2_column_2 > '9'))
                       ||((ship4_3_row_2 < 'A' || ship4_3_row_2 > 'J') || (ship4_3_column_2 < '0' || ship4_3_column_2 > '9'))
                       ||((ship4_4_row_2 < 'A' || ship4_4_row_2 > 'J') || (ship4_4_column_2 < '0' || ship4_4_column_2 > '9')))
                        {

                            cin.ignore(10000, '\n');
                            cout << "Invalid coordinates, try again" << endl;
                            cin >> ship4_1_row_2 >> ship4_1_column_2 >> ship4_2_row_2 >> ship4_2_column_2 >> ship4_3_row_2 >> ship4_3_column_2 >> ship4_4_row >> ship4_4_column;

                            if(ship4_1_row_2 >= 'a' && ship4_1_row_2 <= 'j')//Lowesr case to upper case
                                ship4_1_row_2 -= 32;
                            if(ship4_2_row_2 >= 'a' && ship4_2_row_2 <= 'j')
                                ship4_2_row_2 -= 32;
                            if(ship4_3_row_2 >= 'a' && ship4_3_row_2 <= 'j')
                                ship4_3_row_2 -= 32;
                            if(ship4_4_row_2 >= 'a' && ship4_4_row_2 <= 'j')
                                ship4_4_row_2 -= 32;


                        }



                    if (system("CLS")) system("clear");
                    GameOutlinePlayer2(ship1row_2, ship1column_2
                         ,ship2_1_row_2, ship2_1_column_2, ship2_2_row_2, ship2_2_column_2,
                        ship3_1_row_2,  ship3_1_column_2 , ship3_2_row_2 , ship3_2_column_2, ship3_3_row_2, ship3_3_column_2,
                        ship4_1_row_2, ship4_1_column_2, ship4_2_row_2, ship4_2_column_2, ship4_3_row_2, ship4_3_column_2, ship4_4_row_2, ship4_4_column_2);

                    if (system("CLS")) system("clear");
                    Limbo();
                    if (system("CLS")) system("clear");

                    while(GameOver == '0')
                    {

                        if(TURN % 2 == 0)
                        {
                            GameOutlinePlayer1(ship1row, ship1column,
                            ship2_1_row, ship2_1_column, ship2_2_row, ship2_2_column,
                            ship3_1_row,  ship3_1_column , ship3_2_row , ship3_2_column, ship3_3_row, ship3_3_column,
                            ship4_1_row, ship4_1_column, ship4_2_row, ship4_2_column, ship4_3_row, ship4_3_column, ship4_4_row, ship4_4_column);
                            victory = Victory();
                                if(victory == true)
                                {
                                    if (system("CLS")) system("clear");
                                    cout << endl << endl << endl;
                                    cout << "\t\t\t\t\t\t\tPLAYER 1 WINS!" << endl;
                                    cout << "\t\t\t\t\t\t\tPlay again Y/N?" << endl;
                                    cin >> GameOver;

                                }
                                else
                                    Limbo();
                        }
                        else
                        {
                            GameOutlinePlayer2(ship1row_2, ship1column_2,
                            ship2_1_row_2, ship2_1_column_2, ship2_2_row_2, ship2_2_column_2,
                            ship3_1_row_2,  ship3_1_column_2 , ship3_2_row_2 , ship3_2_column_2, ship3_3_row_2, ship3_3_column_2,
                            ship4_1_row_2, ship4_1_column_2, ship4_2_row_2, ship4_2_column_2, ship4_3_row_2, ship4_3_column_2, ship4_4_row_2, ship4_4_column_2);
                            victory = Victory();
                                if(victory == true)
                                {
                                    if (system("CLS")) system("clear");
                                    cout << endl << endl << endl;
                                    cout << "\t\t\t\t\t\t\tPLAYER 2 WINS!" << endl;
                                    cout << "\t\t\t\t\t\t\tPlay again Y/N?" << endl;
                                    cin >> GameOver;
                                }
                                else
                                    Limbo();
                        }

                        TURN++;

                    }

            } while(GameOver == 'y' || GameOver == 'Y');


            return 0;

    }

    void battleSpaces()
{
    for(int r = 0; r < 10; r++)
    {
        for(int c = 0; c < 10; c++)
        {
            POOP1[r][c] = ' ';
        }
    }
    for(int r = 0; r < 10; r++)
    {
        for(int c = 0; c < 10; c++)
        {
            POOP2[r][c] = ' ';
        }
    }
    for(int r = 0; r < 10; r++)
    {
        for(int c = 0; c < 10; c++)
        {
            POOP_Empty[r][c] = ' ';
        }
    }
    for(int r = 0; r < 10; r++)
    {
        for(int c = 0; c < 10; c++)
        {
            POOP_Empty2[r][c] = ' ';
        }
    }

}

//Creates a board for Player 1 to visualize their hits/misses on Player 2
void EmptyBoard()
    {
            cout << "\t\t\t\t\t\t\t\tPlayer 1" << endl;
            for(int r = 0; r < 10; r++)
            {
                if(r == 0)
                    cout << "   0   1   2   3   4   5   6   7   8   9 " << endl;

                cout << " -----------------------------------------"<< endl;
                for(int c = 0; c < 10; c++)
                    {
                            cout << " | " << POOP_Empty[r][c];
                            if(c == 9 && r == 0)
                                cout << " |   A";
                            else if(c == 9 && r == 1)
                                cout << " |   B";
                            else if(c == 9 && r == 2)
                                cout << " |   C";
                            else if(c == 9 && r == 3)
                                cout << " |   D";
                            else if(c == 9 && r == 4)
                                cout << " |   E";
                            else if(c == 9 && r == 5)
                                cout << " |   F";
                            else if(c == 9 && r == 6)
                                cout << " |   G";
                            else if(c == 9 && r == 7)
                                cout << " |   H";
                            else if(c == 9 && r == 8)
                                cout << " |   I";
                            else if(c == 9 && r == 9)
                                cout << " |   J";
                    }
                cout << endl;
                if(r == 9)
                cout << " -----------------------------------------" << endl;
            }

    }

//Creates an empty board for PLayer 2 to visualize their hits and misses on Player 1
void EmptyBoard2()
    {
            cout << "\t\t\t\t\t\t\t\t\tPlayer 2" << endl;
            for(int r = 0; r < 10; r++)
            {
                if(r == 0)
                    cout << "   0   1   2   3   4   5   6   7   8   9 " << endl;

                cout << " -----------------------------------------"<< endl;
                for(int c = 0; c < 10; c++)
                    {
                            cout << " | " << POOP_Empty2[r][c];
                            if(c == 9 && r == 0)
                                cout << " |   A";
                            else if(c == 9 && r == 1)
                                cout << " |   B";
                            else if(c == 9 && r == 2)
                                cout << " |   C";
                            else if(c == 9 && r == 3)
                                cout << " |   D";
                            else if(c == 9 && r == 4)
                                cout << " |   E";
                            else if(c == 9 && r == 5)
                                cout << " |   F";
                            else if(c == 9 && r == 6)
                                cout << " |   G";
                            else if(c == 9 && r == 7)
                                cout << " |   H";
                            else if(c == 9 && r == 8)
                                cout << " |   I";
                            else if(c == 9 && r == 9)
                                cout << " |   J";
                    }
                cout << endl;
                if(r == 9)
                cout << " -----------------------------------------" << endl;
            }

    }

//Creates a coin flip to determine Player 1 (plays 1st) and Player 2 (plays 2nd)
void CoinFlip()
    {
            srand(time(0));
            int flip;
            flip =  rand() % 2 + 1;// assign random numbers
				if (flip == 1)
                {
                    if (system("CLS")) system("clear");
                    cout << endl << endl << endl << endl << endl;
                    cout << "\t\t\t\t\t\t   IT'S HEADS!" << endl << endl;
                    cout << "\t\t\t\t    Now, let's let Player 1 stay at the computer" << endl << endl;
                    cout << "\t\t\tWe don't want Player 2 seeing where Player 1 will establish their ships!" << endl << endl;
                }
                else
                {
                    if (system("CLS")) system("clear");
                    cout << endl << endl << endl << endl << endl;
                    cout << "\t\t\t\t\t\t   IT'S TAILS!" << endl << endl;
                    cout << "\t\t\t\t    Now, let's let Player 1 stay at the computer" << endl << endl;
                    cout << "\t\t\tWe don't want Player 2 seeing where Player 1 will establish their ships!" << endl << endl;
                }
        }

//Creates initial screen for Player 1/Player 2 which displays instructions and and empty board with coordinates
void MenuOutline()
    {
        static int Turn = 2;
        if(Turn % 2 == 0)
            cout << "\t\t\t\t\t\t\tPlayer 1" << endl;
        else
            cout << "\t\t\t\t\t\t\tPlayer 2" << endl;
        Turn++;


        for(int r = 0; r < 10; r++)
            {
                if(r == 0)
                    cout << "   0   1   2   3   4   5   6   7   8   9 " << endl;

                cout << " -----------------------------------------"<< endl;
                for(int c = 0; c < 10; c++)
                    {
                            cout << " | " << " ";
                            if(c == 9 && r == 0)
                                cout << " |   A\t\tHelp:";
                            else if(c == 9 && r == 1)
                                cout << " |   B\t\tYou are granted 4 ships, place them wisely!";
                            else if(c == 9 && r == 2)
                                cout << " |   C\t\tShip 1 = 1 space, Ship 2 = 2 spaces, etc.";
                            else if(c == 9 && r == 3)
                                cout << " |   D\t\tExamples of coordinates: A4, C8, J1, etc.";
                            else if(c == 9 && r == 4)
                                cout << " |   E\t\tShip 1 = 1 coordinate, Ship 2 = 2 adjacent coordinates, etc.";
                            else if(c == 9 && r == 5)
                                cout << " |   F\t\tShips CANNOT overlap";
                            else if(c == 9 && r == 6)
                                cout << " |   G";
                            else if(c == 9 && r == 7)
                                cout << " |   H";
                            else if(c == 9 && r == 8)
                                cout << " |   I";
                            else if(c == 9 && r == 9)
                                cout << " |   J\t\tStart by entering coordinates for Ship 1";
                    }
                cout << endl;
                if(r == 9)
                cout << " -----------------------------------------" << endl;
            }

    }

//Player 1 attacks Player 2 and checks for hits/misses
bool HitOrMiss1(char attackrow, char attackcolumn)
    {
        static int count = 1;

        int row, column;

        if(attackcolumn == '0') //Converting the Column character in to an integer value.
            column = 0;
        if(attackcolumn == '1')
             column = 1;
        if(attackcolumn == '2')
             column = 2;
        if(attackcolumn == '3')
             column = 3;
        if(attackcolumn == '4')
             column = 4;
        if(attackcolumn == '5')
             column = 5;
        if(attackcolumn == '6')
             column = 6;
        if(attackcolumn == '7')
             column = 7;
        if(attackcolumn == '8')
             column = 8;
        if(attackcolumn == '9')
             column = 9;

        if(attackrow >= 'a' && attackrow <= 'j')//Converting from lower case to uppercase coordinates
            attackrow -= 32;



                                        switch(attackrow)

                                        {
                                                case 'A': row = 0;
                                                    if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;
                                                        POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }
                                                  break;
                                                case 'B': row = 1;
                                                  if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;

                                                        POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;

                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }
                                                  break;
                                                case 'C': row = 2;
                                                  if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                                case 'D': row = 3;
                                                  if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                                case 'E': row = 4;
                                                  if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                                case 'F': row = 5;
                                                  if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                                case 'G': row = 6;
                                                  if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }
                                                  break;
                                                case 'H': row = 7;
                                                  if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                                case 'I': row = 8;
                                                  if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                                case 'J': row = 9;
                                                  if(POOP2[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            a = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            b = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            z = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            d = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            e = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            f = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            g = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            h = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            u = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            v = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP2[row][column] = 'X';
                                                        POOP_Empty[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty[row][column] = 'M';
                                                        return false;
                                                    }
                                                  break;
                                        }//switch end



        return false;
                        }//player 1 end

//Player 2 attacks Player 1 and checks for hits/misses
bool HitOrMiss2(char attackrow, char attackcolumn)
    {
        static int count = 1;

        int row, column;

        if(attackcolumn == '0') //Converting the Column character in to an integer value.
            column = 0;
        if(attackcolumn == '1')
             column = 1;
        if(attackcolumn == '2')
             column = 2;
        if(attackcolumn == '3')
             column = 3;
        if(attackcolumn == '4')
             column = 4;
        if(attackcolumn == '5')
             column = 5;
        if(attackcolumn == '6')
             column = 6;
        if(attackcolumn == '7')
             column = 7;
        if(attackcolumn == '8')
             column = 8;
        if(attackcolumn == '9')
             column = 9;

        if(attackrow >= 'a' && attackrow <= 'j')//Converting from lower case to uppercase coordinates
            attackrow -= 32;



                                        switch(attackrow)
                                            {

                                        case 'A': row = 0;
                                                    if(POOP1[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty2[row][column] = 'M';
                                                        return false;
                                                    }
                                                  break;
                                        case 'B': row = 1;
                                                  if(POOP1[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;

                                                          POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                       POOP_Empty2[row][column] = 'M';
                                                       return false;
                                                    }
                                                  break;
                                        case 'C': row = 2;
                                                  if(POOP1[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;


                                                          POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty2[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                        case 'D': row = 3;
                                                  if(POOP1[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;


                                                          POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty2[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                        case 'E': row = 4;
                                                  if(POOP1[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;


                                                          POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty2[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                        case 'F': row = 5;
                                                  if(POOP1[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;


                                                          POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty2[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                        case 'G': row = 6;
                                                  if(POOP1[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;


                                                          POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        POOP_Empty2[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                        case 'H': row = 7;
                                                  if(POOP1[row][column] =='Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;


                                                          POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;

                                                    }
                                                    else
                                                    {
                                                        POOP_Empty2[row][column] = 'M';
                                                        return false;
                                                    }

                                                  break;
                                        case 'I': row = 8;
                                                  if(POOP1[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;


                                                          POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;
                                                    }
                                                   else
                                                   {
                                                       POOP_Empty2[row][column] = 'M';
                                                        return false;
                                                   }

                                                  break;
                                        case 'J': row = 9;
                                                  if(POOP1[row][column] == 'Z')
                                                    {
                                                        if(count == 1)
                                                        {
                                                            k = true;
                                                            count++;
                                                        }
                                                        else if(count == 2)
                                                        {
                                                            l = true;
                                                            count++;
                                                        }
                                                        else if(count == 3)
                                                        {
                                                            m = true;
                                                            count++;
                                                        }
                                                        else if(count == 4)
                                                        {
                                                            n = true;
                                                            count++;
                                                        }
                                                        else if(count == 5)
                                                        {
                                                            o = true;
                                                            count++;
                                                        }
                                                        else if(count == 6)
                                                        {
                                                            w = true;
                                                            count++;
                                                        }
                                                        else if(count == 7)
                                                        {
                                                            x = true;
                                                            count++;
                                                        }
                                                        else if(count == 8)
                                                        {
                                                            y = true;
                                                            count++;
                                                        }
                                                        else if(count == 9)
                                                        {
                                                            s = true;
                                                            count++;
                                                        }
                                                        else if(count == 10)
                                                        {
                                                            t = true;
                                                            count++;
                                                        }
                                                        else;


                                                        POOP1[row][column] = 'X';
                                                        POOP_Empty2[row][column] = 'X';
                                                        return true;

                                                    }
                                                    else
                                                    {
                                                        POOP_Empty2[row][column] = 'M';
                                                        return false;
                                                    }
                                                  break;
                                        }


            return false;

                        }


//Function which establishes Player 1's ship locations
void GameOutlinePlayer1(char ship1row1, char ship1column1, char ship2row1, char ship2column1, char ship2row2, char ship2column2, char ship3row1, char ship3column1, char ship3row2, char ship3column2, char ship3row3, char ship3column3,
                       char ship4row1, char ship4column1, char ship4row2, char ship4column2, char ship4row3, char ship4column3, char ship4row4, char ship4column4)
    {
        static int count = 1;
        count++;

        bool ATTACK = false;

        char attackrow, attackcolumn;

        int column, row;
        int column21, row21;
        int column22, row22;
        int column31, row31;
        int column32, row32;
        int column33, row33;
        int column41, row41;
        int column42, row42;
        int column43, row43;
        int column44, row44;

        if(ship1column1 == '0') //SHIP 1 COLUMN
             column = 0;
        if(ship1column1 == '1')
             column = 1;
        if(ship1column1 == '2')
             column = 2;
        if(ship1column1 == '3')
             column = 3;
        if(ship1column1 == '4')
             column = 4;
        if(ship1column1 == '5')
             column = 5;
        if(ship1column1 == '6')
             column = 6;
        if(ship1column1 == '7')
             column = 7;
        if(ship1column1 == '8')
             column = 8;
        if(ship1column1 == '9')
             column = 9;

        if(ship2column1 == '0') //SHIP 2 COLUMN 1
             column21 = 0;
        if(ship2column1 == '1')
             column21 = 1;
        if(ship2column1 == '2')
             column21 = 2;
        if(ship2column1 == '3')
             column21 = 3;
        if(ship2column1 == '4')
             column21 = 4;
        if(ship2column1 == '5')
             column21 = 5;
        if(ship2column1 == '6')
             column21 = 6;
        if(ship2column1 == '7')
             column21 = 7;
        if(ship2column1 == '8')
             column21 = 8;
        if(ship2column1 == '9')
             column21 = 9;

        if(ship2column2 == '0') //SHIP 2 COLUMN 2
             column22 = 0;
        if(ship2column2 == '1')
             column22 = 1;
        if(ship2column2 == '2')
             column22 = 2;
        if(ship2column2 == '3')
             column22 = 3;
        if(ship2column2 == '4')
             column22 = 4;
        if(ship2column2 == '5')
             column22 = 5;
        if(ship2column2 == '6')
             column22 = 6;
        if(ship2column2 == '7')
             column22 = 7;
        if(ship2column2 == '8')
             column22 = 8;
        if(ship2column2 == '9')
             column22 = 9;

        if(ship3column1 == '0') //SHIP 3 COLUMN 1
             column31 = 0;
        if(ship3column1 == '1')
             column31 = 1;
        if(ship3column1 == '2')
             column31 = 2;
        if(ship3column1 == '3')
             column31 = 3;
        if(ship3column1 == '4')
             column31 = 4;
        if(ship3column1 == '5')
             column31 = 5;
        if(ship3column1 == '6')
             column31 = 6;
        if(ship3column1 == '7')
             column31 = 7;
        if(ship3column1 == '8')
             column31 = 8;
        if(ship3column1 == '9')
             column31 = 9;

        if(ship3column2 == '0') //SHIP 3 COLUMN 2
             column32 = 0;
        if(ship3column2 == '1')
             column32 = 1;
        if(ship3column2 == '2')
             column32 = 2;
        if(ship3column2 == '3')
             column32 = 3;
        if(ship3column2 == '4')
             column32 = 4;
        if(ship3column2 == '5')
             column32 = 5;
        if(ship3column2 == '6')
             column32 = 6;
        if(ship3column2 == '7')
             column32 = 7;
        if(ship3column2 == '8')
             column32 = 8;
        if(ship3column2 == '9')
             column32 = 9;

        if(ship3column3 == '0') //SHIP 3 COLUMN 3
             column33 = 0;
        if(ship3column3 == '1')
             column33 = 1;
        if(ship3column3 == '2')
             column33 = 2;
        if(ship3column3 == '3')
             column33 = 3;
        if(ship3column3 == '4')
             column33 = 4;
        if(ship3column3 == '5')
             column33 = 5;
        if(ship3column3 == '6')
             column33 = 6;
        if(ship3column3 == '7')
             column33 = 7;
        if(ship3column3 == '8')
             column33 = 8;
        if(ship3column3 == '9')
             column33 = 9;

        if(ship4column1 == '0') //SHIP 4 COLUMN 1
             column41 = 0;
        if(ship4column1 == '1')
             column41 = 1;
        if(ship4column1 == '2')
             column41 = 2;
        if(ship4column1 == '3')
             column41 = 3;
        if(ship4column1 == '4')
             column41 = 4;
        if(ship4column1 == '5')
             column41 = 5;
        if(ship4column1 == '6')
             column41 = 6;
        if(ship4column1 == '7')
             column41 = 7;
        if(ship4column1 == '8')
             column41 = 8;
        if(ship4column1 == '9')
             column41 = 9;

        if(ship4column2 == '0') //SHIP 4 COLUMN 2
             column42 = 0;
        if(ship4column2 == '1')
             column42 = 1;
        if(ship4column2 == '2')
             column42 = 2;
        if(ship4column2 == '3')
             column42 = 3;
        if(ship4column2 == '4')
             column42 = 4;
        if(ship4column2 == '5')
             column42 = 5;
        if(ship4column2 == '6')
             column42 = 6;
        if(ship4column2 == '7')
             column42 = 7;
        if(ship4column2 == '8')
             column42 = 8;
        if(ship4column2 == '9')
             column42 = 9;

        if(ship4column3 == '0') //SHIP 4 COLUMN 4
             column43 = 0;
        if(ship4column3 == '1')
             column43 = 1;
        if(ship4column3 == '2')
             column43 = 2;
        if(ship4column3 == '3')
             column43 = 3;
        if(ship4column3 == '4')
             column43 = 4;
        if(ship4column3 == '5')
             column43 = 5;
        if(ship4column3 == '6')
             column43 = 6;
        if(ship4column3 == '7')
             column43 = 7;
        if(ship4column3 == '8')
             column43 = 8;
        if(ship4column3 == '9')
             column43 = 9;

        if(ship4column4 == '0') //SHIP 4 COLUMN 4
             column44 = 0;
        if(ship4column4 == '1')
             column44 = 1;
        if(ship4column4 == '2')
             column44 = 2;
        if(ship4column4 == '3')
             column44 = 3;
        if(ship4column4 == '4')
             column44 = 4;
        if(ship4column4 == '5')
             column44 = 5;
        if(ship4column4 == '6')
             column44 = 6;
        if(ship4column4 == '7')
             column44 = 7;
        if(ship4column4 == '8')
             column44 = 8;
        if(ship4column4 == '9')
             column44 = 9;


        for(int r = 0; r < 10; r++)
            {
                if(r == 0)
                    cout << "   0   1   2   3   4   5   6   7   8   9 " << endl;

                cout << " -----------------------------------------"<< endl;
                for(int c = 0; c < 10; c++)
                    {

                                        switch(ship1row1)
                                        {

                                        case 'A': row = 0;
                                                  POOP1[row][column] = 'Z';
                                                  break;
                                        case 'B': row = 1;
                                                  POOP1[row][column] = 'Z';
                                                  break;
                                        case 'C': row = 2;
                                                  POOP1[row][column] = 'Z';

                                                  break;
                                        case 'D': row = 3;
                                                  POOP1[row][column] = 'Z';

                                                  break;
                                        case 'E': row = 4;
                                                  POOP1[row][column] = 'Z';

                                                  break;
                                        case 'F': row = 5;
                                                  POOP1[row][column] = 'Z';

                                                  break;
                                        case 'G': row = 6;
                                                  POOP1[row][column] = 'Z';

                                                  break;
                                        case 'H': row = 7;
                                                  POOP1[row][column] = 'Z';

                                                  break;
                                        case 'I': row = 8;
                                                  POOP1[row][column] = 'Z';

                                                  break;
                                        case 'J': row = 9;
                                                  POOP1[row][column] = 'Z';
                                                  break;
                                        }




                                        switch(ship2row1)
                                        {

                                        case 'A': row21 = 0;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        case 'B': row21 = 1;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        case 'C': row21 = 2;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        case 'D': row21 = 3;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        case 'E': row21 = 4;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        case 'F': row21 = 5;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        case 'G': row21 = 6;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        case 'H': row21 = 7;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        case 'I': row21 = 8;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        case 'J': row21 = 9;
                                                  POOP1[row21][column21] = 'Z';

                                                  break;
                                        }


                                        switch(ship2row2)
                                        {

                                        case 'A': row22 = 0;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        case 'B': row22 = 1;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        case 'C': row22 = 2;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        case 'D': row22 = 3;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        case 'E': row22 = 4;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        case 'F': row22 = 5;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        case 'G': row22 = 6;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        case 'H': row22 = 7;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        case 'I': row22 = 8;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        case 'J': row22 = 9;
                                                  POOP1[row22][column22] = 'Z';

                                                  break;
                                        }

                                        switch(ship3row1)
                                        {

                                        case 'A': row31 = 0;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        case 'B': row31 = 1;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        case 'C': row31 = 2;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        case 'D': row31 = 3;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        case 'E': row31 = 4;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        case 'F': row31 = 5;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        case 'G': row31 = 6;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        case 'H': row31 = 7;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        case 'I': row31 = 8;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        case 'J': row31 = 9;
                                                  POOP1[row31][column31] = 'Z';

                                                  break;
                                        }


                                        switch(ship3row2)
                                        {

                                        case 'A': row32 = 0;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        case 'B': row32 = 1;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        case 'C': row32 = 2;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        case 'D': row32 = 3;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        case 'E': row32 = 4;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        case 'F': row32 = 5;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        case 'G': row32 = 6;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        case 'H': row32 = 7;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        case 'I': row32 = 8;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        case 'J': row32 = 9;
                                                  POOP1[row32][column32] = 'Z';

                                                  break;
                                        }

                                        switch(ship3row3)
                                        {

                                        case 'A': row33 = 0;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        case 'B': row33 = 1;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        case 'C': row33 = 2;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        case 'D': row33 = 3;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        case 'E': row33 = 4;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        case 'F': row33 = 5;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        case 'G': row33 = 6;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        case 'H': row33 = 7;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        case 'I': row33 = 8;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        case 'J': row33 = 9;
                                                  POOP1[row33][column33] = 'Z';

                                                  break;
                                        }

                                        switch(ship4row1)
                                        {

                                        case 'A': row41 = 0;
                                                  POOP1[row41][column41] = 'Z';
                                                  break;

                                        case 'B': row41 = 1;
                                                  POOP1[row41][column41] = 'Z';

                                                  break;
                                        case 'C': row41 = 2;
                                                  POOP1[row41][column41] = 'Z';

                                                  break;
                                        case 'D': row41 = 3;
                                                  POOP1[row41][column41] = 'Z';

                                                  break;
                                        case 'E': row41 = 4;
                                                  POOP1[row41][column41] = 'Z';

                                                  break;
                                        case 'F': row41 = 5;
                                                  POOP1[row41][column41] = 'Z';

                                                  break;
                                        case 'G': row41 = 6;
                                                  POOP1[row41][column41] = 'Z';

                                                  break;
                                        case 'H': row41 = 7;
                                                  POOP1[row41][column41] = 'Z';
                                                  break;
                                        case 'I': row41 = 8;
                                                  POOP1[row41][column41] = 'Z';

                                                  break;
                                        case 'J': row41 = 9;
                                                  POOP1[row41][column41] = 'Z';

                                                  break;
                                        }

                                        switch(ship4row2)
                                        {

                                        case 'A': row42 = 0;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        case 'B': row42 = 1;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        case 'C': row42 = 2;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        case 'D': row42 = 3;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        case 'E': row42 = 4;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        case 'F': row42 = 5;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        case 'G': row42 = 6;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        case 'H': row42 = 7;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        case 'I': row42 = 8;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        case 'J': row42 = 9;
                                                  POOP1[row42][column42] = 'Z';

                                                  break;
                                        }

                                        switch(ship4row3)
                                        {

                                        case 'A': row43 = 0;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        case 'B': row43 = 1;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        case 'C': row43 = 2;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        case 'D': row43 = 3;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        case 'E': row43 = 4;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        case 'F': row43 = 5;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        case 'G': row43 = 6;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        case 'H': row43 = 7;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        case 'I': row43 = 8;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        case 'J': row43 = 9;
                                                  POOP1[row43][column43] = 'Z';

                                                  break;
                                        }

                                        switch(ship4row4)
                                        {

                                        case 'A': row44 = 0;
                                                  POOP1[row44][column44] = 'Z';

                                                  break;
                                        case 'B': row44 = 1;
                                                  POOP1[row44][column44] = 'Z';

                                                  break;
                                        case 'C': row44 = 2;
                                                  POOP1[row44][column44] = 'Z';

                                                  break;
                                        case 'D': row44 = 3;
                                                  POOP1[row44][column44] = 'Z';

                                                  break;
                                        case 'E': row44 = 4;
                                                  POOP1[row44][column44] = 'Z';

                                                  break;
                                        case 'F': row44 = 5;
                                                  POOP1[row44][column44] = 'Z';

                                                  break;
                                        case 'G': row44 = 6;
                                                  POOP1[row44][column44] = 'Z';

                                                  break;
                                        case 'H': row44 = 7;
                                                  POOP1[row44][column44] = 'Z';

                                                  break;
                                        case 'I': row44 = 8;
                                                  POOP1[row44][column44] = 'Z';

                                                  break;
                                        case 'J': row44 = 9;
                                                  POOP1[row44][column44] = 'Z';
                                                  break;

                                        }


                            cout << " | " << POOP1[r][c];
                            if(c == 9 && r == 0)
                                cout << " |   A";
                            else if(c == 9 && r == 1)
                                cout << " |   B";
                            else if(c == 9 && r == 2)
                                cout << " |   C";
                            else if(c == 9 && r == 3)
                                cout << " |   D";
                            else if(c == 9 && r == 4)
                                cout << " |   E";
                            else if(c == 9 && r == 5)
                                cout << " |   F";
                            else if(c == 9 && r == 6)
                                cout << " |   G";
                            else if(c == 9 && r == 7)
                                cout << " |   H";
                            else if(c == 9 && r == 8)
                                cout << " |   I";
                            else if(c == 9 && r == 9)
                                cout << " |   J";
                    }

                cout << endl;
                if(r == 9)
                cout << " -----------------------------------------" << endl;
            }

            if(count == 6)
            {
                cout << endl << endl;
                cout << "Now, here are your ships!" << endl;
                cout << "Plus an empty board to begin placing your missles!" << endl;
                cout << "Please enter a coordinate where you would like your first missle strike!" << endl << endl;

               EmptyBoard();
               cout << endl;

               cin >> attackrow >> attackcolumn;

               if(attackrow >= 'a' && attackrow <= 'j')
                    attackrow -= 32;
               while((attackrow < 'A' || attackrow > 'J') || (attackcolumn < '0' || attackcolumn > '9'))
               {
                    cin.ignore(10000,'\n');
                    cin >> attackrow >> attackcolumn;
                    cout << "Invalid input! Try again" << endl;
                    if(attackrow >= 'a' && attackrow <= 'j')
                    attackrow -= 32;
               }

               ATTACK = HitOrMiss1(attackrow, attackcolumn);
                    if(ATTACK == true)
                    {
                        cout << "HIT!!" << endl;
                        cin.ignore();
                        cin.get();
                        if (system("CLS")) system("clear");
                    }
                    else
                    {
                        cout << "MISS!" << endl;
                        cin.ignore();
                        cin.get();
                        if (system("CLS")) system("clear");
                    }
            }
            else if(count > 6)
            {
                cout << endl << endl;
                EmptyBoard();
                cout << endl;

               cin >> attackrow >> attackcolumn;

               if(attackrow >= 'a' && attackrow <= 'j')
                    attackrow -= 32;
               while((attackrow < 'A' || attackrow > 'J') || (attackcolumn < '0' || attackcolumn > '9'))
               {
                    cin.ignore(10000,'\n');
                    cin >> attackrow >> attackcolumn;
                    cout << "Invalid input! Try again" << endl;
                    if(attackrow >= 'a' && attackrow <= 'j')
                    attackrow -= 32;
               }
               ATTACK = HitOrMiss1(attackrow, attackcolumn);
                    if(ATTACK == true)
                    {
                        cout << "HIT!!" << endl;
                        cin.ignore();
                        cin.get();
                        if (system("CLS")) system("clear");
                    }
                    else
                    {
                        cout << "MISS!" << endl;
                        cin.ignore();
                        cin.get();
                        if (system("CLS")) system("clear");
                    }
            }
            else;
    }



//Function which establishes Player 2's ship locations
void GameOutlinePlayer2(char ship1row1, char ship1column1, char ship2row1, char ship2column1, char ship2row2, char ship2column2, char ship3row1, char ship3column1, char ship3row2, char ship3column2, char ship3row3, char ship3column3,
                       char ship4row1, char ship4column1, char ship4row2, char ship4column2, char ship4row3, char ship4column3, char ship4row4, char ship4column4)
    {
        bool ATTACK = false;
        char attackrow, attackcolumn;

        static int count = 1;
        count ++;

        int column, row;
        int column21, row21;
        int column22, row22;
        int column31, row31;
        int column32, row32;
        int column33, row33;
        int column41, row41;
        int column42, row42;
        int column43, row43;
        int column44, row44;

        if(ship1column1 == '0') //SHIP 1 COLUMN
             column = 0;
        if(ship1column1 == '1')
             column = 1;
        if(ship1column1 == '2')
             column = 2;
        if(ship1column1 == '3')
             column = 3;
        if(ship1column1 == '4')
             column = 4;
        if(ship1column1 == '5')
             column = 5;
        if(ship1column1 == '6')
             column = 6;
        if(ship1column1 == '7')
             column = 7;
        if(ship1column1 == '8')
             column = 8;
        if(ship1column1 == '9')
             column = 9;

        if(ship2column1 == '0') //SHIP 2 COLUMN 1
             column21 = 0;
        if(ship2column1 == '1')
             column21 = 1;
        if(ship2column1 == '2')
             column21 = 2;
        if(ship2column1 == '3')
             column21 = 3;
        if(ship2column1 == '4')
             column21 = 4;
        if(ship2column1 == '5')
             column21 = 5;
        if(ship2column1 == '6')
             column21 = 6;
        if(ship2column1 == '7')
             column21 = 7;
        if(ship2column1 == '8')
             column21 = 8;
        if(ship2column1 == '9')
             column21 = 9;

        if(ship2column2 == '0') //SHIP 2 COLUMN 2
             column22 = 0;
        if(ship2column2 == '1')
             column22 = 1;
        if(ship2column2 == '2')
             column22 = 2;
        if(ship2column2 == '3')
             column22 = 3;
        if(ship2column2 == '4')
             column22 = 4;
        if(ship2column2 == '5')
             column22 = 5;
        if(ship2column2 == '6')
             column22 = 6;
        if(ship2column2 == '7')
             column22 = 7;
        if(ship2column2 == '8')
             column22 = 8;
        if(ship2column2 == '9')
             column22 = 9;

        if(ship3column1 == '0') //SHIP 3 COLUMN 1
             column31 = 0;
        if(ship3column1 == '1')
             column31 = 1;
        if(ship3column1 == '2')
             column31 = 2;
        if(ship3column1 == '3')
             column31 = 3;
        if(ship3column1 == '4')
             column31 = 4;
        if(ship3column1 == '5')
             column31 = 5;
        if(ship3column1 == '6')
             column31 = 6;
        if(ship3column1 == '7')
             column31 = 7;
        if(ship3column1 == '8')
             column31 = 8;
        if(ship3column1 == '9')
             column31 = 9;

        if(ship3column2 == '0') //SHIP 3 COLUMN 2
             column32 = 0;
        if(ship3column2 == '1')
             column32 = 1;
        if(ship3column2 == '2')
             column32 = 2;
        if(ship3column2 == '3')
             column32 = 3;
        if(ship3column2 == '4')
             column32 = 4;
        if(ship3column2 == '5')
             column32 = 5;
        if(ship3column2 == '6')
             column32 = 6;
        if(ship3column2 == '7')
             column32 = 7;
        if(ship3column2 == '8')
             column32 = 8;
        if(ship3column2 == '9')
             column32 = 9;

        if(ship3column3 == '0') //SHIP 3 COLUMN 3
             column33 = 0;
        if(ship3column3 == '1')
             column33 = 1;
        if(ship3column3 == '2')
             column33 = 2;
        if(ship3column3 == '3')
             column33 = 3;
        if(ship3column3 == '4')
             column33 = 4;
        if(ship3column3 == '5')
             column33 = 5;
        if(ship3column3 == '6')
             column33 = 6;
        if(ship3column3 == '7')
             column33 = 7;
        if(ship3column3 == '8')
             column33 = 8;
        if(ship3column3 == '9')
             column33 = 9;

        if(ship4column1 == '0') //SHIP 4 COLUMN 1
             column41 = 0;
        if(ship4column1 == '1')
             column41 = 1;
        if(ship4column1 == '2')
             column41 = 2;
        if(ship4column1 == '3')
             column41 = 3;
        if(ship4column1 == '4')
             column41 = 4;
        if(ship4column1 == '5')
             column41 = 5;
        if(ship4column1 == '6')
             column41 = 6;
        if(ship4column1 == '7')
             column41 = 7;
        if(ship4column1 == '8')
             column41 = 8;
        if(ship4column1 == '9')
             column41 = 9;

        if(ship4column2 == '0') //SHIP 4 COLUMN 2
             column42 = 0;
        if(ship4column2 == '1')
             column42 = 1;
        if(ship4column2 == '2')
             column42 = 2;
        if(ship4column2 == '3')
             column42 = 3;
        if(ship4column2 == '4')
             column42 = 4;
        if(ship4column2 == '5')
             column42 = 5;
        if(ship4column2 == '6')
             column42 = 6;
        if(ship4column2 == '7')
             column42 = 7;
        if(ship4column2 == '8')
             column42 = 8;
        if(ship4column2 == '9')
             column42 = 9;

        if(ship4column3 == '0') //SHIP 4 COLUMN 3
             column43 = 0;
        if(ship4column3 == '1')
             column43 = 1;
        if(ship4column3 == '2')
             column43 = 2;
        if(ship4column3 == '3')
             column43 = 3;
        if(ship4column3 == '4')
             column43 = 4;
        if(ship4column3 == '5')
             column43 = 5;
        if(ship4column3 == '6')
             column43 = 6;
        if(ship4column3 == '7')
             column43 = 7;
        if(ship4column3 == '8')
             column43 = 8;
        if(ship4column3 == '9')
             column43 = 9;

        if(ship4column4 == '0') //SHIP 4 COLUMN 4
             column44 = 0;
        if(ship4column4 == '1')
             column44 = 1;
        if(ship4column4 == '2')
             column44 = 2;
        if(ship4column4 == '3')
             column44 = 3;
        if(ship4column4 == '4')
             column44 = 4;
        if(ship4column4 == '5')
             column44 = 5;
        if(ship4column4 == '6')
             column44 = 6;
        if(ship4column4 == '7')
             column44 = 7;
        if(ship4column4 == '8')
             column44 = 8;
        if(ship4column4 == '9')
             column44 = 9;


        for(int r = 0; r < 10; r++)
            {
                if(r == 0)
                    cout << "   0   1   2   3   4   5   6   7   8   9 " << endl;

                cout << " -----------------------------------------"<< endl;
                for(int c = 0; c < 10; c++)
                    {

                                        switch(ship1row1)
                                        {

                                        case 'A': row = 0;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        case 'B': row = 1;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        case 'C': row = 2;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        case 'D': row = 3;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        case 'E': row = 4;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        case 'F': row = 5;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        case 'G': row = 6;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        case 'H': row = 7;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        case 'I': row = 8;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        case 'J': row = 9;
                                                  POOP2[row][column] = 'Z';
                                                  break;
                                        }

                                        switch(ship2row1)
                                        {

                                        case 'A': row21 = 0;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        case 'B': row21 = 1;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        case 'C': row21 = 2;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        case 'D': row21 = 3;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        case 'E': row21 = 4;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        case 'F': row21 = 5;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        case 'G': row21 = 6;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        case 'H': row21 = 7;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        case 'I': row21 = 8;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        case 'J': row21 = 9;
                                                  POOP2[row21][column21] = 'Z';
                                                  break;
                                        }

                                        switch(ship2row2)
                                        {

                                        case 'A': row22 = 0;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        case 'B': row22 = 1;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        case 'C': row22 = 2;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        case 'D': row22 = 3;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        case 'E': row22 = 4;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        case 'F': row22 = 5;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        case 'G': row22 = 6;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        case 'H': row22 = 7;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        case 'I': row22 = 8;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        case 'J': row22 = 9;
                                                  POOP2[row22][column22] = 'Z';
                                                  break;
                                        }

                                        switch(ship3row1)
                                        {

                                        case 'A': row31 = 0;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        case 'B': row31 = 1;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        case 'C': row31 = 2;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        case 'D': row31 = 3;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        case 'E': row31 = 4;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        case 'F': row31 = 5;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        case 'G': row31 = 6;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        case 'H': row31 = 7;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        case 'I': row31 = 8;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        case 'J': row31 = 9;
                                                  POOP2[row31][column31] = 'Z';
                                                  break;
                                        }

                                        switch(ship3row2)
                                        {

                                        case 'A': row32 = 0;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        case 'B': row32 = 1;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        case 'C': row32 = 2;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        case 'D': row32 = 3;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        case 'E': row32 = 4;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        case 'F': row32 = 5;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        case 'G': row32 = 6;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        case 'H': row32 = 7;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        case 'I': row32 = 8;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        case 'J': row32 = 9;
                                                  POOP2[row32][column32] = 'Z';
                                                  break;
                                        }

                                        switch(ship3row3)
                                        {

                                        case 'A': row33 = 0;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        case 'B': row33 = 1;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        case 'C': row33 = 2;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        case 'D': row33 = 3;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        case 'E': row33 = 4;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        case 'F': row33 = 5;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        case 'G': row33 = 6;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        case 'H': row33 = 7;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        case 'I': row33 = 8;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        case 'J': row33 = 9;
                                                  POOP2[row33][column33] = 'Z';
                                                  break;
                                        }

                                        switch(ship4row1)
                                        {

                                        case 'A': row41 = 0;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        case 'B': row41 = 1;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        case 'C': row41 = 2;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        case 'D': row41 = 3;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        case 'E': row41 = 4;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        case 'F': row41 = 5;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        case 'G': row41 = 6;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        case 'H': row41 = 7;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        case 'I': row41 = 8;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        case 'J': row41 = 9;
                                                  POOP2[row41][column41] = 'Z';
                                                  break;
                                        }

                                        switch(ship4row1)
                                        {

                                        case 'A': row42 = 0;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        case 'B': row42 = 1;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        case 'C': row42 = 2;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        case 'D': row42 = 3;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        case 'E': row42 = 4;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        case 'F': row42 = 5;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        case 'G': row42 = 6;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        case 'H': row42 = 7;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        case 'I': row42 = 8;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        case 'J': row42 = 9;
                                                  POOP2[row42][column42] = 'Z';
                                                  break;
                                        }

                                        switch(ship4row3)
                                        {

                                        case 'A': row43 = 0;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        case 'B': row43 = 1;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        case 'C': row43 = 2;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        case 'D': row43 = 3;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        case 'E': row43 = 4;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        case 'F': row43 = 5;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        case 'G': row43 = 6;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        case 'H': row43 = 7;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        case 'I': row43 = 8;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        case 'J': row43 = 9;
                                                  POOP2[row43][column43] = 'Z';
                                                  break;
                                        }

                                        switch(ship4row4)
                                        {

                                        case 'A': row44 = 0;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        case 'B': row44 = 1;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        case 'C': row44 = 2;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        case 'D': row44 = 3;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        case 'E': row44 = 4;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        case 'F': row44 = 5;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        case 'G': row44 = 6;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        case 'H': row44 = 7;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        case 'I': row44 = 8;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        case 'J': row44 = 9;
                                                  POOP2[row44][column44] = 'Z';
                                                  break;
                                        }


                            cout << " | " << POOP2[r][c];
                            if(c == 9 && r == 0)
                                cout << " |   A";
                            else if(c == 9 && r == 1)
                                cout << " |   B";
                            else if(c == 9 && r == 2)
                                cout << " |   C";
                            else if(c == 9 && r == 3)
                                cout << " |   D";
                            else if(c == 9 && r == 4)
                                cout << " |   E";
                            else if(c == 9 && r == 5)
                                cout << " |   F";
                            else if(c == 9 && r == 6)
                                cout << " |   G";
                            else if(c == 9 && r == 7)
                                cout << " |   H";
                            else if(c == 9 && r == 8)
                                cout << " |   I";
                            else if(c == 9 && r == 9)
                                cout << " |   J";
                    }
                cout << endl;
                if(r == 9)
                cout << " -----------------------------------------" << endl;
            }

            if(count == 6)
            {
                cout << "Now, here are your ships!" << endl;
                cout << "Plus an empty board to begin placing your missles!" << endl;
                cout << "Please enter a coordinate to begin your missle strike!" << endl << endl;

                EmptyBoard2();

                cin >> attackrow >> attackcolumn;

                if(attackrow >= 'a' && attackrow <= 'j')
                    attackrow -= 32;
               while((attackrow < 'A' || attackrow > 'J') || (attackcolumn < '0' || attackcolumn > '9'))
               {
                    cin.ignore(10000,'\n');
                    cin >> attackrow >> attackcolumn;
                    cout << "Invalid input! Try again" << endl;
                    if(attackrow >= 'a' && attackrow <= 'j')
                    attackrow -= 32;
               }
                ATTACK = HitOrMiss2(attackrow, attackcolumn);
                    if(ATTACK == true)
                    {
                        cout << "HIT!!" << endl;
                        cin.ignore();
                        cin.get();
                        if (system("CLS")) system("clear");
                    }
                    else
                    {
                        cout << "MISS!" << endl;
                        cin.ignore();
                        cin.get();
                        if (system("CLS")) system("clear");
                    }
            }
            else if(count > 6)
            {
                EmptyBoard2();

                cin >> attackrow >> attackcolumn;

                if(attackrow >= 'a' && attackrow <= 'j')
                    attackrow -= 32;
                while((attackrow < 'A' || attackrow > 'J') || (attackcolumn < '0' || attackcolumn > '9'))
                {
                    cin.ignore(10000,'\n');
                    cin >> attackrow >> attackcolumn;
                    cout << "Invalid input! Try again" << endl;
                    if(attackrow >= 'a' && attackrow <= 'j')
                    attackrow -= 32;
                }
                ATTACK = HitOrMiss2(attackrow, attackcolumn);
                    if(ATTACK == true)
                    {
                        cout << "HIT!!" << endl;
                        cin.ignore();
                        cin.get();
                        if (system("CLS")) system("clear");
                    }
                    else
                    {
                        cout << "MISS!" << endl;
                        cin.ignore();
                        cin.get();
                        if (system("CLS")) system("clear");
                    }
            }
            else;
    }

void Limbo()
    {
        static int count = 1;
                if(count == 1)
                    {
                        cout << endl << endl << endl;
                        cout << "\t\t\t\tGreat! Now let's let Player 2 pick their ship locations!" << endl << endl;
                        cout << "\t\t\t\t\t\tPlease switch places" << endl << endl;
                        cout << "\t\t\t\t\t Press 'ENTER' when Player 2 has arrived" << endl << endl;
                        cin.get();
                            while(cin.get() != '\n')
                                {
                                    if (system("CLS")) system("clear");
                                    cout << endl << endl << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    cout << "\t\t\t\t\t\tInvalid entry, now" << endl;
                                    cout << "\t\t\t\t\t\tpress 'ENTER' twice please" << endl;
                                    cin.get();
                                }
                     }
                else if(count == 2)
                    {
                        cout << endl << endl << endl;
                        cout << "\t\t\t  ALL RIGHT! Now that we've established both Players' ship locations!" << endl << endl;
                        cout << "\t\t\t\t\t\tLET'S BEGIN!" << endl << endl;
                        cout << "\t\t\t\t\tPress 'ENTER' for Player 1 to begin!" << endl;
                        cin.get();
                           while(cin.get() != '\n')
                                {
                                    if (system("CLS")) system("clear");
                                    cout << endl << endl << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    cout << "\t\t\t\t\t\tInvalid entry, now" << endl;
                                    cout << "\t\t\t\t\t\tpress 'ENTER' twice please" << endl;
                                    cin.get();
                                }
                     }
                else if(count >=3)
                {

                    if(count % 2 == 0)
                    {
                        cout << endl << endl << endl << endl;
                        cout<<"\t\t\t\t\t\tPress 'ENTER' twice for Player 1" << endl;
                        cin.get();
                           while(cin.get() != '\n')
                                {
                                    if (system("CLS")) system("clear");
                                    cout << endl << endl << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    cout << "\t\t\t\t\t\tInvalid entry, now" << endl;
                                    cout << "\t\t\t\t\t\tpress 'ENTER' twice please" << endl;
                                    cin.get();
                                }
                        if (system("CLS")) system("clear");
                    }
                    else
                    {
                        cout << endl << endl << endl << endl;
                        cout << "\t\t\t\t\tPress 'ENTER' twice for Player 2" << endl;
                        cin.get();
                           while(cin.get() != '\n')
                                {
                                    if (system("CLS")) system("clear");
                                    cout << endl << endl << endl;
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    cout << "\t\t\t\t\t\tInvalid entry, now" << endl;
                                    cout << "\t\t\t\t\t\tpress 'ENTER' twice please" << endl;
                                    cin.get();
                                }
                        if (system("CLS")) system("clear");
                    }
                }
                else;
            count ++;
        }
bool Victory()
    {
        if(a == true && b == true && z == true && d == true && e == true && f == true && g == true && h == true && u == true && v == true)
        {
            if (system("CLS")) system("clear");
            cout << endl << endl << endl << endl;
            cout << "\t\t\t\t\t\t\tPlAYER 1 WINS!\a" << endl;
            return true;
        }
        else if(k == true && l == true && m == true && n == true && o == true && w == true && x == true && y == true && s == true && t == true)
        {
            if (system("CLS")) system("clear");
            cout << endl << endl << endl << endl;
            cout << "\t\t\t\t\t\t\tPLAYER 2 WINS!\a" << endl;
            return true;
        }
        else
            return false;

    }
