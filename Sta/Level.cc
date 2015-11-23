/* ATTENTION:
* La constitution d'un niveau dépends entièrement de son seed, un même seed donnera lieu à la génération de deux niveau identiques sur des machines de puissances équivalentes.
* En revanche, ce système part du postulat que le déroulement du jeu est fluide et sans intérruption. (usage de durées et de millisecondes)
* De fait cette version du jeu (c'est à dire en mode console) ne permet pas des conditions de génération optimale de fait
* la génération de deux niveau possédant un même seed peut différé.
*/

#include "Level.h"

using namespace std;

Level::Level(int seed)
{
    if(seed < 512)
    {
        throw std::exception(); //il faut 9 bits de valeurs d'incrémentations aléatoire (éventuellement nuls) plus 4 bit amplitude / fréquence
    }


    //Récupération des informations portant sur la génération du niveau
    m_seed = seed;
    m_frame = 0;
    m_tick = 0;
    std::bitset<64> total(m_seed);
    for(int i = 0; i< 64; i++)
    {
        //cout << total[i];
    }
    //cout << endl;
    std::bitset<64> freqampl = total;



    //Récupération des bits random
    for(int i=0; i<9; i++)
    {
        m_rand[i] = total[i];
    }
    m_points = ((int)m_rand.to_ulong()); //Récupération du nombre de points requis pour finir le niveau (511 au max)

    freqampl >>= 9;

    //Récupération du numéro du niveau
    m_levelNumber = ((int)freqampl.to_ulong() - 4); //-4 car est le freqampl minium afin d'avoir une freq et une ampl correct est 5

    std::bitset<64> ampl = freqampl;
    std::bitset<64> freq = freqampl;
    int nb = 0;
    //Récupération de l'index du premier bit significatif
    int i = freqampl.size() -1;
    while(i>=0 && nb == 0)
    {
        if(freqampl[i] == 1)
        {
            nb = i+1;
        }

        i-=1;
    }
    //récupération de l'amplitude par décalage de bits
    ampl >>= nb/2;
    m_amplitude = (int)(ampl.to_ulong());
    //Récupération de la fréquence par usage de mask
    std::bitset<64> mask1;
    for(int i=0; i<nb/2; i++)
    {
        mask1[i] = 1;
    }
    freq &= mask1;
    m_frequency = (int)(freq.to_ulong());



    if(m_amplitude <= 0)
        m_amplitude = 1;
    if(m_frequency <= 0)
        m_frequency = 1;

}

Level::~Level()
{
    vector<EntityEnemy*>::iterator i = m_enemies.begin();
    while(i != m_enemies.end())
    {
        delete (*i);
        m_enemies.erase(i);
    }
    vector<Attack*>::iterator it = m_attacks.begin();
    while(it != m_attacks.end())
    {
        delete (*it);
        m_attacks.erase(it);
    }
    vector<EntityObstacle*>::iterator ite = m_obstacle.begin();
    while(ite != m_obstacle.end())
    {
        delete (*ite);
        m_obstacle.erase(ite);
    }
}

int Level::update()
{
    int done = 0;
    generateEnemies();
    generateObstacles();
    manageEntities();


    //Gestion des frames
    m_frame += 1;
    if(m_frame >= 60)
    {
        m_frame = 0;
    }

    //gestion du compteur de tick (lorsque les ticks arrivent à zéro, un nouvel ennemi/obstacle apparait)
    m_tick += m_rand[m_frame%10];
    double lim = (int)(m_rand.to_ulong());
    lim = 1/lim;
    lim *= 62500;
    if (lim <= 50)
        lim = 50;
    if(m_tick >= (lim)/2)
        m_tick = 0;


    //Détermination de la fin de la partie
    for(unsigned int i = 0; i<m_players.size(); i++)
    {
        if(m_players[i]->getPoints() >= m_points)
        {
            done = GAME_WIN_CODE; //on retourne 2 pour signifier que la partie est finie car l'un des joueurs a atteint le score requis
        }
        if(m_players[i]->getLife() <=0)
            done = GAME_LOOSE_CODE;//On retourne 1 pour signifier que la partie est finie car l'un des joueurs est mort
    }
    return done;
}

