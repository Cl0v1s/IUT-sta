#include "Entity.h"

using namespace std;

Entity::Entity(int x, int y, int width, int height, std::string imageFile) : m_box(x, y, width, height)
{
    m_life = 0;
    m_valueInPoints = 0;
    m_imageFile = imageFile;
    setType(0);
}

void Entity::setType(const int type)
{
    m_type = type;
}

int Entity::getType() const
{
    return m_type;
}


Entity::~Entity()
{

}

int Entity::getLife() const
{
    return m_life;
}


void Entity::setLife(const int life)
{
    m_life = life;
}

void Entity::changePosition(const int x,const int y)
{
    m_box.setX(x);
    m_box.setY(y);
}

int Entity::getValueIntPoints() const
{
    return m_valueInPoints;
}

void Entity::setValueInPoints(const int point)
{
    if(point < 0)
        return;
    m_valueInPoints = point;
}

BoundingBox Entity::getBoundingBox() const
{
    return m_box;
}

bool Entity::collidWith(Entity &other)
{
    if(m_box.intersects(other.getBoundingBox()))
    {
        other.setLife(other.getLife() - 10);
        setLife(0);
        return true;
    }
    return false;
}

void Entity::hurtEnemy(Entity &other)
{

}

string Entity::toString() const
{
    stringstream s;
    s << "life:" << m_life << " valueInPoints:" << m_valueInPoints << endl;
    s << "box: {" << m_box.toString() << "}" << endl;
    return s.str();
}




