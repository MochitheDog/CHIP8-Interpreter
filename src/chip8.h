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
	void JP(uint16_t addr);
	void CALL(uint16_t addr);
	void SE(uint8_t x, uint8_t byte);
	void SNE(uint8_t x, uint8_t byte);
	void SE_xy(uint8_t x, uint8_t y);
	void LD(uint8_t x, uint8_t byte);
	void ADD(uint8_t x, uint8_t byte);
	void LD_xy(uint8_t x, uint8_t y);
	void OR(uint8_t x, uint8_t y);
	void AND(uint8_t x, uint8_t y);
	void XOR(uint8_t x, uint8_t y);
};
