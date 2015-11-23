#include "UpgradeScene.h"

using namespace std;

UpgradeScene::UpgradeScene(const int lastSeed, vector<EntityPlayer*> players) : Scene(), m_players(players)
{


    //Affichage du fond d'écran
    RenderEffect *background = new RenderEffect("assets/background.png", 0,0,WINDOW_WIDTH,WINDOW_HEIGHT, 0);
    View::addRender(background);

    m_seed = lastSeed;

    m_score = 0;
    for(unsigned int i=0; i<players.size(); i++)
    {
        m_score += players[i]->getPoints() + players[i]->getMoney(); //On calcule la moyenne des points gagné par les deux joueurs
    }
    m_score = m_score / players.size();

    //ajout du menu d'amélioration
    Menu* menu = new Menu(this, WINDOW_WIDTH-402, WINDOW_HEIGHT/2-100, 368, 200);
    menu->addEntry("Ameliorer puissance", &upgradeFirePower);
    menu->addEntry("Ameliorer cadence", &upgradeFireSpeed);
    menu->addEntry("Ameliorer vitesse", &upgradeMovingSpeed);
    menu->addEntry("Ameliorer bouclier", &upgradeShield);
    menu->addEntry("Niveau suivant", &goToNextLevel);
    m_menuList.push_back(menu);
    RenderMenu *render = new RenderMenu(menu);
    View::addRender(render);

    //Affichage du nombre de points détenus par le joueur
    RenderText *txt = new RenderText("points", to_string(m_score) + "$", WINDOW_WIDTH/2 - 140, WINDOW_HEIGHT - 50, 20, false);
    View::addRender(txt);

    //Affichage de l'aperçu du joueur
    RenderEffect *sprite = new RenderEffect("assets/hero.png", 100,WINDOW_HEIGHT /2 -32,64,64,10);
    View::addRender(sprite);

    //Affichage du message d'achat (il est vide il sera modifié plus tard dans l'éxécution)
    RenderText *msg = new RenderText("message", "", 100,WINDOW_HEIGHT /2 -100, 16, false);
    View::addRender(msg);
}

bool UpgradeScene::update()
{
    RenderText *rdrtxt = View::getRenderText("points");
    if( rdrtxt != NULL)
        rdrtxt->setText(to_string(m_score)+"$");

    bool done = inputUpdate();


    if(Game::isFinished())
        done = true;
    return done;
}

int UpgradeScene::getScore() const
{
    return m_score;
}

int UpgradeScene::getSeed() const
{
    return m_seed;
}

void UpgradeScene::goToNextLevel(Scene *scene)
{


    View::clearRenders();

    UpgradeScene *s = dynamic_cast<UpgradeScene *>(scene);



    //calcul du nouveau seed (+1 amplitude, *1.1 score max (/rand)
    if(s == NULL)
        throw logic_error("Une upgrade scene est attendue.");
    std::bitset<64> seed(s->getSeed());

    //récupération old Rand
    std::bitset<9> rand;
    for(int i=0; i<9; i++)
    {
        rand[i] = seed[i];
    }
    int oldSeed = ((int)rand.to_ulong());

    //changement rand
    std::bitset<9> newrand(oldSeed*1.1);


    //changement de la frequample
    seed >>= 9;
    int freqampl = (int)seed.to_ulong()+1;

    //création new seed
    std::bitset<64> newseed(freqampl);
    newseed <<= 9;
    for(int i = 0; i<9; i++)
    {
        newseed[i] = newrand[i];
    }


    GameScene *sc = new GameScene(((int)newseed.to_ulong()), s->getPlayers());
    Game::changeScene(sc);
}

void UpgradeScene::upgradeFirePower(Scene *scene)
{
    UpgradeScene *s = dynamic_cast<UpgradeScene *>(scene);
    if(s == NULL)
        throw logic_error("Une upgrade scene est attendue.");
    if(s->buy(exp((s->getPlayers()[0]->getFirePowerLevel()-1))+249) == false)
        return;
    for(unsigned int i = 0; i< s->getPlayers().size(); i++)
    {
        EntityPlayer *e = s->getPlayers()[i];
        e->setFirePowerLevel(e->getFirePowerLevel()+1);
        cout << e->getFirePower() << endl;
        e->setFirePower(e->getFirePower()+exp(-0.08*e->getFirePowerLevel()+1));
        cout << e->getFirePower() << endl;
    }
}

