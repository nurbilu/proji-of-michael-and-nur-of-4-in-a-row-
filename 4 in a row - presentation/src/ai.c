/*
 * ai.c - Computer AI implementation
 * Handles computer move selection at different difficulty levels
 */

#include <stdlib.h>
#include <time.h>
#include "../include/ai.h"
#include "../include/game.h"

/* Global variable to track if random seed was initialized */
int g_randomInitialized = 0;

/* Initializes random seed (call once at start) */
void initRandomSeed(void) {
    if (g_randomInitialized == 0) {
        srand((unsigned int)time(NULL));
        g_randomInitialized = 1;
    }
}

/* Counts consecutive discs in one direction from a position */
int countDiscsInDirection(int board[ROWS][COLS], int row, int col, 
                          int rowDir, int colDir, int player) {
    int count = 0;
    int r = row + rowDir;
    int c = col + colDir;
    
    while (r >= 0 && r < ROWS && c >= 0 && c < COLS && 
           board[r][c] == player) {
        count++;
        r += rowDir;
        c += colDir;
    }
    return count;
}

/* Calculates a score for placing disc at a position */
int calculatePositionScore(int board[ROWS][COLS], int row, int col, int player) {
    int score = 0;
    int opponent;
    int i;
    int rowDir, colDir;
    int playerCount, opponentCount;
    
    /* Determine opponent */
    if (player == PLAYER1) {
        opponent = PLAYER2;
    } else {
        opponent = PLAYER1;
    }
    
    /* Check all 4 directions: horizontal, vertical, diagonal-right, diagonal-left */
    /* Direction pairs: (rowDir, colDir) */
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    
    for (i = 0; i < 4; i++) {
        rowDir = directions[i][0];
        colDir = directions[i][1];
        
        /* Count player discs in both directions */
        playerCount = countDiscsInDirection(board, row, col, rowDir, colDir, player) +
                      countDiscsInDirection(board, row, col, -rowDir, -colDir, player);
        
        /* Count opponent discs in both directions */
        opponentCount = countDiscsInDirection(board, row, col, rowDir, colDir, opponent) +
                        countDiscsInDirection(board, row, col, -rowDir, -colDir, opponent);
        
        /* Add score based on consecutive discs */
        if (playerCount >= 3) {
            score = score + 100;
        } else if (playerCount >= 2) {
            score = score + 10;
        } else if (playerCount >= 1) {
            score = score + 1;
        }
        
        /* Add score for blocking opponent */
        if (opponentCount >= 3) {
            score = score + 80;
        } else if (opponentCount >= 2) {
            score = score + 5;
        }
    }
    
    /* Prefer center column */
    if (col == 3) {
        score = score + 3;
    } else if (col == 2 || col == 4) {
        score = score + 2;
    }
    
    return score;
}

/* Evaluates the board state and returns a score */
int evaluateBoardState(int board[ROWS][COLS], int aiPlayer) {
    int opponent;
    int score = 0;
    int row;
    
    if (aiPlayer == PLAYER1) {
        opponent = PLAYER2;
    } else {
        opponent = PLAYER1;
    }
    
    /* Check for wins */
    if (checkWin(board, aiPlayer)) {
        return 1000;
    }
    if (checkWin(board, opponent)) {
        return -1000;
    }
    
    /* Simple heuristic: count center column control */
    for (row = 0; row < ROWS; row++) {
        if (board[row][3] == aiPlayer) {
            score = score + 3;
        }
        if (board[row][3] == opponent) {
            score = score - 3;
        }
    }
    
    return score;
}

/* Minimax algorithm with alpha-beta pruning for Hard difficulty */
int minimaxAlgorithm(int board[ROWS][COLS], int depth, int isMaximizing, 
                     int alpha, int beta, int aiPlayer) {
    int opponent;
    int currentPlayer;
    int col;
    int tempBoard[ROWS][COLS];
    int eval;
    int maxEval, minEval;
    
    /* Determine opponent */
    if (aiPlayer == PLAYER1) {
        opponent = PLAYER2;
    } else {
        opponent = PLAYER1;
    }
    
    /* Determine current player */
    if (isMaximizing) {
        currentPlayer = aiPlayer;
    } else {
        currentPlayer = opponent;
    }
    
    /* Terminal conditions - check for win, loss, or max depth */
    if (checkWin(board, aiPlayer)) {
        return 1000 - depth;
    }
    if (checkWin(board, opponent)) {
        return -1000 + depth;
    }
    if (isBoardFull(board) || depth >= 6) {
        return evaluateBoardState(board, aiPlayer);
    }
    
    if (isMaximizing) {
        maxEval = -10000;
        for (col = 0; col < COLS; col++) {
            if (isValidMove(board, col)) {
                copyBoard(tempBoard, board);
                dropDisc(tempBoard, col, currentPlayer);
                eval = minimaxAlgorithm(tempBoard, depth + 1, 0, alpha, beta, aiPlayer);
                if (eval > maxEval) {
                    maxEval = eval;
                }
                if (eval > alpha) {
                    alpha = eval;
                }
                if (beta <= alpha) {
                    break;  /* Alpha-beta pruning */
                }
            }
        }
        return maxEval;
    } else {
        minEval = 10000;
        for (col = 0; col < COLS; col++) {
            if (isValidMove(board, col)) {
                copyBoard(tempBoard, board);
                dropDisc(tempBoard, col, currentPlayer);
                eval = minimaxAlgorithm(tempBoard, depth + 1, 1, alpha, beta, aiPlayer);
                if (eval < minEval) {
                    minEval = eval;
                }
                if (eval < beta) {
                    beta = eval;
                }
                if (beta <= alpha) {
                    break;  /* Alpha-beta pruning */
                }
            }
        }
        return minEval;
    }
}

