/*
 * stats.h - Game Statistics header
 * Defines statistics tracking and display
 */

#ifndef STATS_H
#define STATS_H

/* Statistics structure */
typedef struct {
    int player1Wins;      /* Wins for player 1 */
    int player2Wins;      /* Wins for player 2 */
    int computerWins;     /* Wins for computer */
    int humanWins;        /* Wins for human vs computer */
    int ties;             /* Total tie games */
    int totalGames;       /* Total games played */
} GameStats;

/* Function declarations */

/* Initializes statistics to zero */
void initStats(GameStats* stats);

/* Updates stats after player vs player game */
void updatePvPStats(GameStats* stats, int winner);

/* Updates stats after player vs computer game */
void updatePvCStats(GameStats* stats, int humanWon);

/* Displays all statistics */
void displayStats(GameStats* stats);

/* Saves statistics to file */
void saveStats(GameStats* stats, const char* filename);

/* Loads statistics from file */
void loadStats(GameStats* stats, const char* filename);

#endif /* STATS_H */

