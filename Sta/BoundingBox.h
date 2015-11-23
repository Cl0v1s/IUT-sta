#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <sstream>
#include <string>

#include "Const.h"

class EntityMoving;

class BoundingBox
{

friend class EntityMoving;


private:
    //position x de la bounding box
    float m_x;
    //position y de la bounding box
    float m_y;
    //largeur de la bounding box
    int m_width;
    //hauteur de la bounding box
    int m_height;

    //"densité" unité de mesure propre au jeu à user en cas de dommages lors de la collision avec la bounding box
    //Plus l'objet est imposant (et la bounding box grande) plus ola densité est élevée
    int m_density;

public:
    /** \brief BoundingBox
     *  Rectanfgle représentant une zone pouvant entrer en collision avec une autre zone
     * \param x int position de la box
     * \param y int position de la box
     * \param width int largeur de la box
     * \param height int hauteur de la box
     *
     */
    BoundingBox(int x, int y, int width, int height);

    /** \brief intersects
     * vérifie si la bounding box courante coupe la bounding box passée en paramètre
     * \param other const BoundingBox& bounding box à tester
     * \return bool vrai si il y a intersection, faux sinon
     *
     */
    bool intersects(const BoundingBox &other);

    /** \brief getDensity
     * Accesseur de densité (get)
     * \return int densité de la boundingbox
     *
     */
    int getDensity() const;


    /** \brief setDensity
     *  Accesseur de densité (set)
     * \param x const int nouvelle densité de la boundingbox
     * \return void
     *
     */
    void setDensity(const int x);

    /** \brief getX
     * accesseur de position x (get)
     * \return int position x
     *
     */
    int getX() const;

    /** \brief setX
     * accesseur de position x (set)
     * \param x const float nouvelle position x
     * \return void
     *
     */
    void setX(const float x);

    /** \brief getY
     * accesseur de position y (get)
     * \return int position y
     *
     */
    int getY() const;

    /** \brief setY
     * accesseur de position y (set)
     * \param y const float nouvelle position y
     * \return void
     *
     */
    void setY(const float y);

    /** \brief getWidth
     * accesseur de largeur (get)
     * \return int largeur
     *
     */
    int getWidth() const;

    /** \brief setWidth
     * accesseur de largeur (set)
     * \param width const float nouvelle largeur
     * \return void
     *
     */
    void setWidth(const int width);

    /** \brief getHeight
     * accesseur de hauteur (get)
     * \return int hauteur
     *
     */
    int getHeight() const;

    /** \brief setHeight
     * accesseur de position hauteur (set)
     * \param height const float nouvelle hauteur
     * \return void
     *
     */
    void setHeight(const int height);

    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur la bounding box courante
     * \return std::string ensemble des informations
     *
     */
    std::string toString() const;


    /** \brief inScreen
     * Retourne vrai si a bounding box est dans l'écran
     * \return bool
     *
     */
    bool inScreen() const;




};


#endif // BOUNDING_BOX_H
