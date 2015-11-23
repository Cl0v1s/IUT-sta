#include "GameScene.h"

using namespace std;

GameScene::GameScene(const int seed, const int players) : m_level(seed)
{
    m_isPaused = false;
    m_seed = seed;


    //Affichage du fond d'Ã©cran de jeu
    RenderEffect *background = new RenderEffect("assets/background.png", 0,0,WINDOW_WIDTH,WINDOW_HEIGHT, 0);
    View::addRender(background);
    m_backgrounds.push_back(background);
    RenderEffect * background2  =new RenderEffect("assets/background.png", WINDOW_WIDTH,0,WINDOW_WIDTH,WINDOW_HEIGHT,0);
    View::addRender(background2);
    m_backgrounds.push_back(background2);


    for(int i=0; i<players; i++)
    {
        //Les players instanciÃ©s ici seront delete lors de l'implÃ©mentation des options du menu pause.
        EntityPlayer *player = new EntityPlayer(0, WINDOW_HEIGHT/2-25 - ((players-1) *50) + i*25);
        m_players.push_back(player);
        m_level.addPlayer(player);
        RenderEntity *render = new RenderEntity(player);
        View::addRender(render);
    }

    //Affichage gui
    //Icone de la vie du joueur 1
    RenderEffect *life = new RenderEffect("assets/life.png", 10,10,32,32,0);
    View::addRender(life);
    //Affichage de nombre de points de vie du joueur 1
    RenderText *lifePoints = new RenderText("life_1", to_string(m_players[0]->getLife()), 52, 10, 32, false);
    View::addRender(lifePoints);

    if(m_players.size() > 1)
    {
        //ICone de la vie du joueur 2
        life = new RenderEffect("assets/life.png", 64,10,32,32,0);
        View::addRender(life);
        //Affichage de nombre de points de vie du joueur 1
        lifePoints = new RenderText("life_2", to_string(m_players[1]->getLife()), 106, 10, 32, false);
        View::addRender(lifePoints);
    }
    //Affichage du nombre de points total
    unsigned int total = 0;
    unsigned int combos = 0;
    for(unsigned int i = 0; i<m_players.size(); i++)
    {
        total += m_players[i]->getPoints();
        combos += m_players[i]->getCombo();
    }
    total = total / m_players.size();
    RenderText *text = new RenderText("points", to_string(total)+" points", 10, WINDOW_HEIGHT - 26, 16, false);
    View::addRender(text);
    text = new RenderText("level", "Niveau "+to_string(m_level.getLevelNumber()), 10, WINDOW_HEIGHT - 62, 16, false);
    View::addRender(text);
    text = new RenderText("combo", "x"+to_string(combos), 10, 62, 16, false);
    View::addRender(text);




}

GameScene::GameScene(const int seed, vector<EntityPlayer*> players) : Scene(), m_level(seed)
{

    //Affichage du fond d'Ã©cran de jeu
    RenderEffect *background = new RenderEffect("assets/background.png", 0,0,WINDOW_WIDTH,WINDOW_HEIGHT, 0);
    View::addRender(background);
    m_backgrounds.push_back(background);
    RenderEffect * background2  =new RenderEffect("assets/background.png", WINDOW_WIDTH,0,WINDOW_WIDTH,WINDOW_HEIGHT,0);
    View::addRender(background2);
    m_backgrounds.push_back(background2);

    m_isPaused = false;
    m_seed = seed;
    for(unsigned int i=0; i<players.size(); i++)
    {
        players[i]->enablePowerMode();
        players[i]->savePointsToMoney();
        m_players.push_back(players[i]);
        m_level.addPlayer(players[i]);
        RenderEntity *render = new RenderEntity(players[i]);
        View::addRender(render);
    }




    //Affichage gui
    //Icone de la vie du joueur 1
    RenderEffect *life = new RenderEffect("assets/life.png", 10,10,32,32,0);
    View::addRender(life);
    //Affichage de nombre de points de vie du joueur 1
    RenderText *lifePoints = new RenderText("life_1", to_string(m_players[0]->getLife()), 52, 10, 32, false);
    View::addRender(lifePoints);

    if(m_players.size() > 1)
    {
        //ICone de la vie du joueur 2
        life = new RenderEffect("assets/life.png", 64,10,32,32,0);
        View::addRender(life);
        //Affichage de nombre de points de vie du joueur 1
        lifePoints = new RenderText("life_2", to_string(m_players[1]->getLife()), 106, 10, 32, false);
        View::addRender(lifePoints);
    }
    //Affichage du nombre de points total
    unsigned int total = 0;
    unsigned int combos = 0;
    for(unsigned int i = 0; i<m_players.size(); i++)
    {
        combos += m_players[i]->getCombo();
        total += m_players[i]->getPoints();
    }
    total = total / m_players.size();
    RenderText *text = new RenderText("points", to_string(total)+" points", 10, WINDOW_HEIGHT - 26, 16, false);
    View::addRender(text);
    text= new RenderText("level", "Niveau "+to_string(m_level.getLevelNumber()), 10, WINDOW_HEIGHT - 62, 16, false);
    View::addRender(text);
    text = new RenderText("combo", "x"+to_string(combos), 10, 62, 16, false);
    View::addRender(text);
}



