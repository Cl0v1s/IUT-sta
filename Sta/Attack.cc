#include "Attack.h"

using namespace std;

Attack::Attack(SpaceShip *owner, float directionX, float directionY)  : EntityMoving(0,0,32,32,"assets/Attack.png")
{
    setLife(1);
    setType(5);
    m_owner = owner;
    m_damages = owner->getFirePower();
    if(directionX > 0)
    {
        m_box.setX(owner->getBoundingBox().getX() + owner->getBoundingBox().getWidth() + abs(owner->getVelocityX()*0.06));
        m_box.setY(owner->getBoundingBox().getY() + owner->getBoundingBox().getHeight()/2 - getBoundingBox().getHeight()/2);
    }
    else
    {
        m_box.setX(owner->getBoundingBox().getX() - getBoundingBox().getWidth() - abs(((int)owner->getVelocityX())));
        m_box.setY(owner->getBoundingBox().getY() + owner->getBoundingBox().getHeight()/2 - getBoundingBox().getHeight()/2);
    }
    setVelocityX(directionX * (owner->getMovingSpeed()+150));
    setVelocityY(directionY * (owner->getMovingSpeed()+150));

}

bool Attack::collidWith(Entity &other)
{
    if(m_box.intersects(other.getBoundingBox()))
    {
        hurtEnemy(other);
        return true;
    }
    return false;
}

void Attack::hit(Attack *source)
{
    setLife(0);
}

void Attack::hurtEnemy(Entity &other)
{
    other.hit(this);
    setLife(0);
}

SpaceShip *Attack::getOwner() const
{
    return m_owner;
}

void Attack::update()
{
    m_box.setX(m_box.getX() + 0.03*getVelocityX());
    m_box.setY(m_box.getY() + 0.03*getVelocityY());

    if(getVelocityX()*getVelocityX() < 1) //Utilisation du carré car abs ne prends que des entiers et el carré de deux nombres -1> <1 est >0 et <1
        setVelocityX(0);
    if(getVelocityY()*getVelocityY() < 1) //Utilisation du carré car abs ne prends que des entiers et el carré de deux nombres -1> <1 est >0 et <1
        setVelocityY(0);

    //destruction si sortie de l'écran
    if((m_box.getX()+m_box.getWidth()<=0) || (m_box.getY()+m_box.getHeight()<=0) || (m_box.getY()>=WINDOW_HEIGHT) || (m_box.getX() >= WINDOW_WIDTH))
        setLife(0);
}


int Attack::getDamages() const
{
    return m_damages;
}

void Attack::setDamages(const int damages)
{
    m_damages = damages;
}

string Attack::toString() const
{
    stringstream s;
    s << "--------------------------" << endl;
    s << "Attack:" << endl;
    s << EntityMoving::toString() << endl;
    s << "Damages:" << m_damages << endl;
    s << "--------------------------";
    return s.str();
}
