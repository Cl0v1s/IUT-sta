#include "GameOverScene.h"

using namespace std;

GameOverScene::GameOverScene(vector<EntityPlayer *> players)
{

    //Affichage du fond d'écran
    RenderEffect *background = new RenderEffect("assets/background.png", 0,0,WINDOW_WIDTH,WINDOW_HEIGHT, 0);
    View::addRender(background);

    m_score = 0;
    for(unsigned int i=0; i<players.size(); i++)
    {
        m_score += players[i]->getPoints() + players[i] ->getMoney(); //On calcule la moyenne des points gagné par les deux joueurs
    }
    m_score = m_score / players.size();

    //sauvegarde du score
    m_classement = ScoreHelper::saveScore(m_score);
    //récupération du meilleur score
    m_bestScore  = ScoreHelper::getBestScore();

    Menu *menu = new Menu(this, WINDOW_WIDTH /2 -150, WINDOW_HEIGHT/2 - 100, 300,200);
    menu->addEntry("Jouer 1 joueur", &restartOnePlayer);
    //menu->addEntry("Restart 2 Player", &restartTwoPlayers); //TODO: a décommenter dans la version finale
    menu->addEntry("Retour au menu", &goToTitle);
    menu->addEntry("Quitter", &quit);
    m_menuList.push_back(menu);
    RenderMenu *render = new RenderMenu(menu);
    View::addRender(render);
    RenderText *text = new RenderText("gameover", "Game Over !", WINDOW_WIDTH /2, 100, 32, true);
    View::addRender(text);
}


void GameOverScene::restartOnePlayer(Scene *scene)
{

    View::clearRenders();
    GameScene *sc = new GameScene(GAME_SEED_INIT, 1);
    Game::changeScene(sc);
}

void GameOverScene::restartTwoPlayers(Scene *scene)
{
    GameScene *sc = new GameScene(GAME_SEED_INIT, 2);
    Game::changeScene(sc);
}

void GameOverScene::goToTitle(Scene *scene)
{
    View::clearRenders();
    TitleScene *sc = new TitleScene();
    Game::changeScene(sc);
}

void GameOverScene::quit(Scene *scene)
{
    View::clearRenders();
    Game::quit();
}

bool GameOverScene::update()
{
    bool done = inputUpdate();
    if(Game::isFinished())
        done = true;
    return done;
}


bool GameOverScene::inputUpdate()
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

string GameOverScene::toString() const
{
    system("clear");
    stringstream s;
    s << "Game Over Score total: " << m_score;
    if(m_score == m_bestScore)
        s << " Meilleur Score !";
    else
        s << " Classement: " << (m_classement+1);
    s << endl << "=================" << endl;
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
