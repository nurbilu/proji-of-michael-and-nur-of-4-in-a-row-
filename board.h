/*
 * board.h - Board operations header
 * Defines board constants and functions for board management
 */

#ifndef BOARD_H
#define BOARD_H

/* Board dimensions */
#define ROWS 6
#define COLS 7

/* Cell states */
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

/* Function declarations */

/* Initializes the board to empty state */
void initBoard(int board[ROWS][COLS]);

/* Checks if a column is valid and not full */
int isValidMove(int board[ROWS][COLS], int col);

/* Drops a disc into a column, returns the row where it landed (-1 if invalid) */
int dropDisc(int board[ROWS][COLS], int col, int player);

/* Checks if board is completely full */
int isBoardFull(int board[ROWS][COLS]);

/* Copies board from source to destination */
void copyBoard(int dest[ROWS][COLS], int src[ROWS][COLS]);

#endif /* BOARD_H */