int Level::getLevelNumber() const
{
    return m_levelNumber;
}

void Level::manageEntities()
{
    //Mise à jour des joueurs

    for(unsigned int i=0; i<m_players.size(); i++)
    {
        m_players[i]->update();
        for(unsigned int u=0; u<m_enemies.size();u++)
        {
            m_players[i]->collidWith(*m_enemies[u]);
        }
        for(unsigned int u=0; u<m_obstacle.size();u++)
        {
            m_players[i]->collidWith(*m_obstacle[u]);
        }

    }
    //Mise à jour des ennemis
    for(vector<EntityEnemy*>::iterator i=m_enemies.begin(); i != m_enemies.end();)
    {
        ((*i))->update(m_attacks);
        for(unsigned int u=0; u<m_players.size();u++)
        {
            ((*i))->collidWith(*m_players[u]);
        }
        for(unsigned int u=0; u<m_obstacle.size();u++)
        {
            ((*i))->collidWith(*m_obstacle[u]);
        }

        //vérification de non superposition
        for(unsigned int u = 0; u<m_enemies.size(); u++)
        {
            if( (*i) != m_enemies[u] && ((*i))->getBoundingBox().intersects(m_enemies[u]->getBoundingBox()))
            {
                if((*i)->getVelocityY() < 0)
                {
                    (*i)->changePosition((*i)->getBoundingBox().getX(), m_enemies[u]->getBoundingBox().getY()+m_enemies[u]->getBoundingBox().getHeight()+1);
                }
                else
                {
                    (*i)->changePosition((*i)->getBoundingBox().getX(), m_enemies[u]->getBoundingBox().getY()-(*i)->getBoundingBox().getHeight()-1);

                }
                (*i)->setVelocityY((*i)->getVelocityY()*-1);
            }
        }


        //suppression si l'entité courant n'a plus de vie
        if(((*i))->getLife() <=0)
        {
                if((*i)->getBoundingBox().inScreen())
                    View::playSoundEffect(View::getSoundExplosion());
            //cout << "un ennemi a été détruit" << endl;
            //Affichage de l'explosion
            RenderEffect *render = new RenderEffect("assets/explode.png", (*i)->getBoundingBox().getX()+(*i)->getBoundingBox().getWidth()/2 - 16, (*i)->getBoundingBox().getY()+(*i)->getBoundingBox().getHeight()/2 - 16, 32,32,0,0.4);
            View::addRender(render);
            View::removeRender(*i); //On supprime le render associé à cette entité
            delete ((*i));
            m_enemies.erase(i);
        }
        else
            i++;
    }
    //Mise à jour des obstacles
    for(vector<EntityObstacle*>::iterator i=m_obstacle.begin(); i != m_obstacle.end();)
    {
        ((*i))->update();
        (*i)->changePosition((*i)->getBoundingBox().getX()-(m_players[0]->getMovingSpeed()-100), (*i)->getBoundingBox().getY());
        for(unsigned int u=0; u<m_players.size();u++)
        {
            (*i)->collidWith(*m_players[u]);
        }
        for(unsigned int u=0; u<m_obstacle.size();u++)
        {
            if((*i) != (*i))
                (*i)->collidWith(*m_obstacle[u]);
        }
        for(unsigned int u=0; u<m_enemies.size();u++)
        {
            ((*i))->collidWith(*m_enemies[u]);
        }
        //suppression si l'entité courant n'a plus de vie
        if((*i)->getLife() <=0)
        {
                if((*i)->getBoundingBox().inScreen())
                    View::playSoundEffect(View::getSoundExplosion());
            RenderEffect *render = new RenderEffect("assets/explode.png", (*i)->getBoundingBox().getX()+(*i)->getBoundingBox().getWidth()/2 - 16, (*i)->getBoundingBox().getY()+(*i)->getBoundingBox().getHeight()/2 - 16, 32,32,0,0.4);
            View::addRender(render);
            View::removeRender(*i); //On supprime le render associé à cette entité
            delete (*i);
            m_obstacle.erase(i);
            //cout << "Un obstacle est entré en collision et a été detruit." << endl;
        }
        else
            i++;
    }
    //Mise à jour des attaques
    for(vector<Attack*>::iterator i=m_attacks.begin(); i != m_attacks.end();)
    {
            (*i)->update();
            for(unsigned int u=0; u<m_players.size();u++)
            {
                bool f = (*i)->collidWith(*m_players[u]);
                //Vérification de l'existence du propriétaire (pour éviter segfault en cas de destruction du propriétaire alors que le tir existe toujours
                if(f && entityExists((*i)->getOwner()))
                    (*i)->getOwner()->hurtEnemy(*m_players[u]);
            }
            for(unsigned int u=0; u<m_obstacle.size();u++)
            {
                bool f = (*i)->collidWith(*m_obstacle[u]);
                //Vérification de l'existence du propriétaire (pour éviter segfault en cas de destruction du propriétaire alors que le tir existe toujours
                if(f && entityExists((*i)->getOwner()))
                    (*i)->getOwner()->hurtEnemy(*m_obstacle[u]);
            }
            for(unsigned int u=0; u<m_enemies.size();u++)
            {
               bool f = (*i)->collidWith(*m_enemies[u]);
                //Vérification de l'existence du propriétaire (pour éviter segfault en cas de destruction du propriétaire alors que le tir existe toujours
                if(f && entityExists((*i)->getOwner()))
                    (*i)->getOwner()->hurtEnemy(*m_enemies[u]);
            }
            //suppression si l'entité courante n'a plus de vie
            if((*i)->getLife() <=0)
            {
                if((*i)->getBoundingBox().inScreen())
                    View::playSoundEffect(View::getSoundHurt());
                RenderEffect *render = new RenderEffect("assets/explode.png", (*i)->getBoundingBox().getX()+(*i)->getBoundingBox().getWidth()/2 - 16, (*i)->getBoundingBox().getY()+(*i)->getBoundingBox().getHeight()/2 - 16, 32,32,0,0.4);
                View::addRender(render);
                View::removeRender(*i); //On supprime le render associé à cette entité
                delete (*i);
                i=m_attacks.erase(i);
            }
            else
                i++;
    }


}

