#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <windows.h>
#include "chip8.h"

Chip8::Chip8() {
	pc = START_ADDRESS;
	insn = 0;
	index = 0;
	sp = 0;
	delay_timer = 0;
	sound_timer = 0;

	// load font into memory
	for (int i = 0; i < FONTSET_SIZE; i++) {
		memory[FONTSET_START_ADDRESS + i] = font_set[i];
	}

	// random seed based on time
	srand(time(NULL));
}

void Chip8::loadRom(std::string filename) {
	// load file as binary and move file pointer to end
	std::ifstream rom;
	rom.open(filename, std::ios::binary | std::ios::ate);

	if (!rom.is_open()) {
		// file cannot be opened
		std::cerr << "Unable to load game";
		exit(1);
	} else {

		// get file size and create buffer
		std::streamsize size = rom.tellg();

		if (MEMORY_SIZE - START_ADDRESS < size) {
			std::cerr << "ROM too big!";
			exit(1);
		}
		
		char* buffer = new char[size];

		// go to beginning of file and fill buffer
		rom.seekg(0, std::ios::beg);
		rom.read(buffer, size);
		rom.close();

		// write into memory
		for (long i = 0; i < size; i++) {
			memory[START_ADDRESS + i] = buffer[i];
		}

		// release buffer
		delete[] buffer;
	}
}

void Chip8::cycle() {
	// Fetch instruction
	insn = (memory[pc] << 8) | memory[pc + 1];
	if (DEBUG) {
		std::cout << std::hex << insn << " ";
	}

	// Increase program counter
	pc += 2;

	// Execute instruction
	this->exec();

	// Timer countdown
	if (delay_timer > 0) {
		delay_timer--;
	}

	if (sound_timer > 0) {
		if (sound_timer == 1) {
			// Make sound
			Beep(440, 200);
		}
		sound_timer--;
	} 
}

void Chip8::exec() {
	uint8_t msb4 = (insn & 0xF000) >> 12;
	uint8_t lsb4 = insn & 0x000F;
	uint8_t lsb8 = insn & 0x00FF;

	switch (msb4) {
		case 0x0: 
			switch (lsb4) {
				case 0x0: Chip8::op_00E0();
				if (DEBUG) {
					std::cout << "op_00E0\n";
				}
				break;

				case 0xE: Chip8::op_00EE();
				if (DEBUG) {
					std::cout << "op_00EE\n";
				}
				break;
			}
		break;

		case 0x1: Chip8::op_1NNN();
		if (DEBUG) {
			std::cout << "op_1NNN\n";
		}
		break;

		case 0x2: Chip8::op_2NNN();
		if (DEBUG) {
			std::cout << "op_2NNN\n";
		}
		break;

		case 0x3: Chip8::op_3XNN();
		if (DEBUG) {
			std::cout << "op_3XNN\n";
		}
		break;

		case 0x4: Chip8::op_4XNN();
		if (DEBUG) {
			std::cout << "op_4XNN\n";
		}
		break;

		case 0x5: Chip8::op_5XY0();
		if (DEBUG) {
			std::cout << "op_5XY0\n";
		}
		break;

		case 0x6: Chip8::op_6XNN();
		if (DEBUG) {
			std::cout << "op_6XNN\n";
		}
		break;

		case 0x7: Chip8::op_7XNN();
		if (DEBUG) {
			std::cout << "op_7XNN\n";
		}
		break;

		case 0x8:
			switch (lsb4) {
				case 0x0: Chip8::op_8XY0();
				if (DEBUG) {
					std::cout << "op_8XY0\n";
				}
				break;

				case 0x1: Chip8::op_8XY1();
				if (DEBUG) {
					std::cout << "op_8XY1\n";
				}
				break;

				case 0x2: Chip8::op_8XY2();
				if (DEBUG) {
					std::cout << "op_8XY2\n";
				}
				break;

				case 0x3: Chip8::op_8XY3();
				if (DEBUG) {
					std::cout << "op_8XY3\n";
				}
				break;

				case 0x4: Chip8::op_8XY4();
				if (DEBUG) {
					std::cout << "op_8XY4\n";
				}
				break;

				case 0x5: Chip8::op_8XY5();
				if (DEBUG) {
					std::cout << "op_8XY5\n";
				}
				break;

				case 0x6: Chip8::op_8XY6();
				if (DEBUG) {
					std::cout << "op_8XY6\n";
				}
				break;

				case 0x7: Chip8::op_8XY7();
				if (DEBUG) {
					std::cout << "op_8XY7\n";
				}
				break;

				case 0xE: Chip8::op_8XYE();
				if (DEBUG) {
					std::cout << "op_8XYE\n";
				}
				break;
			}
		break;

		case 0x9: Chip8::op_9XY0();
		if (DEBUG) {
			std::cout << "op_9XY0\n";
		}
		break;

		case 0xA: Chip8::op_ANNN();
		if (DEBUG) {
			std::cout << "op_ANNN\n";
		}
		break;

		case 0xB: Chip8::op_BNNN();
		if (DEBUG) {
			std::cout << "op_BNNN\n";
		}
		break;

		case 0xC: Chip8::op_CXNN();
		if (DEBUG) {
			std::cout << "op_CXNN\n";
		}
		break;

		case 0xD: Chip8::op_DXYN();
		if (DEBUG) {
			std::cout << "op_DXYN\n";
		}
		break;

		case 0xE:
			switch (lsb8) {
				case 0xA1: Chip8::op_EXA1();
				if (DEBUG) {
					std::cout << "op_EXA1\n";
				}
				break;

				case 0x9E: Chip8::op_EX9E();
				if (DEBUG) {
					std::cout << "op_EX9E\n";
				}
				break;
			}
		break;

		case 0xF:
			switch (lsb8) {
				case 0x07: Chip8::op_FX07();
				if (DEBUG) {
					std::cout << "op_FX07\n";
				}
				break;

				case 0x0A: Chip8::op_FX0A();
				if (DEBUG) {
					std::cout << "op_FX0A\n";
				}
				break;

				case 0x15: Chip8::op_FX15();
				if (DEBUG) {
					std::cout << "op_FX15\n";
				}
				break;

				case 0x18: Chip8::op_FX18();
				if (DEBUG) {
					std::cout << "op_FX18\n";
				}
				break;

				case 0x1E: Chip8::op_FX1E();
				if (DEBUG) {
					std::cout << "op_FX1E\n";
				}
				break;

				case 0x29: Chip8::op_FX29();
				if (DEBUG) {
					std::cout << "op_FX29\n";
				}
				break;

				case 0x33: Chip8::op_FX33();
				if (DEBUG) {
					std::cout << "op_FX33\n";
				}
				break;

				case 0x55: Chip8::op_FX55();
				if (DEBUG) {
					std::cout << "op_FX55\n";
				}
				break;

				case 0x65: Chip8::op_FX65();
				if (DEBUG) {
					std::cout << "op_FX65\n";
				}
				break;
			}
		break;
	}
}

