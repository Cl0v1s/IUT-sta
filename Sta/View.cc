#include "View.h"

sf::RenderWindow *View::window;
std::vector<Render*> View::m_renders;
bool View::enableSound;
sf::Music *View::music;
sf::Sound *View::sound;

sf::SoundBuffer *View::bonus;
sf::SoundBuffer *View::explosion;
sf::SoundBuffer *View::fire;
sf::SoundBuffer *View::hurt;


void View::Initialize()
{
    enableSound = true;
    music = new sf::Music;
    music->OpenFromFile(MUSIC_FILE);
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Starfall", sf::Style::Close);

    sound = new sf::Sound;
    sound->SetLoop(false);

    //chargementdes effets sonores
    bonus = new sf::SoundBuffer;
    fire = new sf::SoundBuffer;
    explosion = new sf::SoundBuffer;
    hurt = new sf::SoundBuffer;


    bonus->LoadFromFile("assets/bonus.ogg");
    fire->LoadFromFile("assets/fire.ogg");
    explosion->LoadFromFile("assets/explosion.ogg");
    hurt->LoadFromFile("assets/hurt.ogg");
}

void View::playSoundEffect(sf::SoundBuffer *buffer)
{
    //Si le son est activé
    if(View::enableSound)
    {
        View::sound->SetBuffer(*buffer);
        View::sound->Play();
    }
}

void View::Destroy()
{
    //Supression des effets sonores
    delete View::explosion;
    delete View::fire;
    delete View::bonus;
    delete View::hurt;

    //Supression des autres élements de la View
    delete View::sound;
    delete View::music;
    delete View::window;
}

void View::addRender(Render* render)
{
    m_renders.push_back(render);
}

bool View::removeRender(Render* render)
{
    std::vector<Render*>::iterator it = std::find(m_renders.begin(), m_renders.end(), render);
    if(it != m_renders.end())
    {
        removeRenderEffect(render);
        delete (*it);
        m_renders.erase(it);
        return true;
    }
    return false;
}

bool View::removeRender(Menu *menu)
{
    unsigned int i = 0;
    bool f = false;
    while(i<m_renders.size() && !f)
    {
        RenderMenu* render = dynamic_cast<RenderMenu*>(m_renders[i]);
        if(render != NULL)
        {
            if(render->getMenu()  == menu)
            {
                f = removeRender(m_renders[i]);
            }
        }
        i++;
    }
    return f;
}

bool View::removeRender(std::string text)
{
    unsigned int i = 0;
    bool f = false;
    while(i<m_renders.size() && !f)
    {
        RenderText* render = dynamic_cast<RenderText*>(m_renders[i]);
        if(render != NULL)
        {
            if(render->getText()  == text)
            {
                f = removeRender(m_renders[i]);
            }
        }
        i++;
    }
    return f;
}

RenderText* View::getRenderText(std::string text)
{
    RenderText *res = NULL;
    unsigned int i = 0;
    while(i<m_renders.size() && res == NULL)
    {
        RenderText* render = dynamic_cast<RenderText*>(m_renders[i]);
        if(render != NULL)
        {
            if(render->getLabel() == text)
            {
                res = render;
            }
        }
        i++;
    }
    return res;
}

void View::removeRenderEffect(Render *render)
{
    unsigned int i = 0;
    bool f = false;
    while(i<m_renders.size() && !f)
    {
        RenderEffect* render = dynamic_cast<RenderEffect*>(m_renders[i]);
        if(render != NULL)
        {
            if(render->getRender()  == render)
            {
                f = removeRender(m_renders[i]);
            }
        }
        i++;
    }
}

bool View::removeRender(Entity *entity)
{
    unsigned int i = 0;
    bool f = false;
    while(i<m_renders.size() && !f)
    {
        RenderEntity* render = dynamic_cast<RenderEntity*>(m_renders[i]);
        if(render != NULL)
        {
            if(render->getEntity()  == entity)
            {
                f = removeRender(m_renders[i]);
            }
        }
        i++;
    }
    return f;
}

void View::clearRenders()
{
    for(unsigned int i = 0; i< m_renders.size(); i++)
    {
        delete m_renders[i];
    }
    m_renders.clear();
}

void View::draw()
{
    if(View::enableSound == false && View::music->GetStatus() == sf::Music::Status::Playing)
        stopMusic();
    else if(View::enableSound==true && View::music->GetStatus() == sf::Music::Status::Stopped)
        playMusic();
    window->Clear();
    for(unsigned int i = 0; i<m_renders.size(); i++)
    {
        m_renders[i]->draw(window);
    }
    window->Display();

}

const sf::Input& View::getInput()
{
    return window->GetInput();
}

bool View::getEvent(sf::Event &event)
{
    return window->GetEvent(event);
}

void View::playMusic()
{
    View::music->Play();
}

void View::pauseMusic()
{
    View::music->Pause();
}

void View::stopMusic()
{
    View::music->Stop();
}

sf::SoundBuffer* View::getSoundFire()
{
    return fire;
}

sf::SoundBuffer* View::getSoundExplosion()
{
    return explosion;
}

sf::SoundBuffer* View::getSoundHurt()
{
    return hurt;
}


sf::SoundBuffer* View::getSoundBonus()
{
    return bonus;
}




