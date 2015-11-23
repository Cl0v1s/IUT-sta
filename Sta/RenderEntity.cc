#include "RenderEntity.h"

RenderEntity::RenderEntity(Entity *entity) : Render(entity->m_imageFile, entity->m_box.getWidth(), entity->m_box.getHeight(), 1)
{
    m_entity = entity;
    //std:://cout << entity->getType() << std::endl;
    //Ajout des flammes de réacteur si l'entité est un joueur (on use pas de cast pour gagner en performance ainsi que suite à des problèmes d'include)
    if(entity->getType() == 1)
    {
        RenderEffect *render = new RenderEffect("assets/fire.png", -30,-5,33,32,0,this);
        View::addRender(render);
        render = new RenderEffect("assets/fire.png", -30,32,33,32,0,this);
        View::addRender(render);
    }
}

void RenderEntity::draw(sf::RenderWindow *window)
{
    if(m_width != 0 && m_height !=0)
    {
        m_sprite.SetSubRect(sf::IntRect(((int)m_frame)*m_width, 0, m_width, m_height));
        m_frame += m_speed;
        if(((int)m_frame)*m_width>=m_sprite.GetSize().x)
            m_frame = 0;
    }

    //Si l'entité est un obtacle alors on le fait tourner et on corrge sa position (suite au changement de centre)
    if(m_entity->getType() == 6)
    {
        m_sprite.SetCenter(m_entity->m_box.getWidth()/2, m_entity->m_box.getHeight()/2);
        m_sprite.SetRotation(m_sprite.GetRotation()+0.5);
        m_sprite.SetPosition(m_entity->m_box.getX()+m_entity->m_box.getWidth()/2, m_entity->m_box.getY()+m_entity->m_box.getHeight()/2);

    }
    else
        m_sprite.SetPosition(m_entity->m_box.getX(), m_entity->m_box.getY());





    window->Draw(m_sprite);

}

Entity* RenderEntity::getEntity() const
{
    return m_entity;
}
