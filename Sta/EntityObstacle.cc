#include "EntityObstacle.h"

using namespace std;

//Déclaration des différents types d'obtacle
EntityObstacle EntityObstacle::Asteroid(50,0,0,50,50,"assets/rock.png");
EntityObstacle EntityObstacle::ShipPart(70,0,0,70,80,"assets/shipPart.png");

EntityObstacle::EntityObstacle(int life, int x, int y, int width, int height, std::string imageFile) : Entity(x,y,width, height, imageFile)
{
    setType(6);
    setLife(life);
    setValueInPoints(10);
}

void EntityObstacle::update()
{
    if((m_box.getX()+m_box.getWidth()<=0) || (m_box.getY()+m_box.getHeight()<=0) || (m_box.getY()>=WINDOW_HEIGHT))
    {
        setLife(0);
        return;
    }
}

void EntityObstacle::hit(Attack *source)
{
    setLife(getLife()-source->getDamages());
}

std::string EntityObstacle::toString() const
{
    stringstream s;
    s << "--------------------------" << endl;
    s << "Obstacle:" << endl;
    s << Entity::toString() << endl;
    s << "--------------------------";
    return s.str();
}
