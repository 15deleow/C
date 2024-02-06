#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

//Constants
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESCAPE 27
#define DELAY 100000000
#define BLOCK 177
#define FILENAME "record.txt"

//Global Variables
int length;
int bend_no;
int len;
char key;
int life;

//Prototypes//
/**
 * Name: ReadPlayerName
 * Input: Variable to store player's name
 * Output: N/A
 * Description:
 *  Prompts player for their name
*/
void ReadPlayerName(char *plname);

/**
 * Name: WriteToFile
 * Input: modified player name, player's game score
 * Ouput: N/A
 * Description:
 *  Stores Players name and current score to the records file.
*/
void WriteToFile(const char *nplname, int score);

/**
 * Name: DisplayRecords
 * Input: N/A
 * Output: N/A
 * Description:
 *  Displays all the past game records.
*/
void DisplayRecords();

/**
 * Name: record
 * Input: N/A
 * Output: N/A
 * Description:
 *  Prompts user for their name and saves their game score. Display's
 *  past game scores if requested.
*/
void record();

/**
 * Name: load
 * Input: N/A
 * Output: N/A
 * Description:
 *  Displays a loading animation to the terminal window.
*/
void load();

/**
 * Name: Delay
 * Input: duration in seconds
 * Output: N/A
 * Description:
 *  Delays program for a certain time
*/
void Delay(long double);

/**
 * Name: Move
 * Input: N/A
 * Ouput: N/A
 * Description:
 *  Controls the movement, user input, and game logic for the snake game.
 *  Uses recursion to kep the game loop running and handle user input for
 *  changing the direction of the snake
*/
void Move();

/**
 * Name: Food
 * Input: N/A
 * Output: N/A
 * Description:
 *  Initializes the food for the first time and generates new coordinates for
 *  the food when the snake eats the current food.
*/
void Food();

/**
 * Name: Score
 * Input: N/A
 * Output: Player's current game score
 * Description:
 *  
*/
int Score();

/**
 * Name: Print
 * Input: N/A
 * Output: N/A
 * Description:
 *  Displays the title of game and game instructions.
 *  
*/
void Print();

void gotoxy(int x, int y);

/**
 * Name: GotoXY
 * Input: X and Y Coordinates
 * Output: N/A
 * Descriptions
 *  Updates the coordinates of the cursor in the console window. 
*/
void GotoXY(int x,int y);

/**
 * Name: Bend
 * Input: N/A
 * Output: N/A
 * Description:
 *  Handles logic to bend the snake when snake reaches
 *  the bounds of the console window.
*/
void Bend();

/**
 * Name: Boarder
 * Input: N/A
 * Output: N/A
 * Description:
 *  Draws the game board, including the walls and food.
*/
void Boarder();

/**
 * Name: Down
 * Input: N/A
 * Output: N/A
 * Description:
 *  Moves the snake down
*/
void Down();

/**
 * Name: Left
 * Input: N/A
 * Output: N/A
 * Description:
 *  Moves the snake left
*/
void Left();

/**
 * Name: Up
 * Input: N/A
 * Output: N/A
 * Description:
 *  Moves the snake up
*/
void Up();

/**
 * Name: Right
 * Input: N/A
 * Output: N/A
 * Description:
 *  Moves the snake right
*/
void Right();

/**
 * Name: ExitGame
 * Input: N/A
 * Output: N/A
 * Description:
 *  Handles the logic for when the game should exit or
 *  when a life is lost.
*/
void ExitGame();

/**
 * Name: Scoreonly
 * Input: N/A
 * Output: N/A
 * Description:
 *  
*/
int Scoreonly();

struct coordinate
{
    int x;
    int y;
    int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

#endif