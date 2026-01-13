/*
 * game.h - Game logic header
 * Defines game state and win checking functions
 */

#ifndef GAME_H
#define GAME_H

#include "board.h"

/* Game result states */
#define GAME_ONGOING 0
#define GAME_WIN 1
#define GAME_TIE 2

/* Function declarations */

/* Checks for 4 in a row horizontally */
int checkHorizontal(int board[ROWS][COLS], int player);

/* Checks for 4 in a row vertically */
int checkVertical(int board[ROWS][COLS], int player);

/* Checks for 4 in a row diagonally */
int checkDiagonal(int board[ROWS][COLS], int player);

/* Checks if a player has won */
int checkWin(int board[ROWS][COLS], int player);

/* Checks game state: ongoing, win, or tie */
int getGameState(int board[ROWS][COLS], int lastPlayer);

#endif /* GAME_H */
