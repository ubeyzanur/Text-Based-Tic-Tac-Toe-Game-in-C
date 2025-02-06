#include "game.h"

// Push to stack
void push(StackNode** stack, Move move) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode)); // Allocate memory for stack node
    newNode->move = move; // Assign the move to the new node
    newNode->next = *stack; // Point the new node to the current top of the stack
    *stack = newNode; // Update the stack pointer to the new node
}

// Pop from stack
Move pop(StackNode** stack) {
    if (*stack == NULL) {
        Move emptyMove = {-1, -1, ' '}; // Return a default move for empty stack
        return emptyMove;
    }
    StackNode* temp = *stack;
    *stack = (*stack)->next;
    Move move = temp->move;
    free(temp);
    return move;
}

// Free the stack memory
void freeStack(StackNode* stack) {
    while (stack != NULL) {
        StackNode* temp = stack;
        stack = stack->next;
        free(temp);
    }
}