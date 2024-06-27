/**
* CHIP-8 Interpreter entry file
* Using SFML for graphics and audio
* 
* Aaron Cheung - 2024
*/

#include <memory>
#include "ROM.h"
#include <SFML/Graphics.hpp>


int main()
{
    int windowWidth = 64;
    int windowHeight = 32;
    int scaleFactor = 5;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    window.setSize(sf::Vector2u(windowWidth * scaleFactor, windowHeight * scaleFactor));

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    bool romLoadSuccess = false;

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
        
        if (!romLoadSuccess)
        {
            std::unique_ptr<ROM> rom = std::unique_ptr<ROM>(new ROM());
            romLoadSuccess = rom->LoadROMFromFile("E:/Dev/CHIP8 ROM/IBM Logo.ch8");
        }
    }

    return 0;
}