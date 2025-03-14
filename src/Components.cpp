#include "Vec2.h"
#include <SFML/Graphics.hpp>
#include "Components.h"




    CompChecker::CompChecker(float radius,int point_x, int point_y, const sf::Color & fill, const sf::Color & outline, float thickness): circle(radius){
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(point_x,point_y);
    }

    CompRect::CompRect(float width, float height, const sf::Color & fill){
        rect.setSize({width,height});
        rect.setFillColor(fill);
    }

    Turn::Turn(): turn(1) {}

    Turn::Turn(int t): turn(t) {}

    void Turn::switchTurn(){
        if(turn==1){
            turn = 2;
        } else {
            turn =1;
        }
    }

    int Turn::getTurn() const{
        return turn;
    }


