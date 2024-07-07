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

private:
	std::unique_ptr<Memory> memory;
	int mainLoop();
};
