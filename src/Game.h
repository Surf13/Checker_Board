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
    Turn                 turn;
    bool                d_running=true;

    Game(); 

    void init(); //Initalize Board and Spawn Pieces
    void systemMovement(float x_Old, float y_Old, float x_New, float y_New, size_t piece_tag); //Verify Move is allowed
    void UserInput();
    bool Capture(); //Do Actual Capture action
    void Render();
    void Spawn_Board();
    void Spawn_Piece();

//public:

    void run();



};


#endif