#ifndef ENTITYMOVING_H
#define ENTITYMOVING_H

#include "Entity.h"
#include <string>
#include <iostream>
#include <sstream>

#include "Const.h"


class EntityMoving : public Entity
{
private:
    //velocité x
    float m_velocityX;
    //velocity y
    float m_velocityY;

public:
    /** \brief EntityMoving
     * Créer une nouvelle entité pouvant se déplacer à l'écran
     * \param x int position x
     * \param y int position y
     * \param width in largeur de l'entité
     * \param height int hauteur de l'entité
     * \param imageFile std::string fichier image à utiliser pour représenter l'ennemi
     *
     */
    EntityMoving(int x, int y, int width, int height, std::string imageFile);


    /** \brief setVelocityX
     * règle la vélocité x
     * \param x const float nouvelle vélocity
     * \return void
     *
     */
    void setVelocityX(const float x);


    /** \brief setVelocityY
     * règle la vélocité y
     * \param y const float nouvelle vélocité y
     * \return void
     *
     */
    void setVelocityY(const float y);


    /** \brief getVelocityX
     * retourne la vélocité x
     * \return float vélocité x
     *
     */
    float getVelocityX() const;

    /** \brief getVelocityY
     * retourne la vélocité y
     * \return float vélocité
     *
     */
    float getVelocityY() const;

    /** \brief update
     * Met à jour les informations de l'entité
     * \return virtual void
     *
     */
    virtual void update();
    /** \brief moveTo
     *Demande à l'entité de se rendre à la position donnée
     * \param x const int position x de la cible à atteindre
     * \param y const int position y de la cible à atteindre
     * \return void
     *
     */
    void moveTo(const int x, const int y);


    /** \brief move
     * rçgle la vélocité
     * \param x const int nouvelle vélocité x
     * \param y const int nouvelle vélocité y
     * \return virtual void
     *
     */
    virtual void move(const int x, const int y);

    /** \brief toString
     * retourne un string contenant l'ensemble des informations sur l'entité
     * \return virtual std::string ensemble des informations
     *
     */
    std::string toString() const;

};


#endif // ENTITYMOVING_H
