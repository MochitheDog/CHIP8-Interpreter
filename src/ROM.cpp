/**
* File for CHIP-8 ROM input and loading
* Aaron Cheung - 2024
* 
*/

#include <iostream>
#include "ROM.h"


ROM::ROM()
{

};

ROM::~ROM()
{

}

bool ROM::LoadROMFromFile(const std::string path)
{
	std::cout << "Loading file: " << path << std::endl;
	return true;
}