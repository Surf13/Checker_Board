#include "EntityManager.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>


    EntityManager::EntityManager(){}

    std::shared_ptr<Entity> EntityManager::addEntity(const std::string tag){

        std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(totalEntity++,tag);

        std::cout << "Adding Entity: " << tag << std::endl;

        d_entities.push_back(newEntity); //Add to Vector
        d_entitiesMap[tag].push_back(newEntity); //Add to Map

        return newEntity;
    }
    


    EntityVec & EntityManager::getEntities(){
        return d_entities;
    }

    EntityVec& EntityManager::getEntities(const std::string tag){ //Might be wrong
        static EntityVec foundEntities;
        foundEntities.clear();

        for(auto e : d_entities){
            if(e->getTag() == tag){
                foundEntities.push_back(e);
            }
        }
        return foundEntities;
    }

   