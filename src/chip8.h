#pragma once
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
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
	int windowWidth = 64;
	int windowHeight = 32;
	int scaleFactor = 5;

	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Memory> memory;
	int mainLoop();
	uint16_t Fetch();
	void Decode(uint16_t instr);
	void Execute();
	static std::string NibToString(uint8_t nib); // debugging

	void CLS();
	void RET();

};
