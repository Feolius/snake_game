# Snake Game (C)

A classic terminal Snake game written in C, built with ncurses. This is a study project exploring data structures, memory management, and modular C project layout with CMake.

## Features

- Terminal rendering via `ncurses`
- Game board auto-sized to the terminal (capped at 20x20)
- Score tracking and game-over detection
- Collision detection against walls and the snake's own body
- Food spawning that avoids overlapping the snake

## Architecture

The project is split into independent modules:

- **`src/snake.c/.h`** — Core game logic, free of any UI dependency. The snake is modeled not as a grid of cells, but as a **doubly linked list of straight-line segments**, each with a start point, length, and direction. This makes movement and growth O(1) at the head/tail instead of shifting a full body array.
- **`src/render.c/.h`** — ncurses-based rendering: draws the score bar, board border, snake, and food.
- **`src/log.c/.h`** — Minimal file logger (writes to `log.txt`) used for debugging game state during development.
- **`main.c`** — Entry point: initializes the screen, runs the input/game-tick loop on a fixed tick timer.

```
.
├── main.c              # Entry point / game loop
├── src/
│   ├── snake.c/.h      # Game logic (snake, food, collisions)
│   ├── render.c/.h     # ncurses rendering
│   └── log.c/.h        # Debug file logger
├── tests/
│   └── test_snake.c    # Unit tests (Unity framework)
├── vendor/unity/       # Vendored Unity test framework
└── CMakeLists.txt
```

## Requirements

- CMake
- A C17-capable compiler
- `ncurses` (the build expects it via Homebrew on macOS, e.g. `brew install ncurses`)

## Build & Run

```sh
mkdir build && cd build
cmake ..
cmake --build .
./snake_game
```

## Controls

- **Arrow keys** — change direction
- On game over, press **q** to quit

## Testing

Unit tests use the [Unity](http://www.throwtheswitch.org/unity) test framework (vendored in `vendor/unity`) and cover segment geometry, movement, and food placement.

```sh
cd build
ctest
# or run the test binary directly
./test_snake
```
