#include "EntityEnemy.h"

using namespace std;

EntityEnemy::EntityEnemy(int x, int y, int width, int height, std::string imageFile) : SpaceShip(x,y,width, height, imageFile)
{
    m_fireCount = 20;
    m_patternFrame = 0;
}

void EntityEnemy::update(std::vector<Attack*> &entities)
{
    SpaceShip::update();
    m_patternFrame += 1;

    if(m_fireCount > getFireSpeed())
    {
        m_fireCount = 0;
        fire(entities);
    }
}

void EntityEnemy::setPatternFrame(const int a)
{
    m_patternFrame = a;
}

void EntityEnemy::setFireCount(const int a)
{
    m_fireCount = a;
}

int EntityEnemy::getPatterFrame() const
{
    return m_patternFrame;
}

int EntityEnemy::getFireCount() const
{
    return m_fireCount;
}


