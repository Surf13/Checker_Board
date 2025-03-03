#include "Game.h"
#include <iostream>
        Game::Game(){ //const std::string &configFile 
            init();
        }

        void Game::init(){ //const std::string &configFile
                d_window.create(sf::VideoMode(800, 600), "Checker Board");
                d_window.setFramerateLimit(59);

}
        

        void Game::pauseGame(){}
        void Game::systemMovement(){}
        void Game::UserInput(){}
        void Game::Capture(){}
    
        void Game::Spawn_Board(){}//int width, int height
        
        void Game::Spawn_Piece(){}
    
    //public:
    
        void Game::run(){
            while (d_window.isOpen())
            {
                // Process events (like closing the window)
                sf::Event event;
                while (d_window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    d_window.close(); // Close the window when the close event is triggered
                }
        
                // Clear the window with a black color
                d_window.clear(sf::Color::Black);
        
                // Display everything that was drawn
                d_window.display();
            }
        }
    
    
    
/*
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
    */