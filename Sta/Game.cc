#include "Game.h"


using namespace std;

Scene *Game::currentScene = NULL;
bool Game::done = false;

void Game::initialize()
{
    done = false;
    currentScene = new TitleScene();

    Game::run();
}

void Game::run()
{

    std::chrono::time_point<std::chrono::system_clock> current, last;
    //Boucle de jeu principale et gestion des framerate
    current = std::chrono::system_clock::now();
    last = current;
    while(done == false)
    {
         current = std::chrono::system_clock::now();

        int time = std::chrono::duration_cast<std::chrono::milliseconds>(current-last).count();
        if(time > TIME_LAST_FRAME)
        {
            if(currentScene != NULL)
                done = currentScene->update();
            last = std::chrono::system_clock::now();
            //rendu du jeu
            View::draw();
        }
    }
}

void Game::changeScene(Scene *scene)
{
    delete currentScene;
    currentScene = scene;
}

void Game::quit()
{
    done = true;
}

void Game::destroy()
{
    delete currentScene;
}

bool Game::isFinished()
{
    return done;
}
