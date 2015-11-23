#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <vector>
#include <string>
#include <sstream>

#include "EntityMoving.h"
#include "Attack.h"

class SpaceShip : public EntityMoving
{
private:
    //puissance de feu de l'entité
	float m_firePower;
	//puissance de bouclier
	float m_shield;
	//vitesse de tir
	float m_fireSpeed;
	//vitesse de déplacement
	float m_movingSpeed;
protected:
    //compteur d'interval de tir
    int m_fireCount;


public:
    /** \brief Spaceship
     * Créer une nouvelle entité detype vaisseau
     * \param x int position x
     * \param y int position y
     * \param width int largeur
     * \param height int hauteur
     * \param imageFile std::string fichier image à utiliser pour représenter l'entité
     *
     */
    SpaceShip(int x, int y, int width, int height, std::string imageFile);

    /** \brief fire
     * Permet à l'entité de tirer
     * \param entities std::vector<Attack*>& Liste des attaques du niveau afin de permettre d'ajouter un nouveau tir
     * \return void
     *
     */
    virtual bool fire(std::vector<Attack *> &entities) = 0;

    /** \brief hit
     * Définit la réaction de l'entité lorsque elle est touchée par un tir
     * \param source Attack* Tir touchant l'entité
     * \return void
     *
     */
    virtual void hit(Attack *source);

    /** \brief update
     *  Met à jour les informations de l'entité
     * \return void
     *
     */
    virtual void update();

    /** \brief setFirePower
     * ermet de changer la puissance de feu de l'entité
     * \param a const int Nouvelle piussancede feu
     * \return void
     *
     */
	void setFirePower(const float a);

    /** \brief getFirePower
     * Permet de récupérer la puissance de feu de l'entité
     * \return int puissance de feu de l'entité
     *
     */
	float getFirePower() const;

    /** \brief getShield
     * Permet de changer la puissance  de bouclier de l'entité
     * \param a const int Nouvelle puissance de bouclier
     * \return void
     *
     */
	void setShield(const float a);

    /** \brief getShield
     * permet de récupérer la puissance de bouclier de l'entité
     * \return int puissance de bouclier
     *
     */
	float getShield() const;

    /** \brief setireSpeed
     * Permet de chnger la vitesse de tir de l'entité
     * \param a const int Nouvelle vitesse de tir
     * \return void
     *
     */
	void setFireSpeed(const float a);

    /** \brief getFireSpeed
     * permet de récupérer la vitesse de tir de l'entité
     * \return int Vitesse de tir
     *
     */
	float getFireSpeed() const;

    /** \brief setMovingSpeed
     * Permet de changer la vitesse de déplacement de l'entité
     * \param a const int Nouvelle vitesse de déplaement
     * \return void
     *
     */
	void setMovingSpeed(const float a);

    /** \brief getMovingSpeed
     * Permet de récupérer la vitesse de déplacement de l'entité
     * \return int vitesse de déplacement
     *
     */
	float getMovingSpeed() const;

    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur l'entité
     * \return std::string informations
     *
     */
	std::string toString() const;

};


#endif // SPACESHIP_H
