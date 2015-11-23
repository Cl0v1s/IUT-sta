#include "EasyEnemy.h"

using namespace std;

EasyEnemy::EasyEnemy(int x, int y, int level, EntityPlayer *player): EntityEnemy(x, y, 58, 54, "assets/EasyEnemy.png") //TODO: remplacer placeholder
{
    setType(2);
    setLife(6*player->getFirePower() / 1.5);
    setFirePower(2 * level);
    setFireSpeed(80); //TODO à ré-équilibrer
    setMovingSpeed(50);//TODO à ré-équilibrer
    setValueInPoints(5);
    setShield(1);
}

void EasyEnemy::update(vector<Attack *> &entities)
{
    if((m_box.getX()+m_box.getWidth()<=0) || (m_box.getY()+m_box.getHeight()<=0) || (m_box.getY()>=WINDOW_HEIGHT))
    {
        setLife(0);
        return;
    }
    setVelocityX(getMovingSpeed() * -1);
    EntityEnemy::update(entities);
}

bool EasyEnemy::fire(vector<Attack *> &entities)
{
    Attack *atk = new Attack(this, -1,0);
    entities.push_back(atk);
    RenderEntity *render = new RenderEntity(atk);
    View::addRender(render);
    //cout << "Un EasyEnemy vient de tirer." << endl;
    return true;
}

std::string EasyEnemy::toString() const
{
    stringstream s;
    s << "--------------------------" << endl;
    s << "EasyEnemy:" << endl;
    s << SpaceShip::toString() << endl;
    s << "--------------------------";
    return s.str();
}
