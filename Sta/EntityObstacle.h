#ifndef ENTITYOBSTACLE_H
#define ENTITYOBSTACLE_H

#include "Entity.h"
#include "Attack.h"

#include <sstream>
#include <string>
#include <iostream>

class EntityObstacle : public Entity
{

public:
    //Types d'obstacle pouvant etre ajoutés au jeu par copie
    static EntityObstacle Asteroid;
    static EntityObstacle ShipPart;

    /** \brief EntityObstacle
     * Créer une nouvelle instance d'entityObstacle
     * \param int life points de vie de l'entité
     * \param int x position x de l'entité
     * \param int y position y de l'entité
     * \param int width largeur de l'entité
     * \param int height hauteur de l'entité
     * \param string fichier d'image représentant l'entité
     * \return
     *
     */
	EntityObstacle(int life, int x, int y, int width, int height, std::string imageFile);

    /** \brief update
     * Met à jour les informations de l'entité
     * \return void
     *
     */
    void update();
    /** \brief hit
     * Définit la réaction de l'entité lorsque elle est touchée par un tir
     * \param source Attack* Attaque touchant l'entité
     * \return void
     *
     */
    void hit(Attack *source);
    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur l'entité
     * \return std::string informations
     *
     */
    std::string toString() const;


};

#endif
