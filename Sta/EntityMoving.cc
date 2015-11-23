#include "EntityMoving.h"

using namespace std;

EntityMoving::EntityMoving(int x, int y, int width, int height, string imageFile) : Entity(x,y,width,height, imageFile)
{
    m_velocityX = 0;
    m_velocityY = 0;
}

void EntityMoving::moveTo(const int x, const int y)
{
    move(x-m_box.getX(), y-m_box.getY());
}

void EntityMoving::move(const int x, const int y)
{
    m_velocityX = x;
    m_velocityY = y;
}

void EntityMoving::update()
{

    //on déplace l'entité grace à sa velocité
    m_box.m_x += 0.03*m_velocityX;
    if((m_box.getY() >0 && m_velocityY < 0) || (m_box.getY()+m_box.getHeight() < WINDOW_HEIGHT && m_velocityY > 0))
        m_box.m_y += 0.03*m_velocityY;

    //on réduit sa vélocité
    m_velocityX -= 0.03*m_velocityX;
    m_velocityY -= 0.03*m_velocityY;

    //on supprime toute vélocité résiduelle si celle si est trop réduite
    if(m_velocityX*m_velocityX < 1) //Utilisation du carré car abs ne prends que des entiers
        m_velocityX = 0;
    if(m_velocityY*m_velocityY < 1)
        m_velocityY = 0;


}

void EntityMoving::setVelocityX(const float x)
{
    m_velocityX = x;
}

void EntityMoving::setVelocityY(const float y)
{
    m_velocityY = y;
}

float EntityMoving::getVelocityX() const
{
    return m_velocityX;
}

float EntityMoving::getVelocityY() const
{
    return m_velocityY;
}

std::string EntityMoving::toString() const
{
    stringstream s;
    s << Entity::toString() << endl;
    s << "Velocity: [" << m_velocityX << "," << m_velocityY << "]";
    return s.str();
}
