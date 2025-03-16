#include "Vec2.h"
#include "Components.h"
#include <memory>
#include <string>

#ifndef ENTITY_H
#define ENTITY_H

 COMPONENTS_H
class Entity{
    friend class EntityManager;
public:
    bool alive     = true;
    size_t m_id     =0;
    std::string tag = "default";

public:

    Entity(const size_t input_id,const std::string input_tag);
        

public:
    std::shared_ptr<CompTransform> compTransform;
    std::shared_ptr<CompChecker>   compChecker;
    std::shared_ptr<CompRect>      compRect;


    bool isAlive() const;
    const std::string & getTag() const;
    size_t id() const;

    void destroy();

    bool operator ==(const std::shared_ptr<Entity>& other);

};






#endif