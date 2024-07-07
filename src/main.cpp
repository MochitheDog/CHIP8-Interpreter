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
    // Window setup stuff
    int windowWidth = 64;
    int windowHeight = 32;
    int scaleFactor = 5;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    window.setSize(sf::Vector2u(windowWidth * scaleFactor, windowHeight * scaleFactor));

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Chip8 chip8;
    bool romLoadSuccess = chip8.LoadROMFromFile("E:/Dev/CHIP8 ROM/IBM Logo.ch8");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
        
    }

    return 0;
}