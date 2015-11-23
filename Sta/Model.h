#ifndef MODEL_H
#define MODEL_H

#include "Entity.h"

class Model
{
private:
    Entity *m_owner;
    sf::Sprite *m_sprite;
public:
    Model(Entity *owner);
    ~Model();
    void draw();
};

#endif
