/*
 *	Author	: SuperVingo
 *  Created : 2024-05-29
 *	File : chip8.h
 */

#pragma once

#ifndef __CHIP8_H__
#define __CHIP8_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const unsigned char chip8_hex[] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80 // F
};

class Chip8 {
public:
	// 4KB Memory
	/*
	* 0x000 ~ 0x1FF -> Interpreter, Reserved, Hex Font 
	* 0x200 ~ 0xFFF -> Programs, PC will start in 0x200
	*/
	unsigned char mem[4096];

	// General Purpose Registers
	unsigned char V[16];
	// Index Register
	unsigned short I;
	// Program Counter
	unsigned short pc;
	unsigned short opcode;

	// Stack and Stack Pointer
	unsigned short stack[16];
	unsigned short sp;

	// Timer Registers
	unsigned char delay_timer;
	unsigned char sound_timer;

	// Graphics
	unsigned char gfx[64 * 32];
	bool drawFlag;

	//KeyPad
	unsigned char key[16];

public:
	void Initialize();
	void ChipCycle();
	bool LoadProgram(char* file);
};
#endif /*__CHIP8_H__*/