#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <sstream>

#include "BoundingBox.h"

class Attack;

class Entity
{

friend class RenderEntity;

private:
    //permet de reconnaitre le type de l'entité sans avoir à réaliser de cast.
    // 0: Entity de base
    // 1: Player
    // 2: EasyEnemy
    // 3 : Medium" "
    // 4 : Hard" "
    // 5 : Attack
    // 6 : Obstacle
    int m_type;

    //Fichier d'image allant etre utilisé pour sa représentation à l'écran
    std::string m_imageFile;

    //Points de vie de l'entité
    int m_life;

    //Valeur, en points de l'entité à ajouter un score du joueur lorsque celui-ci élimine l'entité
    int m_valueInPoints;

protected:
    //Zone collisionable (on use pas de SFML rectangle car nous avions besoin de position en float et noçn en int
    BoundingBox m_box;

public:
    /** \brief Entity
     * Créer un nouvelle entité
     * \param x int position x
     * \param y int position y
     * \param width int largeur de l'entité
     * \param height int hauteur de l'entité
     * \param imageFile std::string  fichier image à utiliser lors du dessin de l'entité
     *
     */
    Entity(int x, int y, int width, int height, std::string imageFile);


    virtual ~Entity();


    /** \brief changePosition
     * change la position de l'entité aux coordonnée transmises
     * \param x const int nouvelle position x de l'entité
     * \param y const int nouvelle position y de l'entité
     * \return void
     *
     */
    void changePosition(const int x,const int y);

    /** \brief getLife
     * Retourne le nombre de points de vie de l'entité
     * \return int nombre de points de vie de l'entité
     *
     */
    int getLife() const;
    /** \brief setLife
     * permet de changer le nombre de pints de vie du joueur
     * \param amount const int nouveau nombre de points de vie
     * \return void
     *
     */
    void setLife(const int amount);

    /** \brief getValueInPoints
     * retourne la valeur en points de l'entité
     * \return int valeur en points de l'entité
     *
     */
    int getValueIntPoints() const;

    /** \brief setValueInPoints
     * change la valeur en points de l'entité
     * \param amount const int Nouvelle valeur en points de l'entité
     * \return void
     *
     */
    void setValueInPoints(const int amount);

    /** \brief getBoundingBox
     * Retourne la zone collisionnable de l'entité
     * \return BoundingBox zone collisionable
     *
     */
    BoundingBox getBoundingBox() const;

    /** \brief update
     * Met à jour l'entité
     * \return virtual void
     *
     */
    virtual void update() = 0;
    /** \brief collidWith
     * Test si il y a collisiobn avec l'entité passée en paramètre et détermine l'action de l'entité si il y a collision
     * \param other Entity& Entité à tester
     * \return virtual bool vrai si collision, faux sinon
     *
     */
    virtual bool collidWith(Entity &other);

    /** \brief hit
     * Définit l'action de l'entité lors de la collision avec une attaque
     * \param source Attack* attaque encaissée
     * \return virtual void
     *
     */
    virtual void hit(Attack* source) = 0;

    /** \brief hurtEnemy
     * Définit l'action de l'entité lorsqu'elle blesse l'entité transmise
     * \param other Entity& entité bléssée par l'entité courante
     * \return virtual void
     *
     */
    virtual void hurtEnemy(Entity &other);

    /** \brief toString
     * retourne un string contenant l'ensemble des informations sur l'entité
     * \return virtual std::string ensemble des informations
     *
     */
    virtual std::string toString() const;

    /** \brief setType
     * Permet de régler le type de l'entité
     * \param type const int
     * \return void
     *
     */
    void setType(const int type);


    /** \brief getType
     * Retourne le type de l'entité
     * \return int
     *
     */
    int getType() const;
};

#endif // ENTITY_H
