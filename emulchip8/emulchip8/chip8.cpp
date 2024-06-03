#pragma warning(disable:4996)

#include "chip8.h"

void Chip8::Initialize()
{
	// Random Initialize
	srand(time(NULL));

	// Reset the status of chip8
	pc = 0x200;
	opcode = 0;
	I = 0;
	sp = 0;

	// Copy Hex Sprite to Interpreter Area
	for (int i = 0; i < 80; i++)
		mem[0x050 + i] = chip8_hex[i];
}

void Chip8::ChipCycle()
{
	// Fetch opcode from [pc], 2bytes
	opcode = mem[pc] << 8 | mem[pc + 1];

	// Decode & Execute
	switch (opcode & 0xF000) {
	case 0x0000:
	{
		switch (opcode & 0x000F) {
		case 0x0000: // 0x00E0 - CLS
		{
			// Clear The Display
			for (int i = 0; i < 64 * 32; i++)
				gfx[i] = 0;
			drawFlag = true;
			pc += 2;
			break;
		}
		case 0x000E: // 0x00EE - RET
		{
			// Return From Subroutine
			sp--;
			pc = stack[sp];
			pc += 2;
			break;
		}
		default: // Unknown
		{
			printf("0x%04X is Unknown Instruction.", opcode);
			break;
		}
		}
		break;
	}
	case 0x1000: // 0x1nnn - JP Addr
	{
		// Jump to Addr
		pc = (opcode & 0x0FFF);
		break;
	}
	case 0x2000: // 0x2nnn - CALL Addr
	{
		// Call to Addr
		stack[sp] = pc;
		sp++;
		pc = (opcode & 0x0FFF);
		break;
	}
	case 0x3000: // 0x3xkk - SE Vx, kk
	{
		// Skip Next Instruction if Vx == kk
		if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
			pc += 4;
		else
			pc += 2;
		break;
	}
	case 0x4000: // 0x4xkk - SNE Vx, kk
	{
		// Skip Next Instruction if Vx != kk
		if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
			pc += 4;
		else
			pc += 2;
		break;
	}
	case 0x5000: // 0x5xy0 - SE Vx, Vy
	{
		// Skip Next Instruction if Vx == Vy
		if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
			pc += 4;
		else
			pc += 2;
		break;
	}
	case 0x6000: // 0x6xkk - LD Vx, kk
	{
		// Vx = kk
		V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
		pc += 2;
		break;
	}
	case 0x7000: // 0x7xkk - ADD Vx, kk
	{
		// Vx = Vx + kk
		V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);
		pc += 2;
		break;
	}
	case 0x8000:
	{
		switch (opcode & 0x000F) {
		case 0x0000: // 0x8xy0 - LD Vx, Vy
		{
			// Vx = Vy
			V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
			pc += 2;
			break;
		}
		case 0x0001: // 0x8xy1 - OR Vx, Vy
		{
			// Vx = Vx | Vy
			V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
			pc += 2;
			break;
		}
		case 0x0002: // 0x8xy2 - AND Vx, Vy
		{
			// Vx = Vx & Vy
			V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];
			pc += 2;
			break;
		}
		case 0x0003: // 0x8xy3 - XOR Vx, Vy
		{
			// Vx = Vx ^ Vy
			V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
			pc += 2;
			break;
		}
		case 0x0004: // 0x8xy4 - ADD Vx, Vy
		{
			// Vx = Vx + Vy, if carry, VF is set to 1. Otherwise 0.
			if (V[(opcode & 0x0F00) >> 8] > (0xFF - V[(opcode & 0x00F0) >> 4]))
				V[0xF] = 1;
			else
				V[0xF] = 0;
			V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
			pc += 2;
			break;
		}
		case 0x0005: // 0x8xy5 - SUB Vx, Vy
		{
			// Vx = Vx - Vy, if Vx > Vy, VF is set to 1. Otherwise 0.
			if (V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8])
				V[0xF] = 0;
			else
				V[0xF] = 1;
			V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
			pc += 2;
			break;
		}
		case 0x0006: // 0x8xy6 - SHR Vx
		{
			// Vx = Vx SHR 1, if LSB of Vx is set to 1, VF is set to 1. Otherwise 0.
			V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
			V[(opcode & 0x0F00) >> 8] >>= 1;
			pc += 2;
			break;
		}
		case 0x0007: // 0x8xy7 - SUBN Vx, Vy
		{
			//  Vx = Vy - Vx, if Vy > Vx, VF is set to 1. Otherwise 0.
			if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4])
				V[0xF] = 0;
			else
				V[0xF] = 1;
			V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
			pc += 2;
			break;
		}
		case 0x000E: // 0x8xyE - SHL Vx
		{
			// Vx = Vx SHL 1, if MSB of Vx is set to 1, VF is set to 1. Otherwise 0.
			V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
			V[(opcode & 0x0F00) >> 8] <<= 1;
			pc += 2;
			break;
		}
		default: // Unknown Instruction
		{
			printf("0x%04X is Unknown Instruction.", opcode);
			break;
		}
		}
		break;
	}
	case 0x9000: // 0x9xy0 - SNE Vx, Vy
	{
		// Skip next instruction if Vx != Vy
		if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
			pc += 4;
		else
			pc += 2;
		break;
	}
	case 0xA000: // 0xAnnn - LD I, Addr
	{
		// I = Addr
		I = (opcode & 0x0FFF);
		pc += 2;
		break;
	}
	case 0xB000: // 0xBnnn - JP V0, addr
	{
		// Jump to addr + v0
		pc = (opcode & 0x0FFF) + V[0];
		break;
	}
	case 0xC000: // 0xCxkk - RND Vx, kk
	{
		// Vx = Rnd AND kk
		V[(opcode & 0x0F00) >> 8] = (rand() % 0xFF) & (opcode & 0x00FF);
		pc += 2;
		break;
	}
	case 0xD000: // 0xDxyn - DRW Vx, Vy, nibble
	{
		// Display n bytes sprite, starting at I, (Vx, Vy), set VF = Collision
		unsigned char vx = V[(opcode & 0x0F00) >> 8];
		unsigned char vy = V[(opcode & 0x00F0) >> 4];
		unsigned char n = (opcode & 0x000F);

		// Clear Collision
		V[0xF] = 0;

		for (int y = 0; y < n; y++)
		{
			unsigned char t = mem[I + y];
			for (int x = 0; x < 0x8; x++)
			{
				if (t & (0x80 >> x)) {
					//Collision Check
					if (gfx[64 * (vy + y) + vx + x] == 1)
						V[0xF] = 1;
					gfx[64 * (vy + y) + vx + x] ^= 1;
				}
			}
		}

		drawFlag = true;
		pc += 2;
		
		break;
	}
	case 0xE000:
	{
		switch (opcode & 0x00FF) {
		case 0x009E: // 0xEx9E - SKP Vx 
		{
			// Skip Next Instruction if Vx == key
			if (key[V[(opcode & 0x0F00) >> 8]] != 0)
				pc += 4;
			else
				pc += 2;
			break;
		}
		case 0x00A1: // 0xExA1 - SKNP Vx
		{
			// Skip Next Instruction if Vx != Key
			if (key[V[(opcode & 0x0F00) >> 8]] == 0)
				pc += 4;
			else
				pc += 2;
			break;
		}
		default: // Unknown Instruction
		{
			printf("0x%04X is Unknown Instruction.", opcode);
			break;
		}
		}
		break;
	}
	case 0xF000:
	{
		switch (opcode & 0x00FF) {
		case 0x0007: // 0xFx07 - LD Vx, DT
		{
			// Vx = Delay Timer
			V[(opcode & 0x0F00) >> 8] = delay_timer;
			pc += 2;
			break;
		}
		case 0x000A: // 0xFx0A - LD Vx, K
		{
			// Waiting for key input, and store in Vx
			bool flag = false;
			for (int i = 0; i < 0x10; i++)
			{
				if (key[i] != 0)
				{
					V[(opcode ^ 0x0F00) >> 8] = i;
					flag = true;
				}
			}

			// if key was not pressed, try next cycle
			if (!flag)
				break;

			pc += 2;
			break;
		}
		case 0x0015: // 0xFx15 - LD DT, Vx
		{
			// Delay Timer = Vx
			delay_timer = V[(opcode & 0x0F00) >> 8];
			pc += 2;
			break;
		}
		case 0x0018: // 0xFx18 - LD ST, Vx
		{
			// Sound Timer = Vx
			sound_timer = V[(opcode & 0x0F00) >> 8];
			pc += 2;
			break;
		}
		case 0x001E: // 0xFx1E - ADD I, Vx
		{
			// I = I + Vx
			if (I + V[(opcode & 0x0F00) >> 8] > 0xFFF)
				V[0xF] = 1;
			else
				V[0xF] = 0;
			I += V[(opcode & 0x0F00) >> 8];
			pc += 2;
			break;
		}
		case 0x0029: // 0xFx29 - LD, F, Vx
		{
			// I = The hex digit corresponding Vx
			I = 0x50 + V[(opcode & 0x0F00) >> 8] * 5;
			pc += 2;
			break;
		}
		case 0x0033: // 0xFx33 - LD B, Vx
		{
			// [I, I+1, I+2] = Vx BCD
			mem[I] = (V[(opcode & 0x0F00) >> 8]) / 100;
			mem[I + 1] = ((V[(opcode & 0x0F00) >> 8]) % 100) / 10;
			mem[I + 2] = (V[(opcode & 0x0F00) >> 8]) % 10;
			pc += 2;
			break;
		}
		case 0x0055: // 0xFx55 - LD [I], Vx
		{
			// I ~ I+0xF = V[0x0-0xF]
			for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++)
				mem[I + i] = V[i];
			I += ((opcode & 0x0F00) >> 8) + 1;
			pc += 2;
			break;
		}
		case 0x0065: // 0xFx65 - LD Vx, [I]
		{
			// V[0x0-0xF] = I ~ I+0xF
			for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++)
				V[i] = mem[I + i];
			I += ((opcode & 0x0F00) >> 8) + 1;
			pc += 2;
			break;
		}
		default: // Unknown Instruction
		{
			printf("0x%04X is Unknown Instruction.", opcode);
			break;
		}
		}
		break;
	}
	default: // Unreachable
	{
		printf("0x%04X is Unknown Instruction.", opcode);
		break;
	}
	}

	if (delay_timer > 0)
		--delay_timer;

	if (sound_timer > 0)
	{
		if (sound_timer == 1)
			//printf("BEEP!\n");
		--sound_timer;
	}
}

bool Chip8::LoadProgram(const char* file)
{
	FILE* fp;
	fp = fopen(file, "rb");
	if (fp == NULL)
		return false;
	
	int i = 0;
	while (!feof(fp)) {
		unsigned char t[0x2];
		fread(t, 1, 1, fp);
		mem[0x200 + i] = t[0];
		i++;
	}

	return true;
}