uint8_t Chip8::getVX() {
	return (insn >> 8) & 0x0F;
}

uint8_t Chip8::getVY() {
	return (insn >> 4) & 0x0F;
}

uint8_t Chip8::getByte() {
	return insn & 0xFF;
}

uint16_t Chip8::getAddr() {
	return insn & 0x0FFF;
}

void Chip8::op_0NNN() {
	/* Execute machine language subroutine at address NNN */
	/* Not applicable for modern machine*/
}

void Chip8::op_00E0() {
	/* Clear the screen */
	memset(display, 0, sizeof(display));
}

void Chip8::op_00EE() {
	/* Return from a subroutine */
	sp--;
	pc = stack[sp];
}

void Chip8::op_1NNN() {
	/* Jump to address NNN */
	pc = this->getAddr();
}

void Chip8::op_2NNN() {
	/* Execute subroutine starting at address NNN */
	stack[sp] = pc;
	sp++;
	pc = this->getAddr();
}

void Chip8::op_3XNN() {
	/* Skip next instruction if VX == NN */
	uint8_t vx = this->getVX();
	uint8_t cond = this->getByte();
	if (regs[vx] == cond) {
		pc += 2;
	}
}

void Chip8::op_4XNN() {
	/* Skip next instruction if VX != NN */
	uint8_t vx = this->getVX();
	uint8_t cond = this->getByte();
	if (regs[vx] != cond) {
		pc += 2;
	}	
}

void Chip8::op_5XY0() {
	/* Skip next instruction if VX == VY */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	if (regs[vx] == regs[vy]) {
		pc += 2;
	}
}

void Chip8::op_6XNN() {
	/* Store NN in VX */
	uint8_t vx = this->getVX();
	regs[vx] = this->getByte();
}

void Chip8::op_7XNN() {
	/* Add NN to VX */
	uint8_t vx = this->getVX();
	regs[vx] += this->getByte();	
}

void Chip8::op_8XY0() {
	/* Store VY in VX */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	regs[vx] = regs[vy];
}

void Chip8::op_8XY1() {
	/* Set VX to VX | VY */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	regs[vx] = regs[vx] | regs[vy];	
}

void Chip8::op_8XY2() {
	/* Set VX to VX & VY */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	regs[vx] = regs[vx] & regs[vy];		
}

void Chip8::op_8XY3() {
	/* Set VX to VX ^ VY */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	regs[vx] = regs[vx] ^ regs[vy];	
}

void Chip8::op_8XY4() {
	/* Add VY to Vx, VF = carry */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	uint16_t res = regs[vx] + regs[vy];
	regs[vx] = res & 0xFF;
	regs[FLAG] = (res >> 8) & 0x01;
}

void Chip8::op_8XY5() {
	/* Subtract VY from VX, VF = !borrow */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	regs[FLAG] = !(regs[vx] < regs[vy]);
	uint16_t res = regs[vx] - regs[vy];
	regs[vx] = res & 0xFF;
}

