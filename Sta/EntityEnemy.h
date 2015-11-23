#ifndef ENTITYENEMY_H
#define ENTITYENEMY_H


#include <vector>
#include <string>

#include "SpaceShip.h"

class EntityEnemy : public SpaceShip
{
private:
    //compteur de frame à utiliser pour déterminer le pattern de l'entité
    int m_patternFrame;

public:



    /** \brief EntityEnemy
     * Créer un nouvel enemi
     * \param int x position de l'ennemi
     * \param int y position de l'ennemi
     * \param int width largeur de l'ennemi
     * \param int height hauteur de l'ennemi
     * \param string fichier image à utiliser pour représenter l'ennemi
     * \return
     *
     */
	EntityEnemy(int x, int y, int width, int height, std::string imageFile);

    /** \brief update
     * met à jour les informations sur l'ennemi
     * \param entities std::vector<Attack*>& Liste d'attaque pour un eventuel ajout
     * \return virtual void
     *
     */
	virtual void update(std::vector<Attack*> &entities);

    /** \brief  fire
     * Fait tirer l'ennemi
     * \param entities std::vector<Attack*>& Liste d'attaque pour un ajout
     * \return virtual void
     *
     */
	virtual bool fire(std::vector<Attack*> &entities) = 0;

    /** \brief getPatternFrame
     * Retourne le compteur de pattern
     * \return int compteur de pattern
     *
     */
	int getPatterFrame() const;
    /** \brief getFireCount
     * Retourne le compteur de tir
     * \return int compteur de tir
     *
     */
	int getFireCount() const;

    /** \brief setPatternFrame
     * Paramètre le compteur de frame de pattern
     * \param a const int nouveau compteur
     * \return void
     *
     */
	void setPatternFrame(const int a);

    /** \brief setFireCount
     * Paramètre le compteur de frame de tir
     * \param a const int nouveau compteur
     * \return void
     *
     */
	void setFireCount(const int a);

};

#endif // ENTITY_ENNEMY_H