bool Level::entityExists(const Entity *entity) const
{
    unsigned int i = 0;
    bool f = false;
    while (i < m_enemies.size() && !f)
    {
        if(m_enemies[i] == entity)
            f = true;
        i++;
    }
    if(f)
        return true;
    i = 0;
    while (i < m_obstacle.size() && !f)
    {
        if(m_obstacle[i] == entity)
            f = true;
        i++;
    }
    if(f)
        return true;
    i = 0;
    while (i < m_attacks.size() && !f)
    {
        if(m_attacks[i] == entity)
            f = true;
        i++;
    }
    if(f)
        return true;
    i = 0;
    while (i < m_players.size() && !f)
    {
        if(m_players[i] == entity)
            f = true;
        i++;
    }
    return f;
}

void Level::generateEnemies()
{
    if(m_tick != 0)
        return;
    //cout << "Un nouvel ennemi vient d'apparaitre:" << endl;

    long v = m_amplitude * sin(m_frequency*m_frame); //plus ce nombre est grand plus le monstre apparaissant sera puissant, la variation de cette fonction sinusoidale dépend du seed
    float type = abs(v);

    //Détermination de la position de l'entité

    int y = m_frame * v * 10;
    while(y > WINDOW_HEIGHT)
    {
        y -= WINDOW_HEIGHT;
    }

    //génération d'ennemi de niveau 1
   if (type <= 1)
   {
        EasyEnemy *e = new EasyEnemy(WINDOW_WIDTH, abs(y), m_levelNumber, m_players[0]);
        m_enemies.push_back(e);
        //Ajout de l'entité au View
        RenderEntity *render = new RenderEntity(e);
        View::addRender(render);
        //cout << e->toString() << endl;
   }
   else if (type <= 2) //génération d'ennemi de niveau 2
   {
        MediumEnemy *e = new MediumEnemy(WINDOW_WIDTH, abs(y), m_levelNumber, m_players[0]);
        m_enemies.push_back(e);
        //Ajout de l'entité au View
        RenderEntity *render = new RenderEntity(e);
        View::addRender(render);
        //cout << e->toString() << endl;
   }
   else if (type <= 3) //génération d'ennemi de niveau 3
   {
        HardEnemy *e = new HardEnemy(WINDOW_WIDTH, abs(y), m_levelNumber, m_players[0]);
        m_enemies.push_back(e);
        //Ajout de l'entité au View
        RenderEntity *render = new RenderEntity(e);
        View::addRender(render);
        //cout << e->toString() << endl;
   }
}