bool GameScene::update()
{
    bool done = inputUpdate();



    //Mise Ã  jour de la gui
    //Mise Ã  jour des points de vie
    for(unsigned int i = 0; i<m_players.size(); i++)
    {
        RenderText *rdrtxt = View::getRenderText("life_"+to_string(i+1));
        if(rdrtxt != NULL)
            rdrtxt->setText(to_string(m_players[i]->getLife()));
    }
    //Affichage du nombre de points total et de combo totaux
    unsigned int total = 0;
    unsigned int combos = 0;
    for(unsigned int i = 0; i<m_players.size(); i++)
    {
        total += m_players[i]->getPoints();
        combos += m_players[i]->getCombo();
    }
    total = total / m_players.size();

    RenderText *rdrtxtp =  View::getRenderText("level");
    if(rdrtxtp != NULL)
        rdrtxtp->setText("Niveau "+to_string(m_level.getLevelNumber()));
    rdrtxtp =  View::getRenderText("points");
    if(rdrtxtp != NULL)
        rdrtxtp->setText(to_string(total)+" points");
    rdrtxtp = View::getRenderText("combo");
    if(rdrtxtp != NULL)
    {
        if(combos < 20)
            rdrtxtp->setText("x"+to_string(combos)+"/20");
        else
            rdrtxtp->setText("Canons charges !");
    }


    //Si le jeu est en pause alors on ne met pas Ã  jour les entitÃ©s
    if(m_isPaused == false)
    {
        //Mise Ã  jour de la position du fond
        for(unsigned int i = 0; i< m_backgrounds.size(); i++)
        {
            m_backgrounds[i]->setX(m_backgrounds[i]->getX()-1);
            if(m_backgrounds[i]->getX() <= -WINDOW_WIDTH)
                m_backgrounds[i]->setX(WINDOW_WIDTH);
        }
        int code = m_level.update();
        switch(code)
        {
            case GAME_WIN_CODE:
            {
                View::clearRenders();
                UpgradeScene *se = new UpgradeScene(m_seed, m_players);
                Game::changeScene(se);
                break;
            }
            case GAME_LOOSE_CODE:
            {

                View::clearRenders();
                GameOverScene *s = new GameOverScene(m_players);
                Game::changeScene(s);
                break;
            }
        }

    }
    //Si le jeu a recu l'ordre de quitter alors on force la scene Ã  quitter
    if(Game::isFinished())
        done = true;
    return done;
}

