/*
 * ui.h - User Interface header
 * Defines display and input functions
 */

#ifndef UI_H
#define UI_H

#include "board.h"

/* Color codes for Windows console */
#define COLOR_DEFAULT 7
#define COLOR_RED 12
#define COLOR_YELLOW 14
#define COLOR_BLUE 9
#define COLOR_GREEN 10
#define COLOR_CYAN 11

/* Function declarations */

/* Clears the console screen */
void clearScreen(void);

/* Sets console text color */
void setColor(int color);

/* Displays the game board with colors */
void displayBoard(int board[ROWS][COLS]);

/* Displays the main menu */
void displayMainMenu(void);

/* Displays difficulty selection menu */
void displayDifficultyMenu(void);

/* Gets valid column input from user (1-7) */
int getPlayerMove(int board[ROWS][COLS], int player);

/* Displays win message */
void displayWinMessage(int player);

/* Displays tie message */
void displayTieMessage(void);

/* Displays game title banner */
void displayTitle(void);

/* Waits for user to press Enter */
void waitForEnter(void);

/* Gets a valid menu choice from user */
int getMenuChoice(int min, int max);

#endif /* UI_H */
