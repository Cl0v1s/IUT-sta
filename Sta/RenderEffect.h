#ifndef RENDEREFFECT_H
#define RENDEREFFECT_H

#include <iostream>
#include <string>

#include <SFML/Window.hpp>

#include "Render.h"
#include "View.h"

class RenderEffect : public Render
{
private:


    //Render "parent"
    Render *m_render;

    //position x du render
    float m_x;

    //position y du render
    float m_y;

    //velocité du render
    int m_velocityX;
    int m_velocityY;
public:

    //Vitesse d'annimation par defaut des renderEffect
    static float defaultSpeed;

    RenderEffect(std::string file, int deg, Render *render);
    RenderEffect(std::string file, int width, int height, int deg, Render *render);
    RenderEffect(std::string file, int x, int y, int width, int height,int deg,  Render *render);
    RenderEffect(std::string file, int x, int y, int width, int height, int deg);
    RenderEffect(std::string file, int x, int y, int width, int height, int deg, float speed);


    /** \brief draw
     * Dessine le render à l'écran
     * \param window sf::RenderWindow*
     * \return void
     *
     */
    void draw(sf::RenderWindow *window);

    /** \brief getRender
     * Retourne l'eventuel render parent de l'entité
     * \param
     * \param
     * \return
     *
     */

    Render *getRender() const;


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


    /** \brief setX
     * Règle la position x du render
     * \param x const int
     * \return void
     *
     */
    void setX(const int x);


    /** \brief setY
     * Règle la position y du render
     * \param y const int
     * \return void
     *
     */
    void setY(const int y);

    /** \brief setVelocity
     * Règle la velocité du render
     * \param
     * \param
     * \return
     *
     */

    void setVelocity(const int x, const int y);

};

#endif
