#include "Entity.h"
#include <iostream>


Entity::Entity(const size_t input_id, const std::string input_tag)
    : m_id(input_id), tag(input_tag) {}

const std::string& Entity::getTag() const{
    return tag;
}

size_t Entity::id() const{
    return m_id;
};

void Entity::destroy(){
    alive = false;
}

/*
class Checker{

public:
    char color = NULL;
    char type  = NULL;

checker(char col, char type)
    : color(col), type(type){}

char getColor() const{
    return color;
}

char getType() const{
    return type;
}

char Promote(char newType){
    type = newType;
}


};
*/