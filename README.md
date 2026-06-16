# Console Tetris — Low-Level Game Development Basics

A terminal-based Tetris clone written in **plain C++**, with no game engine, no graphics library, and no framework. Everything runs on the Windows console using direct input polling, cursor positioning, and a hand-rolled game loop.

This project is meant as a school project.

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

