/*
 * main.c - Connect Four Game Entry Point
 * Main menu and game loop implementation
 * 
 * Course: Introduction to Computer Science
 * Assignment: Final Project - Connect Four (4 in a Row)
 */

#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "game.h"
#include "ai.h"
#include "ui.h"
#include "stats.h"

#define STATS_FILE "connect4_stats.dat"

/* Runs a Player vs Player game */
void playPvP(GameStats* stats) {
    int board[ROWS][COLS];
    int currentPlayer = PLAYER1;
    int gameState = GAME_ONGOING;
    int col;
    
    initBoard(board);
    
    /* Main game loop */
    while (gameState == GAME_ONGOING) {
        clearScreen();
        displayTitle();
        displayBoard(board);
        
        /* Get player move */
        col = getPlayerMove(board, currentPlayer);
        dropDisc(board, col, currentPlayer);
        
        /* Check game state */
        gameState = getGameState(board, currentPlayer);
        
        /* Switch player if game continues */
        if (gameState == GAME_ONGOING) {
            currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
        }
    }
    
    /* Display final board and result */
    clearScreen();
    displayTitle();
    displayBoard(board);
    
    if (gameState == GAME_WIN) {
        displayWinMessage(currentPlayer);
        updatePvPStats(stats, currentPlayer);
    } else {
        displayTieMessage();
        updatePvPStats(stats, 0);
    }
    
    saveStats(stats, STATS_FILE);
    waitForEnter();
}

/* Runs a Player vs Computer game */
void playPvC(GameStats* stats, int difficulty) {
    int board[ROWS][COLS];
    int currentPlayer = PLAYER1;  /* Human is Player 1 */
    int gameState = GAME_ONGOING;
    int col;
    
    initBoard(board);
    
    /* Main game loop */
    while (gameState == GAME_ONGOING) {
        clearScreen();
        displayTitle();
        
        /* Show difficulty level */
        setColor(COLOR_GREEN);
        printf("  Difficulty: ");
        if (difficulty == EASY) printf("Easy\n");
        else if (difficulty == MEDIUM) printf("Medium\n");
        else printf("Hard\n");
        setColor(COLOR_DEFAULT);
        
        displayBoard(board);
        
        if (currentPlayer == PLAYER1) {
            /* Human's turn */
            col = getPlayerMove(board, currentPlayer);
        } else {
            /* Computer's turn */
            setColor(COLOR_YELLOW);
            printf("  Computer is thinking...\n");
            setColor(COLOR_DEFAULT);
            col = getAIMove(board, difficulty, PLAYER2);
            printf("  Computer chose column %d\n", col + 1);
        }
        
        dropDisc(board, col, currentPlayer);
        
        /* Check game state */
        gameState = getGameState(board, currentPlayer);
        
        /* Switch player if game continues */
        if (gameState == GAME_ONGOING) {
            currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
        }
    }
    
    /* Display final board and result */
    clearScreen();
    displayTitle();
    displayBoard(board);
    
    if (gameState == GAME_WIN) {
        if (currentPlayer == PLAYER1) {
            setColor(COLOR_GREEN);
            printf("\n  *** YOU WIN! ***\n\n");
            setColor(COLOR_DEFAULT);
            updatePvCStats(stats, 1);
        } else {
            setColor(COLOR_RED);
            printf("\n  *** COMPUTER WINS! ***\n\n");
            setColor(COLOR_DEFAULT);
            updatePvCStats(stats, 0);
        }
    } else {
        displayTieMessage();
        updatePvCStats(stats, -1);
    }
    
    saveStats(stats, STATS_FILE);
    waitForEnter();
}

/* Handles Player vs Computer menu and game start */
void handlePvCMenu(GameStats* stats) {
    int choice;
    int playing = 1;
    
    while (playing) {
        clearScreen();
        displayDifficultyMenu();
        choice = getMenuChoice(1, 4);
        
        switch (choice) {
            case 1:
                playPvC(stats, EASY);
                break;
            case 2:
                playPvC(stats, MEDIUM);
                break;
            case 3:
                playPvC(stats, HARD);
                break;
            case 4:
                playing = 0;
                break;
        }
    }
}

/* Main function - program entry point */
int main(void) {
    GameStats stats;
    int choice;
    int running = 1;
    
    /* Load saved statistics */
    loadStats(&stats, STATS_FILE);
    
    /* Main menu loop */
    while (running) {
        clearScreen();
        displayMainMenu();
        choice = getMenuChoice(1, 4);
        
        switch (choice) {
            case 1:
                /* Player vs Player */
                playPvP(&stats);
                break;
            case 2:
                /* Player vs Computer */
                handlePvCMenu(&stats);
                break;
            case 3:
                /* View Statistics */
                displayStats(&stats);
                waitForEnter();
                break;
            case 4:
                /* Exit */
                clearScreen();
                displayTitle();
                setColor(COLOR_GREEN);
                printf("\n  Thank you for playing!\n");
                printf("  Goodbye!\n\n");
                setColor(COLOR_DEFAULT);
                running = 0;
                break;
        }
    }
    
    return 0;
}

