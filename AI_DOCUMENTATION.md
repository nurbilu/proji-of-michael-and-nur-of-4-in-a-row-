# AI Tools Usage Documentation

## תיעוד שימוש בכלי AI

This document describes how AI tools were used in the development of this Connect Four project.

---

## כלי AI שבהם נעשה שימוש

### 1. Claude (Cursor IDE)
- **מטרה**: עזרה בתכנון ופיתוח הפרויקט
- **Purpose**: Help with project planning and development

---

## דוגמאות לפניות וקבלת עזרה

### Example 1: Project Structure Planning

**Question asked:**
> "Create a Connect Four game project based on the assignment requirements. Use a simple but effective GUI library. Create proper architectural structure."

**How it helped:**
- Provided a modular file structure (separate .c and .h files)
- Suggested using Windows Console API for colored graphics
- Created organized function declarations and implementations

---

### Example 2: AI Algorithm Implementation

**Question asked:**
> "Implement different difficulty levels for computer opponent"

**How it helped:**
- Easy: Random move selection algorithm
- Medium: Win/block detection + position evaluation
- Hard: Minimax algorithm with alpha-beta pruning

---

### Example 3: Win Detection Logic

**Question asked:**
> "How to check for 4 in a row in all directions?"

**How it helped:**
- Horizontal, vertical, and diagonal checking algorithms
- Optimized loop bounds to avoid out-of-bounds access

---

## חלקים בקוד שנכתבו בעזרת AI

### Parts written with AI assistance:

1. **ai.c - Computer AI Logic**
   - `minimax()` function - Minimax algorithm with alpha-beta pruning
   - `evaluatePosition()` function - Position scoring heuristic
   - `getMediumMove()` function - Smart move selection

2. **game.c - Win Detection**
   - `checkHorizontal()`, `checkVertical()`, `checkDiagonal()` functions
   - Optimized loop boundaries for checking all directions

3. **ui.c - Console Graphics**
   - `setColor()` function - Windows Console API usage
   - `displayBoard()` function - Colored board display

4. **Project Structure**
   - File organization (separate .h and .c files)
   - Header guards and include structure

---

## הבנת הקוד

### Understanding the code:

All code provided by AI was thoroughly reviewed and understood:

1. **Minimax Algorithm**: Recursive algorithm that evaluates all possible game states to find the optimal move. Uses alpha-beta pruning to eliminate unnecessary branches.

2. **Win Detection**: Checks all possible 4-in-a-row combinations by iterating through the board with appropriate bounds.

3. **Console Colors**: Uses Windows `SetConsoleTextAttribute()` function to change text colors.

4. **Modular Design**: Each module handles a specific responsibility (board, game logic, AI, UI, statistics).

---

## הערות נוספות

- All AI-generated code was tested and verified
- Code was modified where needed to fit project requirements
- Comments were added to ensure code readability
- All algorithms are understood and can be explained

---

**Date:** January 2026  
**Course:** Introduction to Computer Science  
**Institution:** Holon Institute of Technology

