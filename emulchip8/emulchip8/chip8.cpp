#include "chip8.h"

void Chip8::Initialize()
{
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

	switch (opcode & 0xF000) {
	case 0x0000:
	{
		switch (opcode & 0x000F) {
		case 0x0000: // 0x00E0 - CLS
		{
			//TODO : Clear The Display
			break;
		}
		case 0x000E: // 0x00EE - RET
		{
			//TODO : Return From Subroutine
			break;
		}
		default: // Unknown
		{
			printf("0x%04X is Unknown Instruction.", opcode);
			break;
		}
		}
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
		// TODO : Skip Next Instruction if Vx == kk
		
		break;
	}
	case 0x4000: // 0x4xkk - SNE Vx, kk
	{
		// TODO : Skip Next Instruction if Vx != kk
		break;
	}
	case 0x5000: // 0x5xy0 - SE Vx, Vy
	{
		// TODO : Skip Next Instruction if Vx == Vy
		break;
	}
	case 0x6000: // 0x6xkk - LD Vx, kk
	{
		// TODO : Vx = kk
		break;
	}
	case 0x7000: // 0x7xkk - ADD Vx, kk
	{
		// TODO : Vx = Vx + kk
		break;
	}
	case 0x8000: 
	{
		switch (opcode & 0x000F) {
		case 0x0000: // 0x8xy0 - LD Vx, Vy
		{
			// TODO : Vx = Vy
			break;
		}
		case 0x0001: // 0x8xy1 - OR Vx, Vy
		{
			// TODO : Vx = Vx | Vy
			break;
		}
		case 0x0002: // 0x8xy2 - AND Vx, Vy
		{
			// TODO : Vx = Vx & Vy
			break;
		}
		case 0x0003: // 0x8xy3 - XOR Vx, Vy
		{
			// TODO : Vx = Vx ^ Vy
			break;
		}
		case 0x0004: // 0x8xy4 - ADD Vx, Vy
		{
			// TODO : Vx = Vx + Vy, if carry, VF is set to 1. Otherwise 0.
			break;
		}
		case 0x0005: // 0x8xy5 - SUB Vx, Vy
		{
			// TODO : Vx = Vx - Vy, if Vx > Vy, VF is set to 1. Otherwise 0.
			break;
		}
		case 0x0006: // 0x8xy6 - SHR Vx
		{
			// TODO : Vx = Vx SHR 1, if LSB of Vx is set to 1, VF is set to 1. Otherwise 0.
			break;
		}
		case 0x0007: // 0x8xy7 - SUBN Vx, Vy
		{
			// TODO : Vx = Vy - Vx, if Vy > Vx, VF is set to 1. Otherwise 0.
			break;
		}
		case 0x000E: // 0x8xyE - SHL Vx
		{
			// TODO : Vx = Vx SHL 1, if MSB of Vx is set to 1, VF is set to 1. Otherwise 0.
			break;
		}
		default: // Unknown Instruction
		{
			printf("0x%04X is Unknown Instruction.", opcode); 
			break;
		}
		}
	}
	case 0x9000: // 0x9xy0 - SNE Vx, Vy
	{
		// TODO : Skip next instruction if Vx != Vy
		break;
	}
	case 0xA000: // 0xAnnn - LD I, Addr
	{
		// TODO : I = Addr
		break;
	}
	case 0xB000: // 0xBnnn - JP V0, addr
	{
		// TODO : Jump to addr + v0
		break;
	}
	case 0xC000: // 0xCxkk - RND Vx, kk
	{
		// TODO : Vx = Rnd AND kk
		break;
	}
	case 0xD000: // 0xDxyn - DRW Vx, Vy, nibble
	{
		// TODO : Display n bytes sprite, starting at I, (Vx, Vy), set VF = Collision
		break;
	}
	case 0xE000:
	{
		switch (opcode & 0x00FF) {
		case 0x009E: // 0xEx9E - SKP Vx 
		{
			// TODO : Skip Next Instruction if Vx == key
			break;
		}
		case 0x00A1: // 0xExA1 - SKNP Vx
		{
			// TODO : Skip Next Instruction if Vx != Key
			break;
		}
		default: // Unknown Instruction
		{
			printf("0x%04X is Unknown Instruction.", opcode);
			break;
		}
		}
	}
	case 0xF000:
	{
		switch (opcode & 0x00FF) {
		case 0x0007: // 0xFx07 - LD Vx, DT
		{
			// TODO : Vx = Delay Timer
			break;
		}
		case 0x000A: // 0xFx0A - LD Vx, K
		{
			// TODO : Waiting for key input, and store in Vx
			break;
		}
		case 0x0015: // 0xFx15 - LD DT, Vx
		{
			// TODO : Delay Timer = Vx
			break;
		case 0x0018: // 0xFx18 - LD ST, Vx
		{
			// TODO : Sound Timer = Vx
			break;
		}
		case 0x001E: // 0xFx1E - ADD I, Vx
		{
			// TODO : I = I + Vx
			break;
		}
		case 0x0029: // 0xFx29 - LD, F, Vx
		{
			// TODO : I = The hex digit corresponding Vx
			break;
		}
		case 0x0033: // 0xFx33 - LD B, Vx
		{
			// TODO : Vx = BCD [I, I+1, I+2]
			break;
		}
		case 0x0055: // 0xFx55 - LD [I], Vx
		{
			// TODO : I ~ I+0xF = V[0x0-0xF]
			break;
		}
		case 0x0065: // 0xFx65 - LD Vx, [I]
		{
			// TODO : V[0x0-0xF] = I ~ I+0xF
			break;
		}
		default: // Unknown Instruction
		{
			printf("0x%04X is Unknown Instruction.", opcode);
			break;
		}
		}
	}
	default: // Unreachable
	{
		printf("0x%04X is Unknown Instruction.", opcode);
		break;
	}
	}
}
