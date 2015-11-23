#ifndef RENDERENTITY_H
#define RENDERENTITY_H

#include <iostream>

#include <SFML/Window.hpp>

#include "Render.h"
#include "Entity.h"

#include "RenderEffect.h"

class EntityPlayer;
class EasyEnemy;
class MediumEnemy;
class HardEnemy;

class RenderEntity : public Render
{
private:
    //Entité associée au render
    Entity *m_entity;

public:
    RenderEntity(Entity *entity);

    /** \brief draw
     * Dessine le render
     * \param window sf::RenderWindow*
     * \return void
     *
     */
    void draw(sf::RenderWindow *window);


    /** \brief getEntity
     * Recupère l'entité associé à ce render
     * \return Entity*
     *
     */
    Entity* getEntity() const;
};

#endif
