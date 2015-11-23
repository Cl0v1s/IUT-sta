#ifndef RENDERMENU_H
#define RENDERMENU_H

#include <vector>

#include <SFML/System.hpp>

#include "Render.h"
#include "Menu.h"

class RenderMenu : public Render
{
private:

    //menu associé à ce render
    Menu *m_menu;

    //Police d'affichage
    sf::Font m_font;

    //Liste d'iage permettant d'afficher un fond de menu adaptable
    std::vector<sf::Sprite*> background;
public:
    RenderMenu(Menu *menu);

    /** \brief getMenu
     * Retourne le menu associé à ce render
     * \return Menu*
     *
     */
    Menu* getMenu() const;

    ~RenderMenu();


    /** \brief draw
     * Dessine le render courant
     * \param window sf::RenderWindow*
     * \return void
     *
     */
    void draw(sf::RenderWindow *window);

};
#endif // RENDERMENU_H
