# DS-LAB---project-2
TETRIS GAME IN C++
=================

This is a simple implementation of the classic Tetris game written in C++.

FEATURES:
--------
- Tetrominoes: Seven different types of Tetrominoes (I, O, T, S, Z, J, L).
- Controls:
  - Arrow keys or WASD to move and rotate the Tetrominoes.
  - Spacebar for hard drop.
  - Option to restart or exit after game over.
- Score System: Keeps track of the current score and high score.
- Line Clearing: Clears full lines and increases the score.
- Colorful Display: Different colors for each Tetromino to enhance the visual experience.

REQUIREMENTS:
-------------
- A Windows operating system (due to the use of Windows-specific libraries like conio.h and windows.h). It can also run on ios and linux by doing some minor changes
- C++ compiler (e.g., GCC, MSVC).
- The game uses basic C++ libraries and Windows API for console manipulation.

CONTROLS:
---------
- Move Left: Press A or Left Arrow key.
- Move Right: Press D or Right Arrow key.
- Move Down: Press S or Down Arrow key.
- Rotate Tetromino: Press W or Up Arrow key.
- Hard Drop: Press the Spacebar.
- Restart Game: After game over, press R to restart.
- Exit Game: After game over, press X to exit.

Color Assignments:
'1' (I shape) → Cyan
'2' (O shape) → Red
'3' (T shape) → Green
'4' (S shape) → Yellow
'5' (Z shape) → Magenta
'6' (J shape) → Blue
'7' (L shape) → Light Cyan

HOW THE GAME WORKS:
-------------------
1. *Tetromino Generation*: New Tetrominoes are randomly generated and fall from the top of the screen.
2. *Movement*: You can move the Tetrominoes left, right, or down. You can also rotate the Tetrominoes.
3. *Collision Detection*: If a Tetromino collides with another block or the bottom of the screen, it is placed on the grid.
4. *Line Clearing*: Full lines are cleared, and the score is incremented by 100 points for each cleared line.
5. *Game Over*: If a new Tetromino cannot be placed at the top due to collisions, the game ends. You can choose to restart or exit.

SAMPLE GAMEPLAY:
----------------
The game will display a grid of 10x20 cells, and each Tetromino shape will fall from the top. You control the movement and rotation of these shapes to fill the empty spaces. Full lines will be cleared automatically.

GAME OVER:
----------
When the game ends, the final score will be displayed along with the highest score achieved in the current session. You can press R to restart or X to exit the game.