void Chip8::op_8XY6() {
	/* Store LSB of VX in VF, then VX >> 1 */
	uint8_t vx =this->getVX();
	regs[FLAG] = regs[vx] & 0x01;
	regs[vx] >>= 1;
}

void Chip8::op_8XY7() {
	/* Set VX to Vy - VX, VF = !borrow */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	regs[FLAG] = !(regs[vy] < regs[vx]);
	uint16_t res = regs[vy] - regs[vx];
	regs[vx] = res & 0xFF;
}

void Chip8::op_8XYE() {
	/* Store MSB of VX in VF, then VX << 1 */
	uint8_t vx =this->getVX();
	regs[FLAG] = (regs[vx] & 0x80) >> 7;
	regs[vx] <<= 1;
}

void Chip8::op_9XY0() {
	/* Skip next instruction if VX != VY */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	if (regs[vx] != regs[vy]) {
		pc += 2;
	}
}

void Chip8::op_ANNN() {
	/* Set I to adress NNN */
	index = this->getAddr();
}

void Chip8::op_BNNN() {
	/* Jump to address V0 + NNN */
	pc = regs[0] + this->getAddr();
}

void Chip8::op_CXNN() {
	/* Set VX = rand() & NN */
	uint8_t random = rand() % 256;
	uint8_t vx = this->getVX();
	regs[vx] = random & this->getByte();
}

void Chip8::op_DXYN() {
	/* Draw a sprite at (VX, VY) that is 8 * N pixels, 
	 * where every row is read from I, 
	 * VF = if any pixel changed from 1 -> 0 */
	uint8_t vx = this->getVX();
	uint8_t vy = this->getVY();
	uint8_t height = (insn & 0x000F);

	uint8_t xPos = regs[vx] % DISPLAY_WIDTH;
	uint8_t yPos = regs[vy] % DISPLAY_HEIGHT;

	regs[FLAG] = 0;

	for (int row = 0; row < height; row++) {
		uint8_t spriteByte = memory[index + row];

		for (int col = 0; col < 8; col++) {
			uint8_t spritePixel = spriteByte & (0x80 >> col);
			unsigned int screenIndex = (yPos + row) * DISPLAY_WIDTH + (xPos + col);
			if (screenIndex >= DISPLAY_WIDTH * DISPLAY_HEIGHT) {
				// Wrap around for out of bound writes
				screenIndex %= DISPLAY_WIDTH * DISPLAY_HEIGHT;
			}

			if (spritePixel != 0) {
				regs[FLAG] = display[screenIndex] == 0xFFFFFFFF;
				display[screenIndex] ^= 0xFFFFFFFF;
			}
		}
	}
}

void Chip8::op_EX9E() {
	/* Skip next instruction if key[VX] is pressed */
	uint8_t vx = this->getVX();
	if (keyboard[regs[vx]] != 0) {
		pc += 2;
	}
}

void Chip8::op_EXA1() {
	/* Skip next instruction if key[VX] is not pressed*/
	uint8_t vx = this->getVX();
	if (keyboard[regs[vx]] == 0) {
		pc += 2;
	}
}

void Chip8::op_FX07() {
	/* Set VX to the value of delay timer*/
	uint8_t vx = this->getVX();
	regs[vx] = delay_timer;
}

void Chip8::op_FX0A() {
	/* Wait from a key press (blocks the program), VX = key */
	uint8_t vx = this->getVX();
	bool pressed = false;
	for (uint8_t i = 0; i < 16; i++) {
		if (keyboard[i] != 0) {
			regs[vx] = i;
			pressed = true;
		}
	}

	if (!pressed) {
		pc -= 2;
	}

}

void Chip8::op_FX15() {
	/* Set delay timer to VX */
	uint8_t vx = this->getVX();
	delay_timer = regs[vx];
}

void Chip8::op_FX18() {
	/* Set sound timer to VX */
	uint8_t vx = this->getVX();
	sound_timer = regs[vx];
}

void Chip8::op_FX1E() {
	/* Add VX to I, VF not affected */
	uint8_t vx = this->getVX();
	index += regs[vx];
}

void Chip8::op_FX29() {
	/* Set I to the location of the sprite for the character in VX */
	uint8_t vx = this->getVX();
	index = FONTSET_START_ADDRESS + (5 * regs[vx]);
}

void Chip8::op_FX33() {
	/* Store the digits (starting from MSB) of BCD(VX) 
	 * to location I, I + 1, I + 2*/
	uint8_t vx = this->getVX();
	unsigned int value = regs[vx];
	for (int i = 2; i >= 0; i--) {
		memory[index + i] = value % 10;
		value /= 10;
	}
}

void Chip8::op_FX55() {
	/* Stores V0 - VX in memory starting at address I */
	uint8_t vx = this->getVX();
	for (uint8_t i = 0; i <= vx; i++) {
		memory[index + i] = regs[i];
	}	
}

void Chip8::op_FX65() {
	/* Fills V0 - VX with the values starting from address I */
	uint8_t vx = this->getVX();
	for (uint8_t i = 0; i <= vx; i++) {
		regs[i] = memory[index + i];
	}
}