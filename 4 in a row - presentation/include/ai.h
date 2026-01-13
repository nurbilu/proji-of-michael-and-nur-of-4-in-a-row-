/*
 * ai.h - Computer AI header
 * Defines AI difficulty levels and move selection
 */

#ifndef AI_H
#define AI_H

#include "board.h"

/* Difficulty levels */
#define EASY 1
#define MEDIUM 2
#define HARD 3

/* Function declarations */

/* Gets a random valid move (Easy difficulty) */
int getRandomMove(int board[ROWS][COLS]);

/* Gets a smart move (Medium difficulty) */
int getMediumMove(int board[ROWS][COLS], int aiPlayer);

/* Gets best move using minimax (Hard difficulty) */
int getHardMove(int board[ROWS][COLS], int aiPlayer);

/* Main AI function - selects move based on difficulty */
int getAIMove(int board[ROWS][COLS], int difficulty, int aiPlayer);

#endif /* AI_H */
