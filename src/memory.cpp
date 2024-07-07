#include <iostream>
#include "memory.h"

Memory::Memory()
{
	Initialize();
}

Memory::~Memory()
{

}

void Memory::Initialize()
{
	std::cout << "Initializing new memory" << std::endl;
	stack.clear();
	stack.reserve(0xFFF);
	stack.resize(0xFFF);
	SP = 0x0;
	V0 = 0x0;
	V1 = 0x0;
	V2 = 0x0;
	V3 = 0x0;
	V4 = 0x0;
	V5 = 0x0;
	V6 = 0x0;
	V7 = 0x0;
	V8 = 0x0;
	V9 = 0x0;
	VA = 0x0;
	VB = 0x0;
	VC = 0x0;
	VD = 0x0;
	VE = 0x0;
	VF = 0x0;
	I = 0x00;
	PC = PROGRAM_START_ADDRESS;
}

void Memory::DebugPrintSP()
{
	// print 4 bytes from stack
	for (int i = 0; i < 4; i++)
	{
		std::cout << +stack[PC + i] << " "; // The + promotes the uint8_t to int so it can be printed properly
	}
	std::cout << std::endl;
}