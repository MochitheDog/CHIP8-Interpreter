#include "Chip8.h"
#include <windows.h>
#include <objbase.h> 
#include <shobjidl.h>  
#include <string>
Chip8::Chip8()
{
	memory = std::unique_ptr<Memory>(new Memory);
	window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "SFML works!", sf::Style::Titlebar | sf::Style::Close));
	window->setSize(sf::Vector2u(windowWidth * scaleFactor, windowHeight * scaleFactor));
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	window->clear();
	window->draw(shape);
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

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		
		window->display();
	}
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
	auto ins = Fetch();
	Decode(ins);
	ins = Fetch();


	/*Decode(ins);
	while (memory->PC < memory->stack.size())
	{
		auto ins = Fetch();
		Decode(ins);
	}*/

	// file.close(); // Don't need to close explicitly because of RAII
	return true;
}

std::string Chip8::GetFilePathFromDialog()
{
	// Fug this do this later with vxWidgets or something less annoying to setup
	return "";
}

// Read the instruction that the program counter is pointing at
// and increment the PC
uint16_t Chip8::Fetch()
{
	uint16_t instr = 0x00;
	// Combine two bytes into one 16bit instruction
	instr = (memory->stack[memory->PC] << 8 | memory->stack[memory->PC + 1]<<0);
	//std::cout << std::to_string(memory->stack[memory->PC]) << " " << std::to_string(memory->stack[memory->PC + 1]);
	memory->PC += 2;
	return instr;
}

// Take the instruction from Fetch and figure out what it's supposed to do
void Chip8::Decode(uint16_t instr)
{
	uint8_t bytes[2];
	
	bytes[0] = instr >> 8;
	bytes[1] = instr >> 0;
	std::cout << "Decoding " << HexPrint(bytes[0]) << HexPrint(bytes[1]) << std::endl;
	//CHIP-8 instructions are divided into broad categories by the first “nibble”, or “half-byte”
	// <-- upper bits, --> lower bits
	uint8_t nib1 = (bytes[0] & 0xF0) >> 4;
	switch (nib1)
	{
	case (0x0):
	{
		// 00E0 - CLS - Clear display
		if (bytes[1] == 0xE0)
		{
			CLS();
		}
		else if (bytes[1] == 0xEE)
		{
			RET();
		}
		break;
	}
	case (0x1):
	{
		// 1nnn - JP - Set PC to nnn
		JP(bytes[0] << 8 | bytes[1]);
		break;
	}
	case (0x2):
	{
		CALL(bytes[0] << 8 | bytes[1]);
		break;
	}
	case (0x3):
	{
		SE(bytes[0] << 8, bytes[1]);
		break;
	}
	case (0x4):
	{
		SNE(bytes[0] << 8, bytes[1]);
		break;
	}
	case (0x5):
	{
		break;
	}
	case (0x6):
	{
		break;
	}
	case (0x7):
	{
		break;
	}
	case (0x8):
	{
		break;
	}
	case (0x9):
	{
		break;
	}
	case (0xA):
	{
		break;
	}
	case (0xB):
	{
		break;
	}
	case (0xC):
	{
		break;
	}
	case (0xD):
	{
		break;
	}
	case (0xE):
	{
		break;
	}
	case (0xF):
	{
		break;
	}
	}
}

void Chip8::Execute()
{

}

// Takes a byte
std::string Chip8::HexPrint(uint8_t byte)
{
	uint8_t nibs[2];
	nibs[0] = (byte & 0xF0) >> 4;
	nibs[1] = byte & 0x0F;
	std::string first = "";
	std::string second = "";
	first = NibToString(nibs[0]);
	second = NibToString(nibs[1]);
	return first + second;
}

// Takes a half byte
std::string Chip8::NibToString(uint8_t nib)
{
	switch (nib)
	{
	case (10):
	{
		return "A";
		break;
	}
	case (11):
	{
		return "B";
		break;
	}
	case (12):
	{
		return "C";
		break;
	}
	case (13):
	{
		return "D";
		break;
	}
	case (14):
	{
		return "E";
		break;
	}
	case (15):
	{
		return "F";
		break;
	}
	default:
		return std::to_string(nib);
	}
}

// Clear display
void Chip8::CLS()
{
	std::cout << "Clear window" << std::endl;
	window->clear();
}

// Return from a subroutine.
// The interpreter sets the program counter to the address at the top of the stack,
// then subtracts 1 from the stack pointer.
void Chip8::RET()
{
	memory->PC = memory->stack[memory->SP];
	memory->SP--;
}

// Jump
// Set the program counter to Xnnn
void Chip8::JP(uint16_t addr)
{
	memory->PC = addr;
}

// CALL subroutine at Xnnn
// Increment the stack pointer then put current PC on top of the stack. Then set PC to nnn
void Chip8::CALL(uint16_t addr)
{
	memory->SP++;
	memory->stack[memory->SP] = memory->PC;
	memory->PC = addr;
}

// Skip next instruction if Vx == kk from instr: 3xkk.
void Chip8::SE(uint8_t x, uint8_t byte)
{
	if (memory->V[x] == byte)
	{
		memory->PC += 2;
	}
}

// Skip the next instruction if Vx != kk from instr: 4xkk
void Chip8::SNE(uint8_t x, uint8_t byte)
{
	if (memory->V[x] != byte)
	{
		memory->PC += 2;
	}
}
