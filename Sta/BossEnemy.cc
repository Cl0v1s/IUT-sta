#include "BossEnemy.h"

using namespace std;

BossEnemy::BossEnemy(int x, int y, int level, EntityPlayer *player): EntityEnemy(x, y, 70, 70, "placeholder/BossEnemy.png") //TODO: remplacer placeholder
{
    setLife((50*level + player->getLife() + player->getMovingSpeed() + player->getShield() + player->getFirePower())/ 2.5);
    setFirePower(player->getFirePower());
    setFireSpeed(15); //TODO: à ré-équilibrer
    setMovingSpeed(1); //TODO: à ré-équilibrer

    m_upElseDown = false;
}

void BossEnemy::update(vector<Attack *> &entities)
{
    if(m_upElseDown)
        setVelocityY(getMovingSpeed() * -1);
    else
        setVelocityY(getMovingSpeed());
    if(m_box.getY() <= 0 || m_box.getY() + m_box.getHeight() >= WINDOW_HEIGHT)
        m_upElseDown = !m_upElseDown;
    //TODO: Pattern simpliste à améliorer


    EntityEnemy::update(entities);
}

bool BossEnemy::fire(vector<Attack *> &entities)
{
    int delta = getPatterFrame() % 3;

    if(delta == 0)
    {
        Attack *atkMiddle = new Attack(this, -1,0);
        entities.push_back(atkMiddle);
    }
    else if(delta == 1)
    {
        Attack *atkTop = new Attack(this, -1,-1);
        Attack *atkDown = new Attack(this, -1,1);
        entities.push_back(atkTop);
        entities.push_back(atkDown);
    }
    else if(delta == 2)
    {
        Attack *atkTop = new Attack(this, -1,-1);
        Attack *atkMiddle = new Attack(this, -1,0);
        Attack *atkDown = new Attack(this, -1,1);
        entities.push_back(atkTop);
        entities.push_back(atkMiddle);
        entities.push_back(atkDown);
    }
    return true;

}

bool BossEnemy::collidWith(const Entity &other)
{
    if(m_box.intersects(other.getBoundingBox()))
    {
        setLife(getLife() - other.getBoundingBox().getDensity());
    }
    return false;
}

std::string BossEnemy::toString() const
{
    stringstream s;
    s << "--------------------------" << endl;
    s << "BossEnemy:" << endl;
    s << SpaceShip::toString() << endl;
    s << "--------------------------";
    return s.str();
}


