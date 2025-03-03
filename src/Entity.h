#include "Vec2.h"
#include "Components.h"
#include <memory>
#include <string>

#ifndef ENTITY_H
#define ENTITY_H

 COMPONENTS_H
class Entity{
    friend class EntityManager;

    bool active     = true;
    size_t m_id     =0;
    std::string tag = "default";

    Entity();

    Entity(const size_t input_id,const std::string input_tag);
    
public:

};






#endif