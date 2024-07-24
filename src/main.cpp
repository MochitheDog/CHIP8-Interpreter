/**
* CHIP-8 Chip8 entry file
* Using SFML for graphics and audio
* 
* Aaron Cheung - 2024
*/

#include <memory>
#include <SFML/Graphics.hpp>
#include "chip8.h"

int main()
{
    Chip8 chip8;
    bool romLoadSuccess = chip8.LoadROMFromFile("E:/Dev/CHIP8 ROM/IBM Logo.ch8");
    chip8.StartMainLoop();

    return 0;
}