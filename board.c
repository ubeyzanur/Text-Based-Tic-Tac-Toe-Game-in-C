#include "game.h"

// Board initialization
void initBoard() {
    currentBoard = (char **)malloc(boardSize * sizeof(char *));
    for (int i = 0; i < boardSize; i++) {
        currentBoard[i] = (char *)malloc(boardSize * sizeof(char));
        for (int j = 0; j < boardSize; j++) {
            currentBoard[i][j] = ' ';
        }
    }
    moveCount = 0;
    currentPlayer = 'X';
}

// Free the board memory
void freeBoard() {
    if (currentBoard != NULL) {
        for (int i = 0; i < boardSize; i++) {
            free(currentBoard[i]);
        }
        free(currentBoard);
        currentBoard = NULL;
    }
}

// Print the current board state
void printBoard() {
    system("clear"); // Clear the console
    printf("Current Board:\n");

    printf("   ");
    for (int j = 0; j < boardSize; j++) {
        printf(BLUE " %d  " RESET, j + 1); // Print column numbers in blue
    }
    printf("\n");

    for (int i = 0; i < boardSize; i++) {
        printf(BLUE " %d " RESET, i + 1); // Print row numbers in blue
        for (int j = 0; j < boardSize; j++) {
            if (currentBoard[i][j] == 'X') printf(RED " X " RESET); // Red for X
            else if (currentBoard[i][j] == 'O') printf(GREEN " O " RESET); // Green for O
            else printf(" . "); // Dot for empty spaces
            if (j < boardSize - 1) printf("|"); // Print vertical separators
        }
        printf("\n");
        if (i < boardSize - 1) {
            printf("   ");
            for (int j = 0; j < boardSize; j++) printf("--- "); // Print horizontal separators
            printf("\n");
        }
    }
}

// Select board size
void selectBoardSize() {
    int input;
    while (1) {
        printf("Select board size (3-5): ");
        
        input = readInt();

        if (input >= 3 && input <= 5) {
            boardSize = input;
            break; // Valid input, exit loop
        }
        
        // Print error message only if the input is invalid
        printf("Invalid input! Please enter a value between 3 and 5.\n");
    }
}
