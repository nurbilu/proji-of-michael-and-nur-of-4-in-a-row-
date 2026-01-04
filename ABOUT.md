# About Connect Four Game

## הסבר כללי על התוכנה

---

## Overview / סקירה כללית

This is a Connect Four (4 in a Row) game implemented in C. The game runs in the Windows console with colorful graphics and supports both multiplayer and single-player modes.

משחק "ארבע בשורה" ממומש בשפת C. המשחק רץ בקונסולה של Windows עם גרפיקה צבעונית ותומך במשחק רב-משתתפים ויחיד.

---

## Main Functions / פונקציות עיקריות

### main.c - Entry Point

| Function | Description | תיאור |
|----------|-------------|--------|
| `main()` | Program entry, runs main menu loop | נקודת כניסה, מריץ לולאת תפריט ראשי |
| `playPvP()` | Handles player vs player game | מנהל משחק שחקן נגד שחקן |
| `playPvC()` | Handles player vs computer game | מנהל משחק שחקן נגד מחשב |
| `handlePvCMenu()` | Difficulty selection menu | תפריט בחירת רמת קושי |

### board.c - Board Management

| Function | Description | תיאור |
|----------|-------------|--------|
| `initBoard()` | Initializes board to empty | מאתחל לוח ריק |
| `isValidMove()` | Checks if column move is valid | בודק אם המהלך חוקי |
| `dropDisc()` | Drops disc into column | מטיל דסקית לעמודה |
| `isBoardFull()` | Checks if board is full | בודק אם הלוח מלא |
| `copyBoard()` | Creates copy of board | יוצר עותק של הלוח |

### game.c - Game Logic

| Function | Description | תיאור |
|----------|-------------|--------|
| `checkHorizontal()` | Checks 4 in a row horizontally | בודק 4 בשורה אופקית |
| `checkVertical()` | Checks 4 in a row vertically | בודק 4 בשורה אנכית |
| `checkDiagonal()` | Checks 4 in a row diagonally | בודק 4 בשורה אלכסונית |
| `checkWin()` | Checks if player won | בודק אם שחקן ניצח |
| `getGameState()` | Returns current game state | מחזיר מצב משחק נוכחי |

### ai.c - Computer AI

| Function | Description | תיאור |
|----------|-------------|--------|
| `getRandomMove()` | Returns random valid move (Easy) | מהלך אקראי (קל) |
| `getMediumMove()` | Returns smart move (Medium) | מהלך חכם (בינוני) |
| `getHardMove()` | Returns best move using Minimax (Hard) | מהלך מיטבי עם Minimax (קשה) |
| `getAIMove()` | Main AI function by difficulty | פונקציית AI ראשית לפי קושי |
| `minimax()` | Minimax algorithm with alpha-beta | אלגוריתם מינימקס |

### ui.c - User Interface

| Function | Description | תיאור |
|----------|-------------|--------|
| `clearScreen()` | Clears console | מנקה מסך |
| `setColor()` | Sets text color | קובע צבע טקסט |
| `displayBoard()` | Shows colored game board | מציג לוח משחק צבעוני |
| `displayMainMenu()` | Shows main menu | מציג תפריט ראשי |
| `displayDifficultyMenu()` | Shows difficulty menu | מציג תפריט קושי |
| `getPlayerMove()` | Gets valid input from player | מקבל קלט חוקי משחקן |
| `displayWinMessage()` | Shows win message | מציג הודעת ניצחון |
| `displayTieMessage()` | Shows tie message | מציג הודעת תיקו |

### stats.c - Statistics

| Function | Description | תיאור |
|----------|-------------|--------|
| `initStats()` | Initializes statistics | מאתחל סטטיסטיקות |
| `updatePvPStats()` | Updates after PvP game | מעדכן אחרי משחק שחקן-שחקן |
| `updatePvCStats()` | Updates after PvC game | מעדכן אחרי משחק שחקן-מחשב |
| `displayStats()` | Shows all statistics | מציג כל הסטטיסטיקות |
| `saveStats()` | Saves stats to file | שומר סטטיסטיקות לקובץ |
| `loadStats()` | Loads stats from file | טוען סטטיסטיקות מקובץ |

---

## Difficulty Levels / רמות קושי

### Easy (קל)
- Random move selection
- No strategy, just picks any valid column
- בחירת מהלך אקראית, ללא אסטרטגיה

### Medium (בינוני)
- Checks if can win and takes winning move
- Blocks opponent's winning moves
- Evaluates positions for strategic advantage
- Prefers center columns
- בודק ניצחון אפשרי, חוסם יריב, מעריך עמדות

### Hard (קשה)
- Uses Minimax algorithm
- Alpha-beta pruning for efficiency
- Looks ahead multiple moves
- Nearly unbeatable
- משתמש באלגוריתם Minimax עם אלפא-בטא

---

## Data Structures / מבני נתונים

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

## File Persistence / שמירת נתונים

Statistics are saved to `connect4_stats.dat` in binary format.
The file is loaded on program start and saved after each game.

---

## Technical Notes / הערות טכניות

- Uses Windows Console API for colored output
- Safe input handling with `fgets()` and `sscanf()`
- Modular code structure for maintainability
- All functions have clear single responsibilities

---

**Version:** 1.0  
**Date:** January 2026