/* Returns a random valid column (Easy difficulty) */
int getRandomMove(int board[ROWS][COLS]) {
    int validMoves[COLS];
    int count = 0;
    int col;
    int randomIndex;
    
    initRandomSeed();
    
    /* Find all valid moves */
    for (col = 0; col < COLS; col++) {
        if (isValidMove(board, col)) {
            validMoves[count] = col;
            count++;
        }
    }
    
    /* Return random valid move */
    if (count > 0) {
        randomIndex = rand() % count;
        return validMoves[randomIndex];
    }
    return -1;
}

/* Medium AI: checks for wins/blocks, then picks best position */
int getMediumMove(int board[ROWS][COLS], int aiPlayer) {
    int col, row;
    int opponent;
    int tempBoard[ROWS][COLS];
    int bestCol = -1;
    int bestScore = -1;
    int score;
    
    initRandomSeed();
    
    /* Determine opponent */
    if (aiPlayer == PLAYER1) {
        opponent = PLAYER2;
    } else {
        opponent = PLAYER1;
    }
    
    /* First: Check if AI can win */
    for (col = 0; col < COLS; col++) {
        if (isValidMove(board, col)) {
            copyBoard(tempBoard, board);
            dropDisc(tempBoard, col, aiPlayer);
            if (checkWin(tempBoard, aiPlayer)) {
                return col;
            }
        }
    }
    
    /* Second: Block opponent's winning move */
    for (col = 0; col < COLS; col++) {
        if (isValidMove(board, col)) {
            copyBoard(tempBoard, board);
            dropDisc(tempBoard, col, opponent);
            if (checkWin(tempBoard, opponent)) {
                return col;
            }
        }
    }
    
    /* Third: Evaluate each position and pick best */
    for (col = 0; col < COLS; col++) {
        if (isValidMove(board, col)) {
            /* Find where disc would land */
            for (row = ROWS - 1; row >= 0; row--) {
                if (board[row][col] == EMPTY) {
                    score = calculatePositionScore(board, row, col, aiPlayer);
                    if (score > bestScore) {
                        bestScore = score;
                        bestCol = col;
                    }
                    break;
                }
            }
        }
    }
    
    /* If no good move found, pick random */
    if (bestCol == -1) {
        return getRandomMove(board);
    }
    
    return bestCol;
}

/* Hard AI: Uses minimax with alpha-beta pruning */
int getHardMove(int board[ROWS][COLS], int aiPlayer) {
    int col;
    int bestCol = 3;  /* Default to center */
    int bestScore = -10000;
    int tempBoard[ROWS][COLS];
    int score;
    int i;
    
    /* Check columns in order: center first */
    int columnOrder[COLS] = {3, 2, 4, 1, 5, 0, 6};
    
    for (i = 0; i < COLS; i++) {
        col = columnOrder[i];
        if (isValidMove(board, col)) {
            copyBoard(tempBoard, board);
            dropDisc(tempBoard, col, aiPlayer);
            score = minimaxAlgorithm(tempBoard, 0, 0, -10000, 10000, aiPlayer);
            if (score > bestScore) {
                bestScore = score;
                bestCol = col;
            }
        }
    }
    
    return bestCol;
}

/* Main AI function: selects move based on difficulty level */
int getAIMove(int board[ROWS][COLS], int difficulty, int aiPlayer) {
    switch (difficulty) {
        case EASY:
            return getRandomMove(board);
        case MEDIUM:
            return getMediumMove(board, aiPlayer);
        case HARD:
            return getHardMove(board, aiPlayer);
        default:
            return getRandomMove(board);
    }
}
