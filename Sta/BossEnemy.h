#ifndef BOSSENEMY_H
#define BOSSENEMY_H

#include <string>
#include <sstream>
#include <math.h>

#include "Const.h"
#include "EntityEnemy.h"
#include "EntityPlayer.h"

class BossEnemy : public EntityEnemy
{
private:
    //Définit si l'entité est en phase de montée ou de descente
    //si vrai monte, sinon descend
    bool m_upElseDown;

public:

    /** \brief BossEnnemy
     * Créer une nouvelle instance de bossEnnemy
     * \param position x du boss
     * \param position y du boss
     * \param numéro du niveau actuel
     * \param joueur 1 (pour récupération de ses stats qui seront de toute manière identiques aux stats des autres joueurs)
     */
	BossEnemy(int x, int y, int level, EntityPlayer *player);


    /** \brief update
     * Met à jour les informations du boss
     * \param entities std::vector<Attack*>& liste d'attaques pour insertion des eventuelles attaques du boss
     * \return void
     *
     */
	void update(std::vector<Attack*> &entities);

    /** \brief fire
     * Permet au boss de tirer
     * \param entities std::vector<Attack*>& liste d'attaques pour insertion des attaques du boss
     * \return void
     *
     */
	bool fire(std::vector<Attack*> &entities);

    /** \brief collidWith
     * Indique si le boss est entré en collision avec une entité et définit sa réaction en cas de collision
     * \param other const Entity& liste des autres entités
     * \return bool vrai si collision, faux sinon
     *
     */
	bool collidWith(const Entity &other);

    /** \brief toString
     * retourne un string contenant l'ensemble des informations concernant le boss courant
     * \return std::string informations
     *
     */
    std::string toString() const;

};


#endif
