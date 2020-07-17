# Chip 8 Emulator
A chip 8 emulator that can run basic games like Pong/Space Invader/Tetris etc. 
Check out `https://github.com/dmatlack/chip8` to check for more games(roms) to play
Compiles on Windows. Depends on SDL.

To Run: `./game <rom_name> <delay_time(ms)>`
Make sure the rom file is in `./games`
Every game has their own delay_time for a better gaming experience
Example: 
	- `./game Tetris.ch8 4`
	- `./game Pong.ch8 2`

Prerequisites for Compiling: 
Make sure you have downloaded SDL and put the DLL(32-bit version) in `C:MinGW/bin` to compile