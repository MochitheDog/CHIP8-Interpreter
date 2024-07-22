#pragma once
#include <fstream>
#include <iostream>
#include "memory.h"

class Chip8
{
public:
	Chip8();
	~Chip8();
	void StartMainLoop();
	bool LoadROMFromFile(const std::string path);
	std::string GetFilePathFromDialog();
	static std::string HexPrint(uint8_t byte); // debugging

private:
	std::unique_ptr<Memory> memory;
	int mainLoop();
	uint16_t Fetch();
	void Decode(uint16_t instr);
	void Execute();
	static std::string NibToString(uint8_t nib); // debugging
};