void Level::generateObstacles()
{
    if(m_tick != 0)
        return;

    long v = m_amplitude * sin(m_frequency*m_frame);
    int ok = abs(v);
    //Détermination de la position de l'entité
    int y = m_frame * m_amplitude * 10;
    while(y > WINDOW_HEIGHT)
    {
        y -= WINDOW_HEIGHT;
    }
    if(ok==0)
    {
        //cout << "Un nouvel obstacle vient d'apparaitre:" << endl;
        int type = m_rand[m_frame%10];
        if(type == 0)
        {
            EntityObstacle *o = new EntityObstacle(EntityObstacle::Asteroid);
            o->changePosition(WINDOW_WIDTH, y);
            m_obstacle.push_back(o);
            RenderEntity *render = new RenderEntity(o);
            View::addRender(render);
            //cout << o->toString() << endl;
        }
        else
        {
            EntityObstacle *o = new EntityObstacle(EntityObstacle::ShipPart);
            o->changePosition(WINDOW_WIDTH, y);
            m_obstacle.push_back(o);
            RenderEntity *render = new RenderEntity(o);
            View::addRender(render);
            //cout << o->toString() << endl;
        }
    }
}

void Level::addPlayer(EntityPlayer* e)
{
    m_players.push_back(e);
}

void Level::showAttacks()
{
    //cout << "Liste des attaques en cours:" << endl;
    for(unsigned int i= 0; i< m_attacks.size(); i++)
    {
        //cout << m_attacks[i]->toString() << endl;
    }
    //cout << endl;
}

void Level::showEnemies()
{
    //cout << "Liste des ennemis présents dans le niveau:" << endl;
    for(unsigned int i = 0; i< m_enemies.size(); i++)
    {
        //cout << m_enemies[i]->toString() << endl;
    }
    //cout << endl;
}

void Level::showObstacles()
{
    //cout << "Liste des obstacles présents dans le niveau:" << endl;
    for(unsigned int i = 0; i< m_obstacle.size(); i++)
    {
        //cout << m_obstacle[i]->toString() << endl;
    }
    //cout << endl;
}

void Level::showPlayers()
{
    //cout << "Liste des joueurs en jeu:" << endl;
    for(unsigned int i = 0; i<m_players.size(); i++)
    {
        //cout << m_players[i]->toString() << endl;
    }
    //cout << endl;
}

int Level::getRequiredPoints() const
{
    return m_points;
}

void Level::reset()
{
    m_tick = 0;
    m_frame = 0;
    //Replacement des joueurs
    for(unsigned int i = 0; i< m_players.size();i++)
    {
        m_players[i]->setLife(20);
        m_players[i]->setPoints(0);
        m_players[i]->changePosition(0, WINDOW_HEIGHT/2-25 - ((m_players.size()-1) *50) + i*25);
        m_players[i]->setVelocityX(0);
        m_players[i]->setVelocityY(0);
    }
    //supression des tirs
    for(unsigned int i = 0; i<m_attacks.size(); i++)
    {
        delete m_attacks[i];
        View::removeRender(m_attacks[i]);
    }
    m_attacks.clear();
    //Supression des enemis
    for(unsigned int i = 0; i< m_enemies.size(); i++)
    {
        delete m_enemies[i];
        View::removeRender(m_enemies[i]);
    }
    m_enemies.clear();
    //Supression des obstacles
    for(unsigned int i = 0; i< m_obstacle.size(); i++)
    {
        delete m_obstacle[i];
        View::removeRender(m_obstacle[i]);
    }
    m_obstacle.clear();
}





