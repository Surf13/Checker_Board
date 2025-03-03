#include "Entity.h"
#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include <string>

#ifndef GAME_H
#define GAME_H
class Game{
public:
    sf::RenderWindow    d_window;
    EntityManager       d_Entities;
    sf::Font            d_Font;
    sf::Text            d_Test;
    int                 turn=1;
    bool                d_paused=false;
    bool                d_running=true;

    Game(); //const std::string &configFile

    void init(); //const std::string &configFile
    void pauseGame();
    void systemMovement();
    void UserInput();
    void Capture();

    void Spawn_Board();

    void Spawn_Piece();

//public:

    void run();



};


#endif