#include <cstddef>
#include "Entity.h"

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager{ //Current Entities: white_piece, black_piece, tile

public:
    EntityVec d_entities;
    EntityMap d_entitiesMap; 
    size_t totalEntity = 0;
   
    EntityManager();

    std::shared_ptr<Entity> addEntity(std::string tag);
    
    EntityVec & getEntities();
    
    EntityVec& getEntities(const std::string tag);


};








#endif