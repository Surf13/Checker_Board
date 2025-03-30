#include "EntityManager.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>


    EntityManager::EntityManager(){}

    std::shared_ptr<Entity> EntityManager::addEntity(const std::string tag){

        std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(totalEntity++,tag);

        d_entities.push_back(newEntity); //Add to Vector
        d_entitiesMap[tag].push_back(newEntity); //Add to Map(Never Used)

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

   
    std::shared_ptr<Entity> EntityManager::getEntity(const size_t id){

        for(auto& e : d_entities){
            if(e->m_id ==id ){
                return e;
            }
        }
        return nullptr;
    }

    void EntityManager::RemoveEntity(std::shared_ptr<Entity> entity){
        auto iter = std::remove(d_entities.begin(),d_entities.end(),entity);
        if(iter != d_entities.end()){
            d_entities.erase(iter, d_entities.end());
            totalEntity--;
            
        }
    }