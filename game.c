#include "game.h"

// Global variables
StackNode* undoStack = NULL;
StackNode* redoStack = NULL;
int moveCount = 0;
char currentPlayer = 'X';
char** currentBoard;
int boardSize = 3;
char *player1;
char *player2;


// Make a move on the board
void makeMove(int row, int col) {
    if (currentBoard[row][col] == ' ') { // Ensure the cell is empty
        currentBoard[row][col] = currentPlayer; // Place the current player's marker
        moveCount++; 
        Move newMove = {row, col, currentPlayer}; // Create a new move
        push(&undoStack, newMove); // Push the move onto the undo stack
        freeStack(redoStack); // Clear the redo stack as the history is reset
        redoStack = NULL; // Reset redo stack pointer to NULL
    }
}

// Check for a win
bool checkWin(char player) {
    for (int i = 0; i < boardSize; i++) {
        bool rowWin = true, colWin = true;
        for (int j = 0; j < boardSize; j++) {
            if (currentBoard[i][j] != player) rowWin = false;
            if (currentBoard[j][i] != player) colWin = false;
        }
        if (rowWin || colWin) return true;
    }

    bool diag1Win = true, diag2Win = true;
    for (int i = 0; i < boardSize; i++) {
        if (currentBoard[i][i] != player) diag1Win = false;
        if (currentBoard[i][boardSize - i - 1] != player) diag2Win = false;
    }
    return diag1Win || diag2Win;
}

// Check for a draw
bool isDraw() {
    return moveCount == boardSize * boardSize;
}

// Read an integer input
int readInt() {
    char input[10];
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (strlen(input) == 2 && input[0] >= '0' && input[0] <= '9') {
            return input[0] - '0';
        } else {
            printf("Please enter a single digit.\n"); 
        }
    }
}

// Validate menu input
int readMenuOption() {
    int option;
    while (1) {
        printf("Enter your choice: ");
        option = readInt();
        if (option == 1 || option == 2 || option == 3) {
            return option;
        } else {
            printf("Invalid choice! Please enter 1, 2, or 3.\n");
        }
    }
}


// Validate row and column input
void validateRowColumn(int *row, int *col) {
    while (1) {
        printf("Enter row and column:\n");
        printf("6 to return to menu, 7 to quit, 8 to undo, 9 to redo\n");

        printf("Row: ");
        *row = readInt(); // Read row input
 
        if (*row == 6) { // Return to menu
            if (currentBoard != NULL) {
                freeBoard();
            }
            if (undoStack != NULL) {
                freeStack(undoStack);
                undoStack = NULL;
            }
            if (redoStack != NULL) {
                freeStack(redoStack);
                redoStack = NULL;
            }
            printf("Returning to the main menu...\n");
            *row = -1;
            *col = -1;
            return;
        } else if (*row == 7) { // Quit game
            if (currentBoard != NULL) {
                freeBoard();
            }
            if (undoStack != NULL) {
                freeStack(undoStack);
                undoStack = NULL;
            }
            if (redoStack != NULL) {
                freeStack(redoStack);
                redoStack = NULL;
            }
            printf("Exiting the game. Goodbye!\n");
            exit(0);
        } else if (*row == 8) {
            undoMove();
            continue;
        } else if (*row == 9) {
            redoMove();
            continue;
        }

        printf("Column: ");
        *col = readInt(); // Read column input

        *row -= 1;
        *col -= 1;

        if (*row >= 0 && *row < boardSize && *col >= 0 && *col < boardSize) {
            if (currentBoard[*row][*col] == ' ') { //is valid
                break;
            } else {
                printf("Invalid move! The cell is already occupied. Please try again.\n");
            }
        } else {
            printf("Invalid move! Out of bounds. Please try again.\n");
        }
    }
}
