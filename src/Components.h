#include "Vec2.h"
#include <SFML/Graphics.hpp>

#ifndef COMPONENTS_H
#define COMPONENTS_H

class CompTransform
{
//Where Entity Is, How fast its going
};

class CompChecker
{
    sf::CircleShape circle;


};

class CompInput
{
public:
    bool up =false;
    bool down= false;
    bool right = false;
    bool left = false;
};


class Turn
{

    int turn = 1;
    //Player 1 or Player 2
    Turn();

    Turn(int t);

    void switchTurn();

    int getTurn();
};





#endif