# Othello Game

A console-based implementation of the **Othello** game written in C++.

The game can be played by two players or by one player against the computer.

## Features

- 8×8 Othello board
- Two-player mode
- Single-player mode against the computer
- Three computer difficulty levels:
  - Easy
  - Medium
  - Hard
- Detection of valid moves
- Automatic flipping of captured pieces
- Colored console output
- Game score calculation
- Game start and end time
- Game history saved in a file
- Display of previous game results

## Game Modes

### Two Players

Two players can enter their names and play against each other.

Black always starts the game.

### Player vs Computer

The player plays as **Black** and the computer plays as **White**.

The computer has three difficulty levels:

1. **Easy** – chooses a move with a lower immediate score.
2. **Medium** – chooses a random valid move.
3. **Hard** – chooses a move with a higher immediate score.

## Controls

Use the following keys to move around the board:

| Key | Action |
|-----|--------|
| `W` | Move Up |
| `S` | Move Down |
| `A` | Move Left |
| `D` | Move Right |
| `Enter` | Select a position |

Valid moves are displayed with `*` on the board.

## Game Rules

- The game is played on an 8×8 board.
- Black always moves first.
- A move is valid when it captures one or more opponent pieces.
- Captured pieces are flipped to the current player's color.
- If a player has no valid move, their turn is skipped.
- The game ends when neither player has a valid move.
- The player with the most pieces at the end wins.

## Main Menu

The game contains the following menu options:

```text
1. New Game
2. Load Game
3. Help
4. Game History
5. Exit
```

> **Note:** The Load Game option is currently included in the menu, but loading a saved game has not been implemented yet.

## Game History

After each completed game, information about the game is stored in:

```text
history_file.txt
```

The stored information includes:

- Start date and time
- End date and time
- Final scores
- Winner of the game

Previous game results can be viewed using the **Game History** option from the main menu.




## Compile and Run

Compile:

```bash
g++ "othello(mini project).cpp" -o othello
```

Run:

```bash
./othello
```

On Windows Command Prompt:

```bash
othello.exe
```

## Project Structure

```text
Othello/
│
├── othello(mini project).cpp
├── history_file.txt
└── README.md
```

`history_file.txt` is created when completed game results are saved.

## Author

- [Parmis Jamami](https://github.com/parmis-jamami)
