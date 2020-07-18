# Chip 8 Emulator
A chip 8 emulator that can run basic games like Pong/Space Invader/Tetris etc.\
Check out `https://github.com/dmatlack/chip8` to check for more games(roms) to play\
Compiles on Windows. Depends on SDL.

To Run: `./game <rom_name> <delay_time(ms)>`\
Make sure the rom file is in `./games`\
Every game has their own delay_time for a better gaming experience\
Example: \
	- `./game Tetris.ch8 4`\
	- `./game Pong.ch8 2`

Keyboard layout is as follow:

Keypad on Chip8:
| 1 | 2 | 3 | C |
|---|---|---|---|
| 4 | 5 | 6 | D |
| 7 | 8 | 9 | E |
| A | 0 | B | F |


KeyBoard:
| 1 | 2 | 3 | 4 |
|---|---|---|---|
| Q | W | E | R |
| A | S | D | F |
| Z | X | C | V |

Gameplay:\
Pong: `1 = up`, `Q = down`\
Tetris: `W = left`, `E = right`, `Q = rotate`, `A = down`

Prerequisites for Compiling:\
Make sure you have downloaded SDL and put the DLL(32-bit version) in `C:MinGW/bin` to compile
