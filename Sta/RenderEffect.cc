#include "RenderEffect.h"


float RenderEffect::defaultSpeed = 0.2;

RenderEffect::RenderEffect(std::string file, int x, int y, int width, int height, int deg, Render *render) : Render(file, width, height, RenderEffect::defaultSpeed)
{
    m_render = render;
    m_x = x;
    m_y = y;
    if(deg != 0)
    {
        m_sprite.SetRotation(deg);
    }
    m_velocityX = 0;
    m_velocityY = 0;
}

RenderEffect::RenderEffect(std::string file, int x, int y, int width, int height, int deg) : Render(file, width, height, defaultSpeed)
{
    m_render = NULL;
    m_x = x;
    m_y = y;
    if(deg != 0)
    {
        m_sprite.SetRotation(deg);
    }
   //std:://cout << "prout" << std::endl;
   m_velocityX = 0;
   m_velocityY = 0;
}

RenderEffect::RenderEffect(std::string file, int x, int y, int width, int height, int deg, float speed) : Render(file, width, height, speed)
{
    m_render = NULL;
    m_x = x;
    m_y = y;
    if(deg != 0)
    {
        m_sprite.SetRotation(deg);
    }
    m_velocityX = 0;
    m_velocityY = 0;
}

void RenderEffect::draw(sf::RenderWindow *window)
{
    m_x += m_velocityX*0.03;
    m_y += m_velocityY*0.03;

    if(m_width != 0 && m_height !=0)
    {
        //gestion des annimations
        m_sprite.SetSubRect(sf::IntRect(((int)m_frame)*m_width, 0, ((int)m_frame+1)*m_width, m_height));
        m_frame += m_speed;
       if(((unsigned int)m_frame)*m_width>=((unsigned int)m_sprite.GetImage()->GetWidth()))
       {
            m_frame = 0;
            if(m_speed != defaultSpeed)
            {
                View::removeRender(this);
                return;
            }

       }
    }
    if(m_render != NULL)
        m_sprite.SetPosition(m_render->getX()+m_x, m_render->getY()+m_y);
    else
        m_sprite.SetPosition(m_x, m_y);
    window->Draw(m_sprite);
}

Render* RenderEffect::getRender() const
{
    return m_render;
}

void RenderEffect::setX(const int x)
{
    m_x = x;
}

void RenderEffect::setY(const int y)
{
    m_y = y;
}

int RenderEffect::getX() const
{
    return m_x;
}

int RenderEffect::getY() const
{
    return m_y;
}

void RenderEffect::setVelocity(const int x, const int y)
{
    m_velocityX = x;
    m_velocityY = y;
}

