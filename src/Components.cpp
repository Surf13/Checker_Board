#include "Vec2.h"
#include <SFML/Graphics.hpp>

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

    Turn(int t): turn(t) {}

    void switchTurn(){
        if(turn==1){
            turn = 2;
        } else {
            turn =1;
        }
    }

    int getTurn(){
        return turn;
    }
};

