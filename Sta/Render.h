#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Render
{
protected:

    //Sprite allant etre affiché
    sf::Sprite m_sprite;

    //Image du sprite
    sf::Image m_image;

    //index de frame du render
    float m_frame;

    //Vitesse d'annimation du render
    float m_speed;

    //Largeur de la vignette d'animation du render
    int m_width;

    //Hauteur de la vignette d'animation du render
    int m_height;
public:

    Render();

    Render(std::string file);

    Render(std::string file, int width, int height, float speed);

    virtual ~Render();

    /** \brief setSpeed
     * change la vitesse d'animation du render
     * \param speed float
     * \return void
     *
     */
    void setSpeed(float speed);

    /** \brief draw
     * Dessine le render à l'écran
     * \param window sf::RenderWindow*
     * \return virtual void
     *
     */
    virtual void draw(sf::RenderWindow *window)=0;

    /** \brief getX
     * Retourne la position x du render
     * \return int
     *
     */
    int getX() const;


    /** \brief getY
     * Retourne la position y du render
     * \return int
     *
     */
    int getY() const;
};

#endif
