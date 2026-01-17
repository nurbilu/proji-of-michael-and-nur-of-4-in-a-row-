# About Connect Four Game

## General Software Explanation

---

## Overview

This is a Connect Four (4 in a Row) game implemented in C. The game runs in the Windows console with colorful graphics and supports both multiplayer and single-player modes.

---

## Main Functions

### main.c - Entry Point

| Function | Description |
|----------|-------------|
| `main()` | Program entry, runs main menu loop |
| `playPvP()` | Handles player vs player game |
| `playPvC()` | Handles player vs computer game |
| `handlePvCMenu()` | Difficulty selection menu |

### board.c - Board Management

| Function | Description |
|----------|-------------|
| `initBoard()` | Initializes board to empty |
| `isValidMove()` | Checks if column move is valid |
| `dropDisc()` | Drops disc into column |
| `isBoardFull()` | Checks if board is full |
| `copyBoard()` | Creates copy of board |

### game.c - Game Logic

| Function | Description |
|----------|-------------|
| `checkHorizontal()` | Checks 4 in a row horizontally |
| `checkVertical()` | Checks 4 in a row vertically |
| `checkDiagonal()` | Checks 4 in a row diagonally |
| `checkWin()` | Checks if player won |
| `getGameState()` | Returns current game state |

### ai.c - Computer AI

| Function | Description |
|----------|-------------|
| `getRandomMove()` | Returns random valid move (Easy) |
| `getMediumMove()` | Returns smart move (Medium) |
| `getHardMove()` | Returns best move using Minimax (Hard) |
| `getAIMove()` | Main AI function by difficulty |
| `minimaxAlgorithm()` | Minimax algorithm with alpha-beta |
| `calculatePositionScore()` | Calculates score for board position |
| `evaluateBoardState()` | Evaluates overall board state |
| `countDiscsInDirection()` | Counts consecutive discs in direction |

### ui.c - User Interface

| Function | Description |
|----------|-------------|
| `clearScreen()` | Clears console |
| `setColor()` | Sets text color |
| `displayBoard()` | Shows colored game board |
| `displayMainMenu()` | Shows main menu |
| `displayDifficultyMenu()` | Shows difficulty menu |
| `displayTitle()` | Shows game title banner |
| `getPlayerMove()` | Gets valid input from player |
| `getMenuChoice()` | Gets valid menu choice from user |
| `displayWinMessage()` | Shows win message |
| `displayTieMessage()` | Shows tie message |
| `waitForEnter()` | Waits for user to press Enter |

### stats.c - Statistics

| Function | Description |
|----------|-------------|
| `initStats()` | Initializes statistics |
| `updatePvPStats()` | Updates after PvP game |
| `updatePvCStats()` | Updates after PvC game |
| `displayStats()` | Shows all statistics |
| `saveStats()` | Saves stats to file |
| `loadStats()` | Loads stats from file |

---

## Difficulty Levels

### Easy
- Random move selection
- No strategy, just picks any valid column

### Medium
- Checks if can win and takes winning move
- Blocks opponent's winning moves
- Evaluates positions for strategic advantage
- Prefers center columns

### Hard
- Uses Minimax algorithm
- Alpha-beta pruning for efficiency
- Looks ahead multiple moves
- Nearly unbeatable

---

## Data Structures

### Game Board
```c
int board[ROWS][COLS];  // 6x7 2D array
// Values: EMPTY (0), PLAYER1 (1), PLAYER2 (2)
```

### Statistics
```c
typedef struct {
    int player1Wins;
    int player2Wins;
    int computerWins;
    int humanWins;
    int ties;
    int totalGames;
} GameStats;
```

---

## File Persistence

Statistics are saved to `connect4_stats.dat` in binary format.
The file is loaded on program start and saved after each game.

---

**Version:** 1.0  
**Date:** January 2026