void UpgradeScene::upgradeFireSpeed(Scene *scene)
{
    UpgradeScene *s = dynamic_cast<UpgradeScene *>(scene);
    if(s == NULL)
        throw logic_error("Une upgrade scene est attendue.");
    if(s->buy(exp((s->getPlayers()[0]->getFireSpeedLevel()-1))+249) == false)
        return;
    for(unsigned int i= 0; i<s->getPlayers().size(); i++)
    {
        EntityPlayer *e = s->getPlayers()[i];
        e->setFireSpeedLevel(e->getFireSpeedLevel()+1);
        cout << e->getFireSpeed() << endl;
        e->setFireSpeed(e->getFireSpeed()-exp(-0.08*e->getFireSpeedLevel()+1));
        cout << e->getFireSpeed() << endl;
    }
}

void UpgradeScene::upgradeMovingSpeed(Scene *scene)
{
    UpgradeScene *s = dynamic_cast<UpgradeScene *>(scene);
    if(s == NULL)
        throw logic_error("Une upgrade scene est attendue.");
    if(s->buy(exp((s->getPlayers()[0]->getMovingSpeedLevel()-1))+249) == false)
        return;
    for(unsigned int i = 0; i<s->getPlayers().size(); i++)
    {
        EntityPlayer *e = s->getPlayers()[i];
        e->setMovingSpeedLevel(e->getMovingSpeedLevel()+1);
        e->setMovingSpeed(e->getMovingSpeed()+exp(-0.08*e->getMovingSpeedLevel()+1));
    }
}

void UpgradeScene::upgradeShield(Scene *scene)
{
    UpgradeScene *s = dynamic_cast<UpgradeScene *>(scene);
    if(s == NULL)
        throw logic_error("Une upgrade scene est attendue.");
    if(s->buy(exp((s->getPlayers()[0]->getShieldLevel()-1))+249) == false)
        return;
    for(unsigned int i= 0; i<s->getPlayers().size(); i++)
    {
        EntityPlayer *e = s->getPlayers()[i];
        e->setShieldLevel(e->getShieldLevel()+1);
        e->setShield(e->getShield()+exp(-0.08*e->getShieldLevel()+1));
    }

}

std::vector<EntityPlayer*> &UpgradeScene::getPlayers()
{
    return m_players;
}

bool UpgradeScene::buy(const int amount)
{
    if(m_score - amount < 0)
    {
        //Affichage du message de deni
        RenderText *txt = View::getRenderText("message");
        if(txt != NULL)
        {
            txt->setText("Nope.");
        }
        return false;
    }

    m_score -= amount;
    for(unsigned int i = 0; i<m_players.size(); i++)
    {
        m_players[i]->setPoints(m_score/m_players.size());
    }

    //affichage du message de remerciement
    RenderText *txt = View::getRenderText("message");
    if(txt != NULL)
    {
        txt->setText("Thx.");
    }
    return true;
}


bool UpgradeScene::inputUpdate()
{
    bool done = false;


    Menu *menu = getCurrentMenu();
    if(menu == NULL)
        return done;

    //Gestion des évenements
    sf::Event event;
    while(View::getEvent(event))
    {
        if(event.Type == sf::Event::Closed)
            done = true;

    }

    //Gestion des entrées au clavier
    const sf::Input &input = View::getInput();
    if(input.IsKeyDown(sf::Key::Down))
    {
        menu->changeOption(1);
        usleep(100000);
    }
    else if(input.IsKeyDown(sf::Key::Up))
    {
        menu->changeOption(-1);
        usleep(100000);
    }
    else if(input.IsKeyDown(sf::Key::Return))
    {
                        View::playSoundEffect(View::getSoundBonus());
        menu->select();
        usleep(100000);
    }
    return done;
}


string UpgradeScene::toString() const
{
    system("clear");
    stringstream s;
    s << "Upgrade Scene " << m_score << " points"  << endl << "=================" << endl;
    for(vector<Menu*>::const_iterator it=m_menuList.begin(); it != m_menuList.end(); it++)
    {
        //Affichage dans le terminal
        //TODO: à supprimer avant release
        if((*it)->getActive())
        {
            s << (*it)->toString() << endl;
        }
    }
    return s.str();
}
