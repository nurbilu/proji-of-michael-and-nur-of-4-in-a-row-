# Connect Four - 4 in a Row Game

## Project Description

A console-based Connect Four game developed in C for the Introduction to Computer Science course. The game features colorful graphics in the Windows console, multiple game modes, and AI opponents with varying difficulty levels.

## Features

- **Player vs Player Mode**: Two players take turns on the same computer
- **Player vs Computer Mode**: Play against the AI with 3 difficulty levels:
  - Easy: Random moves
  - Medium: Smart defensive/offensive moves
  - Hard: Advanced AI using Minimax algorithm
- **Game Statistics**: Track wins, losses, and ties
- **Colorful UI**: Colored console graphics for better experience

## Project Structure

```
4 in a row - dev code/
├── main.c          # Entry point and main menu
├── board.c/.h      # Board operations and management
├── game.c/.h       # Game logic and win detection
├── ai.c/.h         # Computer AI implementation
├── ui.c/.h         # User interface and display
├── stats.c/.h      # Statistics tracking
├── README.md       # This file
├── AI_DOCUMENTATION.md  # AI tool usage documentation
└── ABOUT.md        # General software explanation
```

## How to Compile

### Using Visual Studio

1. Open Visual Studio
2. Create a new Empty Project (C++)
3. Add all `.c` and `.h` files to the project
4. Build the solution (Ctrl+Shift+B)
5. Run the program (F5)

### Using Command Line (GCC)

```bash
gcc -o connect4.exe main.c board.c game.c ai.c ui.c stats.c
```

## How to Play

1. Run the program
2. Select from the main menu:
   - 1: Player vs Player
   - 2: Player vs Computer
   - 3: View Statistics
   - 4: Exit
3. In game, enter column number (1-7) to drop your disc
4. First player to get 4 in a row wins!

## Game Rules

- The board is 7 columns x 6 rows
- Players take turns dropping colored discs
- Discs fall to the lowest available position
- Win by connecting 4 discs horizontally, vertically, or diagonally
- Game is a tie if board fills with no winner

## Requirements

- Windows OS (uses Windows Console API for colors)
- C compiler (Visual Studio or GCC)

## Authors

[Student Names Here]

## Course

Introduction to Computer Science - Fall 2025
Holon Institute of Technology