bool GameScene::inputUpdate()
{
    bool done = false;

    //Gestion des Ã©venements
    sf::Event event;
    while(View::getEvent(event))
    {
        if(event.Type == sf::Event::Closed)
            done = true;

    }

    //Gestion des entrÃ©es au clavier
    const sf::Input &input = View::getInput();
    if(!m_isPaused) //Si aucun menu n'existe / N'est actif
    {
        //Commandes joueur 1
        if(input.IsKeyDown(sf::Key::Down))
        {
                m_players[0]->setVelocityY(m_players[0]->getMovingSpeed());
        }
        if(input.IsKeyDown(sf::Key::Up))
        {
                m_players[0]->setVelocityY(-m_players[0]->getMovingSpeed());
        }
        if(input.IsKeyDown(sf::Key::Left))
        {
                m_players[0]->setVelocityX(-m_players[0]->getMovingSpeed());
        }
        if(input.IsKeyDown(sf::Key::Right))
        {
                m_players[0]->setVelocityX(m_players[0]->getMovingSpeed());
        }
        if(input.IsKeyDown(sf::Key::Space))
        {
            if (m_players[0]->fire(m_level.m_attacks))
                View::playSoundEffect(View::getSoundFire());
        }
        if(input.IsKeyDown(sf::Key::LShift))
        {
            if(m_players[0]->powerMode())
                View::playSoundEffect(View::getSoundBonus());
        }

        //TODO: Ajouter commandes du joueur 2

        //Affichage du menu pause
        if(input.IsKeyDown(sf::Key::Escape))
        {
                m_isPaused = true;
                Menu *pause = new Menu(this, WINDOW_WIDTH /2 - 150, WINDOW_HEIGHT /2 - 100, 300, 200);
                pause->addEntry("Relancer niveau", &restarLevel);
                pause->addEntry("Options", &showOptions);
                pause->addEntry("Quitter le jeu", &quitGame);
                pause->addEntry("Retour au jeu", &quitPause);
                m_menuList.push_back(pause);
                RenderMenu *render = new RenderMenu(pause);
                View::addRender(render);
                usleep(100000);
        }
    }
    else  //Commande des menus
    {
        //permet les interractions avec le menu actif (si il y a lieu)
        Menu *menu = getCurrentMenu();
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
        else if(input.IsKeyDown(sf::Key::Escape)) //Fermeture du menu pause
        {
                m_isPaused = false;
                //Appel de la mÃªme fonction que lors de la sÃ©lÃ©ction de retour dans le menu pause
                quitPause(this);
                usleep(100000);

        }
    }
    return done;
}

std::string GameScene::toString() const
{
    stringstream ss;
    ss << "0.Laisser passer x frames 1.Afficher joueurs 2.Afficher ennemis et obstacles" << endl << "3.Afficher attaques(tirs) 4.DÃ©placer joueur(s) vers un point donnÃ©"<< endl << "5.tirer 6.Tuer le joueur 7.Tuer un ennemi " << endl << "8.Detruire un obstacle 9.Gagner 10.Quitter";
    ss << endl << "Lors d'une action (4 et plus), pour constater son effet, veuillez laisser passerau moins une frame en suivant.";
    return ss .str();
}

void GameScene::removeActiveMenu()
{
    Menu *menu = getCurrentMenu();
    View::removeRender(menu);
    vector<Menu*>::iterator it = std::find(m_menuList.begin(), m_menuList.end(), menu);
    m_menuList.erase(it);
    delete menu;
}

void GameScene::manageSound(Scene *scene)
{
    if(View::enableSound)
    {
        scene->getCurrentMenu()->changeEntryName("Couper le son", "Activer le son");
        View::enableSound = false;
    }
    else
    {
        scene->getCurrentMenu()->changeEntryName("Activer le son", "Couper le son");
        View::enableSound = true;
    }


}

void GameScene::quitGame(Scene *scene)
{
    View::clearRenders();
    Game::quit();
}

void GameScene::quitPause(Scene *scene)
{
    GameScene *t = dynamic_cast<GameScene*>(scene);
    if(t != NULL)
    {
        t->m_isPaused = false;
        t->removeActiveMenu();
    }
}

void GameScene::restarLevel(Scene* scene)
{
    GameScene* s = dynamic_cast<GameScene*>(scene);
    //remise Ã  zÃ©ro du niveau
    s->m_level.reset();
    //fermeture du menu
    s->quitPause(scene);

}

void GameScene::showOptions(Scene* scene)
{
    scene->getMenuList()[0]->setActive(false);
    Menu* sc = new Menu(scene, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT/2-100, 300,200);
    if(View::enableSound)
        sc->addEntry("Couper le son", &manageSound);
    else
        sc->addEntry("Activer le son", &manageSound);
    sc->addEntry("Fermer", &closeOptions);
    RenderMenu *render = new RenderMenu(sc);
    View::addRender(render);
    scene->getMenuList().push_back(sc);
}

void GameScene::closeOptions(Scene *scene)
{
    GameScene *t = dynamic_cast<GameScene*>(scene);
    if(t != NULL)
    {
        //On supprime le menu courant (le menu de pause)
        t->removeActiveMenu();
        //On rÃ©activele menu prÃ©cÃ©dent
        scene->getMenuList()[0]->setActive(true);
    }
}


