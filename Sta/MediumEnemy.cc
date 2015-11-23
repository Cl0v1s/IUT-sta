#include "MediumEnemy.h"

using namespace std;

MediumEnemy::MediumEnemy(int x, int y, int level, EntityPlayer *player): EntityEnemy(x, y, 122, 57, "assets/mediumEnemy.png") //TODO: remplacer placeholder
{
    setLife(12*player->getShield() / 1.5);
    setFirePower(3 * level);
    setFireSpeed(65); //TODO: à ré-équilibrer
    setMovingSpeed(60); //TODO: à ré-équilibrer
    setValueInPoints(10);
    setShield(1);
    setType(3);
}

void MediumEnemy::update(vector<Attack *> &entities)
{

    if((m_box.getX()+m_box.getWidth()<=0) || (m_box.getY()+m_box.getHeight()<=0) || (m_box.getY()>=WINDOW_HEIGHT))
    {
        setLife(0);
        return;
    }

    //fonction de déplacement vertical des ennemis
    EntityEnemy::update(entities);

    setVelocityX(getMovingSpeed() * -1);
    int yvalue = getPatterFrame()%10;
    if(yvalue<5 && getVelocityY() == 0)
        setVelocityY(-getMovingSpeed()*((int)getPatterFrame()%9));
    else if (getVelocityX() == 0)
        setVelocityY(getMovingSpeed());
}

bool MediumEnemy::fire(vector<Attack *> &entities)
{
    Attack *atkTop = new Attack(this, -1,-1);
    Attack *atkMiddle = new Attack(this, -1,1);
    entities.push_back(atkTop);
    entities.push_back(atkMiddle);
    RenderEntity *renderT = new RenderEntity(atkTop);
    View::addRender(renderT);
    RenderEntity *renderM = new RenderEntity(atkMiddle);
    View::addRender(renderM);
    //cout << "Un MediumEnemy vient de tirer." << endl;
    return true;
}

std::string MediumEnemy::toString() const
{
    stringstream s;
    s << "--------------------------" << endl;
    s << "MediumEnemy:" << endl;
    s << SpaceShip::toString() << endl;
    s << "--------------------------";
    return s.str();
}

