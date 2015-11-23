#include "Render.h"

Render::Render()
{

}

Render::~Render()
{

}

Render::Render(std::string file)
{
   // m_image = new sf::Image();
    if(!m_image.LoadFromFile(file))
    {
        throw std::string("Unable to found the file "+file+".");
    }
    m_sprite.SetImage(m_image);
    m_frame = 0;
    m_speed = 1;
    m_width = 0;
    m_height = 0;
}

Render::Render(std::string file, int width, int height, float speed)
{
    m_speed = speed;
    m_width = width;
    m_height = height;
    //m_image = new sf::Image();
    if(!m_image.LoadFromFile(file))
    {
        throw std::string("Unable to found the file "+file+".");
    }
    m_sprite.SetImage(m_image);
}

int Render::getX() const
{
    return m_sprite.GetPosition().x;
}

int Render::getY() const
{
    return m_sprite.GetPosition().y;
}



