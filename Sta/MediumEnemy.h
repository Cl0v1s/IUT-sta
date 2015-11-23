#ifndef MEDIUMENEMY_H
#define MEDIUMENEMY_H

#include <string>
#include <sstream>
#include <math.h>

#include "EntityEnemy.h"
#include "EntityPlayer.h"

class MediumEnemy : public EntityEnemy
{
public:
    /** \brief MediumEnemy
     * Créer un nouvel enemi présentant une difficulté de niveau deux
     * \param int x position x de l'entité
     * \param int y position y del'entité
     * \param int level index du niveau courant
     * \param EntityPlayer* pointeur vers le joueur 1 afin de récupérer ses informations (qui sont identiques à celles du joueur 2)
     *
     */
	MediumEnemy(int x, int y, int level, EntityPlayer *player);

    /** \brief update
     *  Met à jour les informations de l'entité
     * \param entities std::vector<Attack*>& Liste des attaques en cours afin de pouvoir potentiellement y ajouter une nouvelle.
     * \return void
     *
     */
	void update(std::vector<Attack*> &entities);

    /** \brief fire
     * Permet à l'entité de tirer
     * \param entities std::vector<Attack*>& Liste des attaques en cours afin de pouvoir y ajouter une nouvelle attaque.
     * \return void
     *
     */
	bool fire(std::vector<Attack*> &entities);

    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur l'entité
     * \return std::string informations
     *
     */
    std::string toString() const;

};


#endif
