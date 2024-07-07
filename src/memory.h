#pragma
#include "Timer.h"

#define PROGRAM_START_ADDRESS 0x200;
#define ETI660_PROGRAM_START_ADDRESS 0x600;

class Memory
{

public:
	Memory();
	~Memory();
	void Initialize();
	void DebugPrintSP();

	std::vector<uint8_t> stack; // array of bytes
	uint8_t SP; // stack pointer
	// Registers
	uint8_t V0,
		V1,
		V2,
		V3,
		V4,
		V5,
		V6,
		V7,
		V8,
		V9,
		VA,
		VB,
		VC,
		VD,
		VE,
		VF = 0x0;
	// Address register
	uint16_t I = 0x00; // Index register
	uint8_t PC = PROGRAM_START_ADDRESS; // Program counter

	//Timer delayTimer;
};