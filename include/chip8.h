#include <cstdint>
#include <string>

#ifndef CHIP8_H
#define CHIP8_H

#define START_ADDRESS 0x200
#define FONTSET_START_ADDRESS 0x50
#define FONTSET_SIZE 80
#define MEMORY_SIZE 4096
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define SCALE 10
#define SCREEN_WIDTH DISPLAY_WIDTH * SCALE
#define SCREEN_HEIGHT DISPLAY_HEIGHT * SCALE
#define FLAG 15
#define DEBUG 0

static uint8_t font_set[FONTSET_SIZE] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8 {
private:
 // Data Members

	// stack pointer
	uint8_t sp;
	// timer
	uint8_t delay_timer;
	uint8_t sound_timer;
	// CPU registers V0 - VF
	uint8_t regs[16] = {};
	// 4 KB memory map 
	uint8_t memory[MEMORY_SIZE] = {};
	// program counter
	uint16_t pc;
	// current instruction
	uint16_t insn;
	// address register
	uint16_t index;
	// stack
	uint16_t stack[16] = {};


	// Helper Functions
	uint8_t getVX();
	uint8_t getVY();
	uint8_t getByte();
	uint16_t getAddr();

public:
// current state of keys 0x0 - 0xF
uint8_t keyboard[16] = {};
// display
uint32_t display[DISPLAY_WIDTH * DISPLAY_HEIGHT] = {};

// Constructors
	Chip8();

// Opcodes
	void op_0NNN(); /* Execute machine language subroutine at address NNN */
	void op_00E0(); /* Clear the screen */
	void op_00EE(); /* Return from a subroutine */
	void op_1NNN(); /* Jump to address NNN */
	void op_2NNN(); /* Execute subroutine starting at address NNN */
	void op_3XNN(); /* Skip next instruction if VX == NN */
	void op_4XNN(); /* Skip next instruction if VX != NN */
	void op_5XY0(); /* Skip next instruction if VX == VY */
	void op_6XNN(); /* Store NN in VX */
	void op_7XNN(); /* Add NN to VX */
	void op_8XY0(); /* Store VY in VX */
	void op_8XY1(); /* Set VX to VX | VY */
	void op_8XY2(); /* Set VX to VX & VY */
	void op_8XY3(); /* Set VX to VX ^ VY */
	void op_8XY4(); /* Add VY to Vx, VF = carry */
	void op_8XY5(); /* Subtract VY from VX, VF = ~borrow */
	void op_8XY6(); /* Store LSB of VX in VF, then VX << 1 */
	void op_8XY7(); /* Set VX to Vy - VX, VF = ~borrow */
	void op_8XYE(); /* Store MSB of VX in VF, then VX >> 1 */
	void op_9XY0(); /* Skip next instruction if VX != VY */
	void op_ANNN(); /* Set I to adress NNN */
	void op_BNNN(); /* Jump to address V0 + NNN */
	void op_CXNN(); /* Set VX = rand() & NN */
	void op_DXYN(); /* Draw a sprite at (VX, VY) that is 8 * N pixels, 
					 * where every row is read from I, 
					 * VF = if any pixel changed from 1 -> 0*/
	void op_EX9E(); /* Skip next instruction if key == VX */
	void op_EXA1(); /* Skip next instruction if key != VX */
	void op_FX07(); /* Set VX to the value of delay timer*/
	void op_FX0A(); /* Wait from a key press (blocks the program), Vx = key */
	void op_FX15(); /* Set delay timer to VX */
	void op_FX18(); /* Set sound timer to VX */
	void op_FX1E(); /* Add VX to I, VF not affected */
	void op_FX29(); /* Set I to the location of the sprite for the character in VX */
	void op_FX33(); /* Store the digits (starting from MSB) of BCD(VX) 
					 * to location I, I + 1, I + 2*/
	void op_FX55(); /* Stores V0 - VX in memroy starting at address I */
	void op_FX65(); /* Fills V0 - VX with the values starting from address I */

// Methods

	void loadRom(std::string game_name);
	void cycle();
	void exec();
 };

#endif // CHIP8_H