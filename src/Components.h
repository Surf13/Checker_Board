#include "Vec2.h"
#include <SFML/Graphics.hpp>

#ifndef COMPONENTS_H
#define COMPONENTS_H

class CompTransform
{
//Where Entity Is, How fast its going
public:
    Vec2 pos = {0,0};
public:
    CompTransform(const Vec2 &p): pos(p){}
};

class CompChecker
{
    public:

    sf::CircleShape circle;

    CompChecker(float radius,int point_x,int point_y, const sf::Color & fill, const sf::Color & outline, float thickness);
//Maybe not Set Origin as Position
};

class CompRect{
    public:
    sf::RectangleShape rect;

    CompRect(float width, float height, const sf::Color & fill);

};

class CompCollision{
    public:
        float radious = 0;
        CompCollision(int r): radious(r){}
};

class CompScore{
    int score = 0;
    CompScore(int s): score(s){}
};

class Turn{

    int turn = 1;
    
public:
    //Player 1 or Player 2
    Turn();

    Turn(int t);

    void switchTurn();

    int getTurn();

    std::string getTurnName();
};





#endif