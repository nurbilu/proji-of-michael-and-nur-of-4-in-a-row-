/*
 * ai.c - Computer AI implementation
 * Handles computer move selection at different difficulty levels
 */

#include <stdlib.h>
#include <time.h>
#include "ai.h"
#include "game.h"

/* Static flag to track if random seed was initialized */
static int randomInitialized = 0;

/* Initializes random seed if not already done */
static void initRandom(void) {
    if (!randomInitialized) {
        srand((unsigned int)time(NULL));
        randomInitialized = 1;
    }
}

/* Returns a random valid column (Easy difficulty) */
int getRandomMove(int board[ROWS][COLS]) {
    int validMoves[COLS];
    int count = 0;
    int col;
    
    initRandom();
    
    /* Find all valid moves */
    for (col = 0; col < COLS; col++) {
        if (isValidMove(board, col)) {
            validMoves[count++] = col;
        }
    }
    
    /* Return random valid move */
    if (count > 0) {
        return validMoves[rand() % count];
    }
    return -1;
}

/* Counts consecutive discs for a player from a position */
static int countDirection(int board[ROWS][COLS], int row, int col, 
                          int dRow, int dCol, int player) {
    int count = 0;
    int r = row + dRow;
    int c = col + dCol;
    
    while (r >= 0 && r < ROWS && c >= 0 && c < COLS && 
           board[r][c] == player) {
        count++;
        r += dRow;
        c += dCol;
    }
    return count;
}

/* Evaluates score for placing disc at position */
static int evaluatePosition(int board[ROWS][COLS], int row, int col, int player) {
    int score = 0;
    int opponent = (player == PLAYER1) ? PLAYER2 : PLAYER1;
    
    /* Check all 4 directions */
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    int i;
    
    for (i = 0; i < 4; i++) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];
        
        int playerCount = countDirection(board, row, col, dRow, dCol, player) +
                          countDirection(board, row, col, -dRow, -dCol, player);
        
        int opponentCount = countDirection(board, row, col, dRow, dCol, opponent) +
                            countDirection(board, row, col, -dRow, -dCol, opponent);
        
        /* Score based on consecutive discs */
        if (playerCount >= 3) score += 100;
        else if (playerCount >= 2) score += 10;
        else if (playerCount >= 1) score += 1;
        
        /* Block opponent's winning moves */
        if (opponentCount >= 3) score += 80;
        else if (opponentCount >= 2) score += 5;
    }
    
    /* Prefer center column */
    if (col == 3) score += 3;
    else if (col == 2 || col == 4) score += 2;
    
    return score;
}

/* Medium AI: checks for wins/blocks, then picks best position */
int getMediumMove(int board[ROWS][COLS], int aiPlayer) {
    int col, row;
    int opponent = (aiPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    int tempBoard[ROWS][COLS];
    int bestCol = -1;
    int bestScore = -1;
    
    initRandom();
    
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
                    int score = evaluatePosition(board, row, col, aiPlayer);
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

/* Minimax score evaluation for a board state */
static int evaluateBoard(int board[ROWS][COLS], int aiPlayer) {
    int opponent = (aiPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    
    if (checkWin(board, aiPlayer)) return 1000;
    if (checkWin(board, opponent)) return -1000;
    
    /* Simple heuristic: count center control */
    int score = 0;
    int row;
    for (row = 0; row < ROWS; row++) {
        if (board[row][3] == aiPlayer) score += 3;
        if (board[row][3] == opponent) score -= 3;
    }
    
    return score;
}

/* Minimax algorithm with alpha-beta pruning */
static int minimax(int board[ROWS][COLS], int depth, int isMaximizing, 
                   int alpha, int beta, int aiPlayer) {
    int opponent = (aiPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    int currentPlayer = isMaximizing ? aiPlayer : opponent;
    
    /* Terminal conditions */
    if (checkWin(board, aiPlayer)) return 1000 - depth;
    if (checkWin(board, opponent)) return -1000 + depth;
    if (isBoardFull(board) || depth >= 6) {
        return evaluateBoard(board, aiPlayer);
    }
    
    int col;
    int tempBoard[ROWS][COLS];
    
    if (isMaximizing) {
        int maxEval = -10000;
        for (col = 0; col < COLS; col++) {
            if (isValidMove(board, col)) {
                copyBoard(tempBoard, board);
                dropDisc(tempBoard, col, currentPlayer);
                int eval = minimax(tempBoard, depth + 1, 0, alpha, beta, aiPlayer);
                if (eval > maxEval) maxEval = eval;
                if (eval > alpha) alpha = eval;
                if (beta <= alpha) break;
            }
        }
        return maxEval;
    } else {
        int minEval = 10000;
        for (col = 0; col < COLS; col++) {
            if (isValidMove(board, col)) {
                copyBoard(tempBoard, board);
                dropDisc(tempBoard, col, currentPlayer);
                int eval = minimax(tempBoard, depth + 1, 1, alpha, beta, aiPlayer);
                if (eval < minEval) minEval = eval;
                if (eval < beta) beta = eval;
                if (beta <= alpha) break;
            }
        }
        return minEval;
    }
}

/* Hard AI: Uses minimax with alpha-beta pruning */
int getHardMove(int board[ROWS][COLS], int aiPlayer) {
    int col;
    int bestCol = 3;  /* Default to center */
    int bestScore = -10000;
    int tempBoard[ROWS][COLS];
    
    /* Check columns in order: center first */
    int order[COLS] = {3, 2, 4, 1, 5, 0, 6};
    int i;
    
    for (i = 0; i < COLS; i++) {
        col = order[i];
        if (isValidMove(board, col)) {
            copyBoard(tempBoard, board);
            dropDisc(tempBoard, col, aiPlayer);
            int score = minimax(tempBoard, 0, 0, -10000, 10000, aiPlayer);
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

