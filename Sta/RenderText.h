#ifndef RENDERTEXT_H
#define RENDERTEXT_H

#include <string>
#include <iostream>

#include <SFML/Window.hpp>

#include "Render.h"

class RenderText : public Render
{
private:

    //police d'affichage
    sf::Font m_font;

    //vrai si le texte doit etre centré par rapport à sa position
    bool m_centered;

    //texte du render
    std::string m_string_text;

    //label du render afin d'être en mesure de l'identifier
    std::string m_label;

    //texte permettant le rendu sfml
    sf::String m_text;

    //position x du render
    int m_x;

    //position y du render
    int m_y;

    //Taille de la police d'affichage
    int m_size;
public:
    RenderText(std::string label, std::string text, int x, int y, int size, bool centered);


    /** \brief draw
     * Affiche le render courant
     * \param window sf::RenderWindow*
     * \return void
     *
     */
    void draw(sf::RenderWindow *window);


    /** \brief getText
     * Retourne le texte affiché par le render
     * \return std::string
     *
     */
    std::string getText() const;


    /** \brief setText
     * Permet de changer le texte affiché par le render
     * \param text const std::string
     * \return void
     *
     */
    void setText(const std::string text);


    /** \brief getLabel
     * Retourne le label "identifiant" du render
     * \return std::string
     *
     */
    std::string getLabel() const;
};

#endif
