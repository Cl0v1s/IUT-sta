#ifndef EASYENEMY_H
#define EASYENEMY_H

#include <string>
#include <sstream>

#include "EntityEnemy.h"
#include "EntityPlayer.h"

#include "View.h"

class EasyEnemy : public EntityEnemy
{
public:
    /** \brief EasyEnemy
     * Créer un nouvel ennemi présentant une faible dangerosité
     * \param int x position x
     * \param int y position y
     * \param int level index du niveau en cours
     * \param EntityPlayer* player joueur 1, afin de récupérer ses informations (le joueur 2 est ingoré car ses caractéristiques sont identiques)
     * \return
     *
     */
	EasyEnemy(int x, int y, int level, EntityPlayer *player);

    /** \brief update
     * Met à jour les informations de l'entité
     * \param entities std::vector<Attack*>& Liste des attaques afin de pouvoir eventuellement ajouter une nouvelle attaque
     * \return void
     *
     */
	void update(std::vector<Attack*> &entities);

    /** \brief fire
     * Permet à l'entité de tirer
     * \param entities std::vector<Attack*>& Liste des attaques afin de pouvoir ajouter une nouvelle attaque
     * \return void
     *
     */
	bool fire(std::vector<Attack*> &entities);

    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur l'easyenemy courant
     * \return std::string ensemble des informations
     *
     */
    std::string toString() const;

};


#endif
