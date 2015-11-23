#include "RenderMenu.h"

RenderMenu::RenderMenu(Menu* menu) : Render("assets/gui.png")
{
    m_menu = menu;
    //Chargement de la police d'affichage
    if(!m_font.LoadFromFile("assets/font.ttf"))
    {
        throw std::string("Unable to load font file.");
    }
    //COin supérieur Gauche
    sf::Sprite *topLeft = new sf::Sprite(m_image);
    topLeft->Move(m_menu->m_x+1-30, m_menu->m_y);
    topLeft->SetSubRect(sf::IntRect(0,0,32,32));
    //etirement pour corriger un problème de décalage
    topLeft->Resize(33,42);
    background.push_back(topLeft);
    //COin supérieur Droit
    sf::Sprite *topRight = new sf::Sprite(m_image);
    topRight->Move(m_menu->m_x+m_menu->m_width, m_menu->m_y);
    topRight->SetSubRect(sf::IntRect(64,0,96,32));
    //etirement pour corriger un problème de décalage
    topRight->Resize(32,42);
    background.push_back(topRight);
    //COin inférieur Gauche
    sf::Sprite *botLeft = new sf::Sprite(m_image);
    botLeft->Move(m_menu->m_x+1-30, m_menu->m_y+m_menu->m_height-1);
    botLeft->SetSubRect(sf::IntRect(0,64,32,96));
    botLeft->Resize(33,32);
    background.push_back(botLeft);
    //COin inférieur Droit
    sf::Sprite *botRight = new sf::Sprite(m_image);
    botRight->Move(m_menu->m_x+m_menu->m_width, m_menu->m_y+m_menu->m_height-1);
    botRight->SetSubRect(sf::IntRect(64,64,96,96));
    background.push_back(botRight);
    //Bordure supérieur
    sf::Sprite *top = new sf::Sprite(m_image);
    top->Move(m_menu->m_x, m_menu->m_y);
    top->SetSubRect(sf::IntRect(32,0,64,32));
    top->Resize(m_menu->m_width, 42);
    background.push_back(top);
    //Bordure inférieure
    sf::Sprite *bot = new sf::Sprite(m_image);
    bot->Move(m_menu->m_x, m_menu->m_y+m_menu->m_height-1);
    bot->SetSubRect(sf::IntRect(32,64,64,96));
    bot->Resize(m_menu->m_width, 32);
    background.push_back(bot);
    //Bordure Gauche
    sf::Sprite *left = new sf::Sprite(m_image);
    left->Move(m_menu->m_x+1-30, m_menu->m_y+30);
    left->SetSubRect(sf::IntRect(0,32,32,64));
    left->Resize(33, m_menu->m_height-32);
    background.push_back(left);
    //Bordure Droite
    sf::Sprite *right = new sf::Sprite(m_image);
    right->Move(m_menu->m_x+m_menu->m_width, m_menu->m_y+30);
    right->SetSubRect(sf::IntRect(64,32,96,64));
    right->Resize(32, m_menu->m_height-32);
    background.push_back(right);
    //Centre
    sf::Sprite *center = new sf::Sprite(m_image);
    center->Move(m_menu->m_x, m_menu->m_y+30);
    center->SetSubRect(sf::IntRect(32,32,64,64));
    center->Resize(m_menu->m_width, m_menu->m_height-32);
    background.push_back(center);
}

RenderMenu::~RenderMenu()
{
    for(unsigned int i = 0; i<background.size(); i++)
    {
        delete background[i];
    }
}

Menu* RenderMenu::getMenu() const
{
    return m_menu;
}

void RenderMenu::draw(sf::RenderWindow *window)
{
    if(!m_menu->getActive())
        return;
    //Affichage du fond du menu
    for(unsigned int i = 0; i<background.size(); i++)
    {
        window->Draw(*background[i]);
    }
    if(m_menu->m_options.size() > 0)
    {
        //Affichage des différentes options
        for(unsigned int i = 0; i<m_menu->m_options.size(); i++)
        {
            sf::String text;
            text.SetText(m_menu->m_options[i]);
            text.SetSize(16);
            text.SetFont(m_font);
            text.Move(m_menu->m_x+32, m_menu->m_y+32+i*32);
            window->Draw(text);
        }
        //Affichage du curseur
        sf::String text;
        text.SetText("-");
        text.SetSize(16);
        text.SetFont(m_font);
        text.Move(m_menu->m_x, m_menu->m_y+32+(m_menu->m_selected)*32);
        window->Draw(text);
    }

}
