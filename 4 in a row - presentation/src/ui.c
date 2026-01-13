/*
 * ui.c - User Interface implementation
 * Handles console display and user input
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/ui.h"

/* Clears remaining characters from input buffer */
static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Discard characters until newline */
    }
}

/* Reads an integer from user input, returns 1 on success, 0 on failure */
static int readInteger(int* value) {
    int result;
    result = scanf("%d", value);
    clearInputBuffer();
    return (result == 1);
}

/* Clears the console screen */
void clearScreen(void) {
    system("cls");
}

/* Sets console text color using Windows API */
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

/* Displays the game title banner */
void displayTitle(void) {
    setColor(COLOR_CYAN);
    printf("\n");
    printf("  ====================================\n");
    printf("  |     CONNECT FOUR - 4 IN A ROW   |\n");
    printf("  ====================================\n");
    setColor(COLOR_DEFAULT);
}

/* Displays the game board with colored discs */
void displayBoard(int board[ROWS][COLS]) {
    int row, col;
    
    printf("\n");
    
    /* Column numbers */
    setColor(COLOR_GREEN);
    printf("    ");
    for (col = 0; col < COLS; col++) {
        printf(" %d  ", col + 1);
    }
    printf("\n");
    setColor(COLOR_DEFAULT);
    
    /* Top border */
    setColor(COLOR_BLUE);
    printf("   +");
    for (col = 0; col < COLS; col++) {
        printf("---+");
    }
    printf("\n");
    
    /* Board cells */
    for (row = 0; row < ROWS; row++) {
        setColor(COLOR_BLUE);
        printf("   |");
        
        for (col = 0; col < COLS; col++) {
            if (board[row][col] == EMPTY) {
                printf("   ");
            } else if (board[row][col] == PLAYER1) {
                setColor(COLOR_RED);
                printf(" O ");
            } else {
                setColor(COLOR_YELLOW);
                printf(" O ");
            }
            setColor(COLOR_BLUE);
            printf("|");
        }
        printf("\n");
        
        /* Row separator */
        printf("   +");
        for (col = 0; col < COLS; col++) {
            printf("---+");
        }
        printf("\n");
    }
    
    setColor(COLOR_DEFAULT);
    printf("\n");
}

/* Displays the main menu */
void displayMainMenu(void) {
    displayTitle();
    
    setColor(COLOR_GREEN);
    printf("\n  Main Menu:\n");
    setColor(COLOR_DEFAULT);
    printf("  -----------------------\n");
    printf("  1. Player vs Player\n");
    printf("  2. Player vs Computer\n");
    printf("  3. View Statistics\n");
    printf("  4. Exit\n");
    printf("  -----------------------\n");
    printf("\n  Enter your choice (1-4): ");
}

/* Displays difficulty selection menu */
void displayDifficultyMenu(void) {
    displayTitle();
    
    setColor(COLOR_GREEN);
    printf("\n  Select Difficulty:\n");
    setColor(COLOR_DEFAULT);
    printf("  -----------------------\n");
    printf("  1. Easy   - Random moves\n");
    printf("  2. Medium - Smart moves\n");
    printf("  3. Hard   - Expert AI\n");
    printf("  4. Back to Main Menu\n");
    printf("  -----------------------\n");
    printf("\n  Enter your choice (1-4): ");
}

/* Gets valid column input from user */
int getPlayerMove(int board[ROWS][COLS], int player) {
    int col;
    int valid = 0;
    
    while (!valid) {
        if (player == PLAYER1) {
            setColor(COLOR_RED);
            printf("  Player 1 (Red)");
        } else {
            setColor(COLOR_YELLOW);
            printf("  Player 2 (Yellow)");
        }
        setColor(COLOR_DEFAULT);
        printf(" - Enter column (1-7): ");
        
        /* Read integer using scanf with buffer clearing */
        if (readInteger(&col)) {
            col--;  /* Convert to 0-indexed */
            
            if (col >= 0 && col < COLS) {
                if (isValidMove(board, col)) {
                    valid = 1;
                } else {
                    setColor(COLOR_RED);
                    printf("  Column is full! Try another.\n");
                    setColor(COLOR_DEFAULT);
                }
            } else {
                setColor(COLOR_RED);
                printf("  Invalid column! Enter 1-7.\n");
                setColor(COLOR_DEFAULT);
            }
        } else {
            setColor(COLOR_RED);
            printf("  Invalid input! Enter a number 1-7.\n");
            setColor(COLOR_DEFAULT);
        }
    }
    
    return col;
}

/* Displays win message */
void displayWinMessage(int player) {
    printf("\n");
    if (player == PLAYER1) {
        setColor(COLOR_RED);
        printf("  *** PLAYER 1 (RED) WINS! ***\n");
    } else {
        setColor(COLOR_YELLOW);
        printf("  *** PLAYER 2 (YELLOW) WINS! ***\n");
    }
    setColor(COLOR_DEFAULT);
    printf("\n");
}

/* Displays tie message */
void displayTieMessage(void) {
    setColor(COLOR_CYAN);
    printf("\n  *** IT'S A TIE! ***\n\n");
    setColor(COLOR_DEFAULT);
}

/* Waits for user to press Enter */
void waitForEnter(void) {
    printf("  Press Enter to continue...");
    while (getchar() != '\n') {
        /* Wait for Enter key */
    }
}

/* Gets a valid menu choice from user */
int getMenuChoice(int min, int max) {
    int choice;
    
    while (1) {
        if (readInteger(&choice)) {
            if (choice >= min && choice <= max) {
                return choice;
            }
        }
        setColor(COLOR_RED);
        printf("  Invalid choice! Enter %d-%d: ", min, max);
        setColor(COLOR_DEFAULT);
    }
}
