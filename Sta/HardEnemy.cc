#include "HardEnemy.h"

using namespace std;

HardEnemy::HardEnemy(int x, int y, int level, EntityPlayer *player): EntityEnemy(x, y, 244, 114, "assets/hardEnemy.png") //TODO: remplacer placeholder
{
    setLife(12*player->getMovingSpeed() / 1.5);
    setFirePower(6 * level);
    setFireSpeed(30); //TODO: à ré-équilibrer
    setMovingSpeed(35); //TODO: à ré-équilibrer
    setValueInPoints(15);
    setShield(1);
}

bool HardEnemy::collidWith(Entity &other)
{
    return getBoundingBox().intersects(other.getBoundingBox());
}

void HardEnemy::update(vector<Attack*> &entities)
{
    if((m_box.getX()+m_box.getWidth()<=0) || (m_box.getY()+m_box.getHeight()<=0) || (m_box.getY()>=WINDOW_HEIGHT))
    {
        setLife(0);
        return;
    }
    //fonction de déplacement vertical des ennemis
    setVelocityX(getMovingSpeed() * -1);
    float yvalue = sin(getPatterFrame() * 0.03);
    if(yvalue < 0)
        setVelocityY(-getMovingSpeed());
    else
        setVelocityY(getMovingSpeed());
    EntityEnemy::update(entities);
}

bool HardEnemy::fire(vector<Attack *> &entities)
{
    Attack *atkTop = new Attack(this, -1,-1);
    Attack *atkMiddle = new Attack(this, -1,0);
    Attack *atkDown = new Attack(this, -1,1);
    entities.push_back(atkTop);
    entities.push_back(atkMiddle);
    entities.push_back(atkDown);
    RenderEntity *renderT = new RenderEntity(atkTop);
    View::addRender(renderT);
    RenderEntity *renderM = new RenderEntity(atkMiddle);
    View::addRender(renderM);
    RenderEntity *renderD = new RenderEntity(atkDown);
    View::addRender(renderD);
    //cout << "Un HardEnemy vient de tirer." << endl;
    return true;
}

std::string HardEnemy::toString() const
{
    stringstream s;
    s << "--------------------------" << endl;
    s << "HardEnemy:" << endl;
    s << SpaceShip::toString() << endl;
    s << "--------------------------";
    return s.str();
}


