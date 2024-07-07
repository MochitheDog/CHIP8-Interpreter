#include "Chip8.h"
#include <windows.h>
#include <objbase.h> 
#include <shobjidl.h>  
Chip8::Chip8()
{
	memory = std::unique_ptr<Memory>(new Memory);
}

Chip8::~Chip8()
{

}

void Chip8::StartMainLoop()
{
	mainLoop();
}

int Chip8::mainLoop()
{
	return 0;
}

bool Chip8::LoadROMFromFile(const std::string path)
{
	// Remember to initialize the memory
	std::cout << "Loading file: " << path << std::endl;
	std::basic_ifstream<uint8_t> file(path, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		auto sizeOfRom = file.tellg();
		file.seekg(0);
		file.read(&memory->stack[memory->PC], sizeOfRom); // read all characters
	}
	memory->DebugPrintSP();
	// file.close(); // Don't need to close explicitly because of RAII
	return true;
}

std::string Chip8::GetFilePathFromDialog()
{
	// Fug this do this later with vxWidgets or something less annoying to setup
	return "";
}