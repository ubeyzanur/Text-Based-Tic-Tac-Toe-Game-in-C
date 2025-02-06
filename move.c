#include "game.h"

// Undo a move
void undoMove() {
    if (undoStack == NULL) {
        printf("No moves to undo!\n");
        return;
    }

    Move lastMove = pop(&undoStack); // Retrieve the last move
    currentBoard[lastMove.row][lastMove.col] = ' '; // Remove the move from the board
    push(&redoStack, lastMove); // Push the move to the redo stack

    moveCount--;
    currentPlayer = lastMove.player; // Restore the player's turn

    printBoard();
    printf("%s's (%c) turn. Enter row and column (7 to quit, 8 to undo, 9 to redo):\n",
        currentPlayer == 'X' ? player1 : player2, currentPlayer);
}

// Redo a move
void redoMove() {
    if (redoStack == NULL) {
        printf("No moves to redo!\n");
        return;
    }

    Move redoMove = pop(&redoStack); // Retrieve the last undone move
    currentBoard[redoMove.row][redoMove.col] = redoMove.player; // Reapply the move
    push(&undoStack, redoMove); // Push the move back to the undo stack

    moveCount++;
    currentPlayer = (redoMove.player == 'X') ? 'O' : 'X'; // Switch turns

    printBoard();
    printf("%s's (%c) turn. Enter row and column (7 to quit, 8 to undo, 9 to redo):\n",
        currentPlayer == 'X' ? player1 : player2, currentPlayer);
}