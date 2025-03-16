#include "Entity.h"
#include <iostream>


Entity::Entity(const size_t input_id, const std::string input_tag)
    : m_id(input_id), tag(input_tag) {}

const std::string& Entity::getTag() const{
    return tag;
}

size_t Entity::id() const{
    return m_id;
}

void Entity::destroy(){
    alive = false;
    
    //Clears Pointers using reset function
    compChecker.reset();
    compTransform.reset();
    compRect.reset();
}

bool Entity::operator ==(const std::shared_ptr<Entity>& other){
    return m_id == other->m_id; // or compare other unique attributes like `tag`
}

