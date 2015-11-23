#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H


#include <stdlib.h>
#include <vector>

#include "EntityMoving.h"
#include "Attack.h"

#include "View.h"
#include "RenderEntity.h"

#include <iostream>


class EntityPlayer : public SpaceShip
{
private:
    //Score du joueur
	int m_points;

    //Niveau de tir du joueur, dépends des combos
	int m_fireLevel;
	//Nombre de combos
	int m_comboCounter;

    //Retourne fauw si le joueur peut activer son tir secondaire /bonus
    bool m_powerModed;

    //Niveau d'upgrade du la^puissance de feu
	int m_firePowerLevel;

	//Niveau d'upgrade de la cadence de tir
	int m_fireSpeedLevel;

	//Niveau d'upgra de la vitesse de déplacement
	int m_movingSpeedLevel;

	//Retourne le niveau de bouclier
	int m_shieldLevel;

    //Argent du joueur (score restant après upgrade qui s'accumule entre les niveaux)
	int m_money;

public:


    /** \brief EntityPlayer
     * Créer une nouvelle instance de joueur
     * \param int x position x de l'entité
     * \param int y position y de l'entité
     *
     */
	EntityPlayer(int x, int y);

    /** \brief fire
     * Permet à l'entité de tirer
     * \param entities std::vector<Attack*>& Liste des attaques du niveau afin de permettre d'ajouter un nouveau tir
     * \return vrai si a tiré
     *
     */
	bool fire(std::vector<Attack*> &entities);

    bool powerMode();
    void enablePowerMode();
    void update();

    /** \brief hit
     * Définit la réaction de l'entité lorsque elle est touchée par un tir
     * \param source Attack* Tir touchant l'entité
     * \return void
     *
     */
	void hit(Attack* source);

    /** \brief hurtEnemy
     * Définit la réaction de l'entité lorsque elle a blessé une  autre entité
     * \param other const Entity& L'entité blessée
     * \return void
     *
     */
    void hurtEnemy(Entity &other);

    /** \brief setPoints
     * Permet de modifier le nombre de points du joueur
     * \param p const int Nouveau nombre de points
     * \return void
     *
     */
    void setPoints(const int p);

    /** \brief getPoints
     * Permet de récupérer le nombre de points du joueur
     * \return int nombre de oints du joueur
     *
     */
	int getPoints() const;

    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur l'entité
     * \return std::string informations
     *
     */
	std::string toString() const;

    /** \brief getFirePowerLevel
     * Retourne le niveau d'upgrade de la puissance de feu du joueur
     * \return int niveau
     *
     */
	int getFirePowerLevel() const;

    /** \brief getFireSpeedLevel
     * Retourne le niveau d'upgrade de la cadence de feu du joueur
     * \return int niveau
     *
     */
	int getFireSpeedLevel() const;

    /** \brief getMovingSpeedLevel
     * Retourne le niveau d'upgrade de la vitesse de déplacement du joueur
     * \return int niveau
     *
     */
	int getMovingSpeedLevel() const;

    /** \brief getShieldLevel
     * Retourne le niveau d'upgrade de la puissance de bouclier du joueur
     * \return int niveau
     *
     */
	int getShieldLevel() const;

    /** \brief setFirePowerLevel
     *  Change le niveau d'upgrade de la puissance de feu du joueur
     * \param v const int nouveau niveau d'upgrade
     * \return void
     *
     */
	void setFirePowerLevel(const int v);

    /** \brief setFirePowerLevel
     *  Change le niveau d'upgrade de la cadence de feu du joueur
     * \param v const int nouveau niveau d'upgrade
     * \return void
     *
     */
	void setFireSpeedLevel(const int v);

    /** \brief setMovingSpeedLevel
     *  Change le niveau d'upgrade de la vitesse de déplacement du joueur
     * \param v const int nouveau niveau d'upgrade
     * \return void
     *
     */
	void setMovingSpeedLevel(const int v);

    /** \brief setShieldLevel
     *  Change le niveau d'upgrade de la puissance de bouclier du joueur
     * \param v const int nouveau niveau d'upgrade
     * \return void
     *
     */
	void setShieldLevel(const int v);


    /** \brief savePointsToMoney
     *  Transfère les points vers la variable money
     * \return void
     *
     */
	void savePointsToMoney();

    /** \brief setMoney
     * Permet de régler la quantité d'argent
     * \param money const int
     * \return void
     *
     */
	void setMoney(const int money);

    /** \brief getMoney
     *  Retourne la quantité d'argent
     * \return int
     *
     */
	int getMoney() const;

    /** \brief collidWith
     * Retourne si le joueur est en collision avec l'entité passée en paramètre
     * \param other Entity&
     * \return bool
     *
     */
	bool collidWith(Entity &other);

    /** \brief getCombo
     * Retourne le niveau de combo
     * \return int
     *
     */
	int getCombo() const;

};


#endif
