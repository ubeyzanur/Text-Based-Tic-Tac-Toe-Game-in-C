#include "game.h"

// Main function
int main() {
    char *player1 = NULL, *player2 = NULL;  // Declare player names as pointers

    while (1) {
        printf("Welcome to Tic Tac Toe!\n");
        printf("1. Play a new game\n");
        printf("2. How to play\n");
        printf("3. Quit\n");

        int choice = readMenuOption(); // Read the user's menu option

        if (choice == 3) {
            if (currentBoard != NULL) {
                freeBoard();
            }
            printf("Exiting the game. Goodbye!\n");
            break;
        }

        if (choice == 1) {
            // Dynamically allocate memory for player names based on input length
            player1 = (char *)malloc(50 * sizeof(char)); // Allocating memory for player1
            player2 = (char *)malloc(50 * sizeof(char)); // Allocating memory for player2

            if (player1 == NULL || player2 == NULL) {
                printf("Memory allocation failed.\n");
                return 1;  // Exit if memory allocation fails
            }

            printf("Enter Player 1's name: ");
            scanf("%s", player1);  // User input for player1 name
            printf("Enter Player 2's name: ");
            scanf("%s", player2);  // User input for player2 name

            selectBoardSize();
            initBoard();

            while (1) {
                printBoard();
                printf("%s's (%c) turn.\n", 
                    currentPlayer == 'X' ? player1 : player2, currentPlayer); // Display the current player's name and symbol (X or O) to indicate whose turn it is

                int row, col;
                validateRowColumn(&row, &col);

                if (row == -1 && col == -1) {
                    break;
                }

                makeMove(row, col);

                if (checkWin(currentPlayer)) {
                    printBoard();
                    printf("%s wins!\n", currentPlayer == 'X' ? player1 : player2);
                    if (undoStack != NULL) {
                        freeStack(undoStack);
                        undoStack = NULL;
                    }
                    if (redoStack != NULL) {
                        freeStack(redoStack);
                        redoStack = NULL;
                    }
                    if (currentBoard != NULL) {
                        freeBoard();
                    }
                    break;
                }

                if (isDraw()) {
                    printBoard();
                    printf("It's a draw!\n");
                    if (undoStack != NULL) {
                        freeStack(undoStack);
                        undoStack = NULL;
                    }
                    if (redoStack != NULL) {
                        freeStack(redoStack);
                        redoStack = NULL;
                    }
                    if (currentBoard != NULL) {
                        freeBoard();
                    }
                    break;
                }

                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }

            // Free dynamically allocated memory after use
            free(player1);
            free(player2);
        } else if (choice == 2) {
            printf("How to play:\n");
            printf("1. Choose a player to start\n");
            printf("2. Players alternate turns\n");
            printf("3. Enter row and column to place your mark (X or O)\n");
            printf("4. You can undo (8) or redo (9) your moves.\n");
        }
    }

    if (undoStack != NULL) {
        freeStack(undoStack);
    }
    if (redoStack != NULL) {
        freeStack(redoStack);
    }

    return 0;
}
