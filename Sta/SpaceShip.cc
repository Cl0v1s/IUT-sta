#include "SpaceShip.h"

using namespace std;

SpaceShip::SpaceShip(int x, int y, int width, int height, std::string imageFile) : EntityMoving(x,y,width,height, imageFile)
{
	m_firePower = 0;
	m_shield = 0;
	m_fireSpeed =0;
	m_movingSpeed = 0;
	m_fireCount = 0;
}

void SpaceShip::hit(Attack *source)
{
    int life = getLife();
    life -= source->getDamages() / getShield();
    setLife(life);
}

void SpaceShip::update()
{
    EntityMoving::update();
    m_fireCount +=1;
}

void SpaceShip::setFirePower(const float a)
{
    m_firePower = a;
}

float SpaceShip::getFirePower() const
{
    return m_firePower;
}

void SpaceShip::setShield(const float a)
{
    m_shield = a;
}

float SpaceShip::getShield() const
{
    return m_shield;
}

void SpaceShip::setFireSpeed(const float a)
{
    if( a > 0)
        m_fireSpeed = a;
}

float SpaceShip::getFireSpeed() const
{
    return m_fireSpeed;
}

void SpaceShip::setMovingSpeed(const float a)
{
    if(a > 0)
        m_movingSpeed = a;
}

float SpaceShip::getMovingSpeed() const
{
    return m_movingSpeed;
}

std::string SpaceShip::toString() const
{
    stringstream s;
    s << EntityMoving::toString() << endl;
    s << "FirePower: " << m_firePower << " FireSpeed: " << m_fireSpeed << endl;
    s << "Shield: " << m_shield << " MovingSpeed: " << m_movingSpeed;
    return s.str();
}
