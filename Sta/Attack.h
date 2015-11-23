#ifndef ATTACK_H
#define ATTACK_H

#include <string>
#include <sstream>
#include <cmath>

#include "Const.h"
#include "SpaceShip.h"

class SpaceShip;
class Level;

class Attack : public EntityMoving
{

private:
    //Dommages infligés par l'attaque
	int m_damages;
	//Lanceur de l'attaque
	SpaceShip *m_owner;

public:

    /** \brief Créer une nouvelle attaque
     *
     * \param lanceur
     * \param x du vecteur initial de direction
     * \param y du vecteur initial de direction
     *
     */
	Attack(SpaceShip *owner, float directionX, float directionY);

    /** \brief hit
     *  Définit la réaction lors de la rencontre avec une autre attaque
     * \param source Attack*
     * \return void
     *
     */
    void hit(Attack *source);


    /** \brief hurtEnemy
     *  Définit la réaction lorsque l'attaque courante rencontre une entitée
     * \param other Entity&
     * \return void
     *
     */
	void hurtEnemy(Entity &other);


    /** \brief collidWith
     * Réalise le test de collision et initialise la réaction
     * \param other Entity&
     * \return bool true si collision, false sinon
     *
     */
	bool collidWith(Entity &other);

    /** \brief update
     *  Met à jour l'entité
     * \return void
     *
     */
    void update();

    /** \brief getDamages
     * accesseur de dommages (get)
     * \return int dommages infligés par l'attaque courante
     *
     */
    int getDamages() const;

    /** \brief setDamages
     * accesseur de dommages (set)
     * \param damages const int
     * \return void
     *
     */
    void setDamages(const int damages);

    /** \brief toString()
     * Affiche les informations relatives à l'attaque courante
     * \return std::string informations sur l'attaque courante
     *
     */
	std::string toString() const;



    /** \brief getOwner
     *  Retourne un pointeur vers le lanceur de ce missle
     * \return SpaceShip* propriétaire
     *
     */
	SpaceShip *getOwner() const;


};

#endif
