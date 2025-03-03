#include <cstddef>
#include "Entity.h"

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

class EntityManager{

public:
    size_t totalEntity = 0;
   
    EntityManager();

    std::shared_ptr<Entity> addEntity(std::string tag);
    
    
};








#endif