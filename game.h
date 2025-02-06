#ifndef GAME_H
#define GAME_H

#define MAX_HISTORY 100
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Struct definitions
typedef struct {
    int row;
    int col;
    char player;
} Move;

typedef struct StackNode {
    Move move;
    struct StackNode* next;
} StackNode;

// Global variables
extern StackNode* undoStack;
extern StackNode* redoStack;
extern int moveCount;
extern char currentPlayer;
extern char *player1;
extern char *player2;
extern char** currentBoard;
extern int boardSize;

// ANSI codes of colours
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

// Board initialization
void initBoard();

// Free the board memory
void freeBoard();

// Push to stack
void push(StackNode** stack, Move move);

// Pop from stack
Move pop(StackNode** stack);

// Free the stack memory
void freeStack(StackNode* stack);

// Print the current board state
void printBoard();

// Make a move on the board
void makeMove(int row, int col);

// Undo a move
void undoMove();

// Redo a move
void redoMove();

// Check for a win
bool checkWin(char player);

// Check for a draw
bool isDraw();

// Read an integer input
int readInt();

// Validate menu input
int readMenuOption();

// Select board size
void selectBoardSize();

// Validate row and column input
void validateRowColumn(int *row, int *col);

#endif // GAME_H
