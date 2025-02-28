#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create a window with a title "SFML Window" and a size of 800x600 pixels
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(150, 50, 250));
    
    // set a 10-pixel wide orange outline
    shape.setOutlineThickness(10.f);
    shape.setOutlineColor(sf::Color(250, 150, 100));
    // Main game loop (window stays open until user closes it)
    while (window.isOpen())
    {
        // Process events (like closing the window)
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close(); // Close the window when the close event is triggered
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Display everything that was drawn
        window.draw(shape);
        window.display();
    }

    return 0;
}