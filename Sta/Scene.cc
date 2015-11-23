#include "Scene.h"

using namespace std;

Scene::Scene()
{

}

Scene::~Scene()
{
    for(unsigned int i = 0; i < m_menuList.size(); i++)
    {
        delete m_menuList[i];
    }
}

Menu* Scene::getCurrentMenu()
{
    Menu *res = NULL;
    vector<Menu*>::const_iterator it=m_menuList.begin();
    while(res == NULL && it != m_menuList.end())
    {
        if((*it)->getActive())
            res = (*it);
        it++;
    }
    return res;
}

vector<Menu*>& Scene::getMenuList()
{
    return m_menuList;
}
