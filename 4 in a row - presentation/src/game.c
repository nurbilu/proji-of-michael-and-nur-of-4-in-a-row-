/*
 * game.c - Game logic implementation
 * Handles win detection and game state
 */

#include "../include/game.h"

/* Checks for 4 in a row horizontally */
int checkHorizontal(int board[ROWS][COLS], int player) {
    int row, col;
    for (row = 0; row < ROWS; row++) {
        for (col = 0; col <= COLS - 4; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return 1;
            }
        }
    }
    return 0;
}

/* Checks for 4 in a row vertically */
int checkVertical(int board[ROWS][COLS], int player) {
    int row, col;
    for (row = 0; row <= ROWS - 4; row++) {
        for (col = 0; col < COLS; col++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return 1;
            }
        }
    }
    return 0;
}

/* Checks for 4 in a row diagonally (both directions) */
int checkDiagonal(int board[ROWS][COLS], int player) {
    int row, col;
    
    /* Check diagonal down-right */
    for (row = 0; row <= ROWS - 4; row++) {
        for (col = 0; col <= COLS - 4; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return 1;
            }
        }
    }
    
    /* Check diagonal up-right */
    for (row = 3; row < ROWS; row++) {
        for (col = 0; col <= COLS - 4; col++) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return 1;
            }
        }
    }
    
    return 0;
}

/* Returns 1 if player has won, 0 otherwise */
int checkWin(int board[ROWS][COLS], int player) {
    return checkHorizontal(board, player) ||
           checkVertical(board, player) ||
           checkDiagonal(board, player);
}

/* Returns game state: GAME_WIN, GAME_TIE, or GAME_ONGOING */
int getGameState(int board[ROWS][COLS], int lastPlayer) {
    if (checkWin(board, lastPlayer)) {
        return GAME_WIN;
    }
    if (isBoardFull(board)) {
        return GAME_TIE;
    }
    return GAME_ONGOING;
}
