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
    EntityManager       d_BoardTiles;
    int                 turn=1;
    bool                d_running=true;

    Game(); 

    void init(); //Initalize Board and Spawn Pieces
    bool systemMovement(float x_Old, float y_Old, float x_New, float y_New, std::string piece_tag); //Verify Move is allowed
    void UserInput();
    void Capture(); //Do Actual Capture action
    void Render();
    void Spawn_Board();
    void Spawn_Piece();

//public:

    void run();



};


#endif