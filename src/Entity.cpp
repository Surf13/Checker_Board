#include "Entity.h"


Entity::Entity(){}

Entity::Entity(const size_t input_id, const std::string input_tag)
    : m_id(input_id), tag(input_tag) {}



/*
he Entity class is the core of the ECS architecture. It represents a game object, which is just a container that associates components together. The entity itself doesn't hold data, it just provides an ID or reference to different components that define the entity’s behavior.

Entity:
Stores a unique ID or handle to identify the entity.
Stores references or pointers to the components that make up the entity (like Position, Piece, etc.).

*/
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