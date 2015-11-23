#include "TitleScene.h"

using namespace std;


TitleScene::TitleScene()
{


    //Affichage du fond d'écran
    RenderEffect *background = new RenderEffect("assets/background.png", 0,0,WINDOW_WIDTH,WINDOW_HEIGHT, 0);
    View::addRender(background);
    //Affichage titre
    RenderText *txt = new RenderText("title", "StarFall", WINDOW_WIDTH /2, 100, 64, true);
    View::addRender(txt);

    Menu *main_menu = new Menu(this,WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT - 250, 200, 128);
    main_menu->addEntry("1 Joueur", &changeToGameSceneAlone);
    main_menu->addEntry("Scores", &showScore);
    main_menu->addEntry("Quitter", &quit);
    m_menuList.push_back(main_menu);
    RenderMenu *render = new RenderMenu(main_menu);
    View::addRender(render);
}

bool TitleScene::update()
{
    //Affichage en mode console
    ////cout << toString() << endl;
    bool done = inputUpdate();
    if(Game::isFinished())
        done = true;
    return done;
}

bool TitleScene::inputUpdate()
{
    //Affichage en mode console
    ////cout << "1.Monter 2.Descendre 3.Valider" << endl;

    bool done = false;

    //permet les interractions avec le menu
    Menu *menu = getCurrentMenu();
    if(menu == NULL)
        return done;
    //cout << menu->toString() << endl;

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


void TitleScene::changeToGameSceneAlone(Scene *scene)
{
    View::clearRenders();
    Scene *n = new GameScene(GAME_SEED_INIT, 1);
    Game::changeScene(n);
}

void TitleScene::showScore(Scene *scene)
{
    scene->getMenuList()[0]->setActive(false);
    Menu* sc = new Menu(scene, WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2-150, 200,300);
    vector<int> scores = ScoreHelper::readScores();
    unsigned int siz = 5;
    if(scores.size() < siz)
        siz = scores.size();
    for(unsigned int i =0; i<siz; i++)
    {
        stringstream s;
        s << (i+1) << ". " << scores[i];
        sc->addEntry(s.str(), NULL);
    }
    sc->addEntry("Reset", &resetScore);
    sc->addEntry("Close", &closeScore);
    RenderMenu *render = new RenderMenu(sc);
    View::addRender(render);
    scene->getMenuList().push_back(sc);

}

void TitleScene::resetScore(Scene *scene)
{
    ScoreHelper::resetSaveFile();
    closeScore(scene);
}

void TitleScene::closeScore(Scene *scene)
{
    View::removeRender(scene->getMenuList()[scene->getMenuList().size()-1]);
    delete scene->getMenuList()[scene->getMenuList().size()-1];
    scene->getMenuList().pop_back();
    scene->getMenuList()[0]->setActive(true);
}

void TitleScene::quit(Scene *scene)
{
    View::clearRenders();
    Game::quit();
}

string TitleScene::toString() const
{
    system("clear");
    stringstream s;
    s << "Ecran titre" << endl << "=================" << endl;
    for(vector<Menu*>::const_iterator it=m_menuList.begin(); it != m_menuList.end(); it++)
    {
        //Affichage dans le terminal
        if((*it)->getActive())
        {
            s << (*it)->toString() << endl;
        }
    }
    return s.str();
}
