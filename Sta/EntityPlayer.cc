#include "EntityPlayer.h"

using namespace std;

EntityPlayer::EntityPlayer(int x, int y) : SpaceShip(x,y,64,64, "assets/hero.png")
{
    setType(1);

    setLife(20);
    setShield(2);
    setFirePower(2);
    setFireSpeed(15); //délai de 15 frames soit 2.5 tir/seconde
    setMovingSpeed(101);
    m_fireLevel = 1;
    m_points = 0;
    m_comboCounter = 0;

    m_firePowerLevel = 1;
    m_fireSpeedLevel = 1;
    m_movingSpeedLevel = 1;
    m_shieldLevel = 1;

    m_powerModed = false;

    m_money = 0;
}

bool EntityPlayer::powerMode()
{
    if(!m_powerModed)
    {
        m_powerModed = true;
        m_comboCounter = 21;
        m_fireLevel = 2;
        return true;
    }
    return false;
}

void EntityPlayer::savePointsToMoney()
{
    m_money = m_points;
    m_points = 0;
    //cout << "odfsfsdfdsfdsfdsfdfsdsk" << endl;
}

void EntityPlayer::setMoney(const int money)
{
    m_money = money;
}

int EntityPlayer::getMoney() const
{
    return m_money;
}

void EntityPlayer::update()
{
    SpaceShip::update();
    //gestion du dépassement de l'écran
    if(m_box.getX() <= 0)
    {
        m_box.setX(0);
        if(getVelocityX() < 0)
            setVelocityX(0);
    }
    else if(m_box.getX()+m_box.getWidth() > WINDOW_WIDTH)
    {
        m_box.setX(WINDOW_WIDTH - m_box.getWidth());
        if(getVelocityX() > 0)
            setVelocityX(0);
    }

    if(m_box.getY() <= 0)
    {
        m_box.setY(0);
        if(getVelocityY() < 0)
            setVelocityY(0);
    }
    else if(m_box.getY()+m_box.getHeight() > WINDOW_HEIGHT)
    {
        m_box.setY(WINDOW_HEIGHT - m_box.getHeight());
        if(getVelocityY() > 0)
            setVelocityY(0);
    }


}

void EntityPlayer::enablePowerMode()
{
    m_powerModed = false;
}

bool EntityPlayer::fire(vector<Attack*> &entities)
{

    if(m_fireCount >= getFireSpeed())
    {
        if(m_fireLevel == 1)
        {

            Attack *atk = new Attack(this, 1, 0);
            entities.push_back(atk);
            RenderEntity *render = new RenderEntity(atk);
            View::addRender(render);
            //cout << "Le joueur a tiré un simple shot tel que " << endl << atk->toString() << endl;
        }
        else if(m_fireLevel == 2)
        {
            Attack *atkTop =new Attack(this, 1,-1);
            Attack *atkMiddle = new Attack(this, 1,0);
            Attack *atkDown = new Attack(this, 1,1);
            entities.push_back(atkTop);
            entities.push_back(atkMiddle);
            entities.push_back(atkDown);
            RenderEntity *renderT = new RenderEntity(atkTop);
            View::addRender(renderT);
            RenderEntity *renderM = new RenderEntity(atkMiddle);
            View::addRender(renderM);
            RenderEntity *renderD = new RenderEntity(atkDown);
            View::addRender(renderD);
            //cout << "Le joueur a tiré un triple shot tel que " << endl << atkMiddle->toString() << endl;
        }
        m_fireCount = 0;
        return true;
    }
    return false;
}

void EntityPlayer::hurtEnemy(Entity &other)
{
    if(other.getLife() <= 0)
    {
        setPoints(getPoints() + other.getValueIntPoints());
    }
    m_comboCounter += 1;
    if(m_comboCounter > 20)
    {
        m_powerModed = false;
    }
    cout << m_powerModed << endl;
}

int EntityPlayer::getCombo() const
{
    return m_comboCounter;
}

bool EntityPlayer::collidWith(Entity & other)
{
    return m_box.intersects(other.getBoundingBox());
}

void EntityPlayer::hit(Attack *source)
{
    SpaceShip::hit(source);
    m_comboCounter = 0;
    m_powerModed = true;
    m_fireLevel = 1;
    //cout << "Le joueur a été touché par " << endl << source->toString() << endl;
}

string EntityPlayer::toString() const
{
    stringstream s;
    s << "--------------------------" << endl;
    s << "EntityPlayer:" << endl;
    s << SpaceShip::toString() << endl;
    s << "Points:" << m_points << endl;
    s << "Combo: " << m_comboCounter << " FireLevel: " << m_fireLevel << endl;
    s << "--------------------------";
    return s.str();
}

void EntityPlayer::setPoints(const int p)
{
    m_points = p;
}

int EntityPlayer::getPoints() const
{
    return m_points;
}

int EntityPlayer::getFirePowerLevel() const
{
    return m_firePowerLevel;
}

int EntityPlayer::getFireSpeedLevel() const
{
    return m_fireSpeedLevel;
}

int EntityPlayer::getMovingSpeedLevel() const
{
    return m_movingSpeedLevel;
}

int EntityPlayer::getShieldLevel() const
{
    return m_shieldLevel;
}

void EntityPlayer::setFirePowerLevel(const int v)
{
    m_firePowerLevel = v;
}

void EntityPlayer::setFireSpeedLevel(const int v)
{
    m_fireSpeedLevel = v;
}

void EntityPlayer::setMovingSpeedLevel(const int v)
{
    m_movingSpeedLevel = v;
}

void EntityPlayer::setShieldLevel(const int v)
{
    m_shieldLevel = v;
}



