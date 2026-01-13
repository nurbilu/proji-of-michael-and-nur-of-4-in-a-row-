/*
 * stats.c - Game Statistics implementation
 * Handles tracking and storing game statistics
 */

#include <stdio.h>
#include <string.h>
#include "../include/stats.h"
#include "../include/ui.h"

/* Initializes all statistics to zero */
void initStats(GameStats* stats) {
    stats->player1Wins = 0;
    stats->player2Wins = 0;
    stats->computerWins = 0;
    stats->humanWins = 0;
    stats->ties = 0;
    stats->totalGames = 0;
}

/* Updates stats after player vs player game */
void updatePvPStats(GameStats* stats, int winner) {
    stats->totalGames++;
    
    if (winner == 1) {
        stats->player1Wins++;
    } else if (winner == 2) {
        stats->player2Wins++;
    } else {
        stats->ties++;
    }
}

/* Updates stats after player vs computer game */
void updatePvCStats(GameStats* stats, int humanWon) {
    stats->totalGames++;
    
    if (humanWon == 1) {
        stats->humanWins++;
    } else if (humanWon == 0) {
        stats->computerWins++;
    } else {
        stats->ties++;
    }
}

/* Displays all statistics */
void displayStats(GameStats* stats) {
    clearScreen();
    displayTitle();
    
    setColor(COLOR_GREEN);
    printf("\n  Game Statistics:\n");
    setColor(COLOR_DEFAULT);
    printf("  ================================\n");
    printf("  Total Games Played: %d\n", stats->totalGames);
    printf("  --------------------------------\n");
    
    setColor(COLOR_CYAN);
    printf("  Player vs Player:\n");
    setColor(COLOR_DEFAULT);
    printf("    Player 1 Wins: %d\n", stats->player1Wins);
    printf("    Player 2 Wins: %d\n", stats->player2Wins);
    
    setColor(COLOR_CYAN);
    printf("\n  Player vs Computer:\n");
    setColor(COLOR_DEFAULT);
    printf("    Human Wins:    %d\n", stats->humanWins);
    printf("    Computer Wins: %d\n", stats->computerWins);
    
    setColor(COLOR_CYAN);
    printf("\n  Ties: %d\n", stats->ties);
    setColor(COLOR_DEFAULT);
    printf("  ================================\n\n");
}

/* Saves statistics to file */
void saveStats(GameStats* stats, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(stats, sizeof(GameStats), 1, file);
        fclose(file);
    }
}

/* Loads statistics from file */
void loadStats(GameStats* stats, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file != NULL) {
        if (fread(stats, sizeof(GameStats), 1, file) != 1) {
            initStats(stats);  /* Reset if read fails */
        }
        fclose(file);
    } else {
        initStats(stats);  /* Initialize if file doesn't exist */
    }
}
