# Console Tetris — Low-Level Game Development Basics

A terminal-based Tetris clone written in **plain C++**, with no game engine, no graphics library, and no framework. Everything runs on the Windows console using direct input polling, cursor positioning, and a hand-rolled game loop.

This project is meant as a **hands-on introduction to low-level game development**: how games are structured before engines hide the details.

## Why This Project Exists

Modern engines (Unity, Unreal, Godot) handle rendering, input, timing, and scene management for you. That is great for shipping games, but it makes it hard to see what is actually happening each frame.

This Tetris implementation strips that away. You get:

- A **fixed-timestep game loop** driven by threads
- **Grid-based world state** instead of sprites and transforms
- **Collision detection** written by hand against board cells
- **Input handling** polled directly from the keyboard
- **Rendering** as ASCII characters redrawn every frame
- **Game state machines** for menu, pause, play, and game over

If you want to understand how a game *works* under the hood, this is a solid starting point.

## What You Will Learn

| Concept | How it appears in this project |
|---|---|
| Game loop | Separate threads for render, input, piece movement, and score |
| Fixed frame rate | 12 FPS tick with `std::chrono` sleep intervals |
| Entity representation | Tetromino shapes stored as boolean grids in `piece_list` |
| Collision & bounds | Piece movement checks board cell occupancy before committing |
| Rotation | Four orientation states per piece type, indexed in a lookup map |
| Line clearing | Row scan, gravity shift, combo multiplier |
| State management | Flags for pause, game over, menu requests, and piece spawn timing |
| UI without a UI library | Console cursor positioning and colored text via WinAPI |
| Data structures | `std::vector` board grid, custom template vector experiment |

## Architecture Overview

```
Main.cpp
  └── GameManager          ← orchestrates threads and high-level flow
        ├── MainMenu       ← title screen, scoreboard, theme select
        ├── Board          ← grid state, draw, line clear, hold/preview
        ├── Piece          ← movement, rotation, collision response
        └── PieceList      ← all tetromino shape + rotation definitions
```

### Thread model

During gameplay, five worker threads run in parallel:

1. **RenderGame** — redraws the board, preview, and HUD at ~12 FPS
2. **AddPiece** — spawns new pieces when the active piece locks
3. **MovePiece** — applies gravity on a timer
4. **GameInput** — polls arrow keys, rotation, hold, and pause
5. **ManageScore** — clears lines, updates combo multiplier, checks game over

The main menu uses a similar split between rendering and input threads.

### Board representation

The playfield is a flat `std::vector<position>` where each cell stores an index and occupied flag. Hidden rows above the visible area act as the spawn buffer. Walls and floor are explicit occupied cells.

Pieces are 3×3 boolean masks. On move or rotate, the engine clears old cells, tests the new position, and either commits or rolls back.

## Features

- Classic Tetris-style falling blocks with rotation
- **Hold piece** (Tab)
- **Next piece preview**
- **Combo scoring** — consecutive line clears increase the multiplier
- **Progressive difficulty** — the board shrinks as your score rises
- **Local scoreboard** with player UUID entry
- **Main menu** with theme color selection

## Controls

| Key | Action |
|---|---|
| ← / → | Move piece |
| E | Rotate clockwise |
| Q | Rotate counter-clockwise |
| Tab | Hold / swap piece |
| Esc | Pause → return to menu |
| ↑ / ↓ | Navigate menu |
| Enter | Confirm menu selection |

## Building

**Requirements:** Windows, a C++17 compiler (MSVC or MinGW g++)

### MSVC (Developer Command Prompt)

```bat
cl /EHsc /std:c++17 Main.cpp GameManager.cpp Board.cpp Piece.cpp PieceList.cpp MainMenu.cpp CustomVector.cpp /Fe:tetris.exe
```

### MinGW g++

```bat
g++ -std=c++17 -O2 Main.cpp GameManager.cpp Board.cpp Piece.cpp PieceList.cpp MainMenu.cpp CustomVector.cpp -o tetris.exe
```

Run from a terminal:

```bat
tetris.exe
```

> **Note:** This project uses Windows-specific APIs (`windows.h`, `GetAsyncKeyState`, console handles). It will not compile on Linux/macOS without porting the input and rendering layer.

## Project Structure

```
├── Main.cpp           Entry point
├── GameManager.*      Game loop, threading, score persistence
├── Board.*            Grid logic, rendering, line clear
├── Piece.*            Piece movement and rotation
├── PieceList.*        Tetromino shape definitions (all rotations)
├── MainMenu.*         Menu UI and navigation
└── CustomVector.*     Template vector implementation (experimental)
```

## Design Trade-offs (Intentionally Low-Level)

- **Console rendering** instead of a framebuffer — focuses on update logic, not GPU pipelines
- **Polling input** instead of event callbacks — common in fixed-timestep arcade-style loops
- **Thread-per-subsystem** instead of a single update pass — demonstrates concurrent concerns (sync is minimal here; a learning exercise)
- **Lookup tables for rotations** instead of matrix math — easy to read, easy to debug

These choices prioritize clarity over production polish. A commercial game would unify the loop, add proper synchronization, and separate simulation from presentation — but you would still recognize the same core ideas.

## Possible Next Steps

If you want to extend this as a learning exercise:

- Replace threads with a single game loop and fixed update / render phases
- Add wall kicks and proper SRS rotation
- Serialize the scoreboard to a file
- Port rendering to [raylib](https://www.raylib.com/) or SDL while keeping the same `Board` / `Piece` logic
- Write unit tests for line clearing and collision

## License

This is an educational project. Use and modify it freely for learning and portfolio work.
