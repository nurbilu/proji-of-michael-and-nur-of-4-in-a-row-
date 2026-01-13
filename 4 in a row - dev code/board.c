/*
 * board.c - Board operations implementation
 * Handles board initialization and disc placement
 */

#include "board.h"

/* Initializes all board cells to EMPTY */
void initBoard(int board[ROWS][COLS]) {
    int row, col;
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            board[row][col] = EMPTY;
        }
    }
}

/* Checks if column is within bounds and has empty space */
int isValidMove(int board[ROWS][COLS], int col) {
    /* Check column bounds */
    if (col < 0 || col >= COLS) {
        return 0;
    }
    /* Check if top row of column is empty */
    return board[0][col] == EMPTY;
}

/* Drops disc into column, returns row or -1 if invalid */
int dropDisc(int board[ROWS][COLS], int col, int player) {
    int row;
    
    /* Validate move first */
    if (!isValidMove(board, col)) {
        return -1;
    }
    
    /* Find lowest empty row in column */
    for (row = ROWS - 1; row >= 0; row--) {
        if (board[row][col] == EMPTY) {
            board[row][col] = player;
            return row;
        }
    }
    
    return -1;
}

/* Returns 1 if board is full, 0 otherwise */
int isBoardFull(int board[ROWS][COLS]) {
    int col;
    for (col = 0; col < COLS; col++) {
        if (board[0][col] == EMPTY) {
            return 0;
        }
    }
    return 1;
}

/* Copies entire board from source to destination */
void copyBoard(int dest[ROWS][COLS], int src[ROWS][COLS]) {
    int row, col;
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            dest[row][col] = src[row][col];
        }
    }
}

