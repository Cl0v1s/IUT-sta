#ifndef LEVEL_H
#define LEVEL_H


#include <stdlib.h>
#include <climits>
#include <bitset>
#include <vector>
#include <iostream>
#include <math.h>
#include <chrono>


#include "Const.h"
#include "Entity.h"
#include "EntityPlayer.h"
#include "EntityObstacle.h"
#include "EntityEnemy.h"
#include "EasyEnemy.h"
#include "MediumEnemy.h"
#include "HardEnemy.h"

#include "RenderEntity.h"
#include "View.h"


class Game;

class Level
{

friend class GameScene;

private:

    //Nombre de points requis pour finir le niveau
    int m_points;
    //Liste des ennemis
    std::vector<EntityEnemy*> m_enemies;
    //Liste des obstacles
    std::vector<EntityObstacle*> m_obstacle;
    //Liste des joueurs
    std::vector<EntityPlayer*> m_players;
    //Liste des attaques
    std::vector<Attack*> m_attacks;

    /**Seed du niveau
    *Un seed identique donnera lieu à la génération d'un même niveau à condition que ceci ai lieu sur des machines de puissances équivalentes entre elles.
    *Attention: Il se trouve que ce système part du postulat que le déroulement du jeu est fluide et sera toujours le même.
    *De fait il se peut qu'il ne fonctionne pas correctement en mode console.

    *Un seed doit TOUJOURS etre supérieur à 512 et se compose de la manière suivante (à lire de droite à gauche):
    * - 9 bits représentant le nombre de points à atteindre pour finir le niveau (qui deviendra par la suite la séquence de bits définie plus bas)
    * - de 4 à 55 bits avec comme minimum une valeur de 5 (soit 0101) représentant l'index du niveau actuel + 4 (0101 donne donc le niveau 1)
    * La moitié inférieure sera la fréquence de la fonction de génération et la moitié supérieur, l'amplitude
    */
    unsigned int m_seed;

    //compteur de frame
    int m_frame;

    //index du niveau
    int m_levelNumber;

    //compteur de tick, utilisé pour gérer la génération des entités
    int m_tick;

    //Amplitude de la fonction de génération
    unsigned int m_amplitude;

    //Fréquence de la fonction de génération
    unsigned int m_frequency;

    //Séquence binaire permettant une génération non linéaire sur le cours terme.
    std::bitset<9> m_rand;

public:



    /** \brief Level
     * Créer un nouveau niveau
     * \param seed int seed utilisé pour la génération du niveau
     *
     */
    Level(int seed);

    /** \brief Destructeur de niveau
     * Définit les actions à réaliser lors de la destruction du niveau
     *
     */
    ~Level();

    /** \brief addPlayer
     * Ajoute un joueur au niveau courant
     * \param e EntityPlayer* joueur à ajouter
     * \return void
     *
     */
    void addPlayer(EntityPlayer * e);

    /** \brief update
     * Met à jour les informations du niveau
     * \return int retourne GAME_WIN_CODE si le(s) joueur(s) a (ont) gagné la partie, GAME_LOOSE_CODE sinon
     *
     */
    int update();

    /** \brief manageEntities
     * Gère les entités, leurs collisions et met à jour leurs informations
     * \return void
     *
     */
    void manageEntities();

    /** \brief generateEnemies
     * genère les ennemis
     * \return void
     *
     */
    void generateEnemies();

    /** \brief generateObstacles
     * génère les obstacles
     * \return void
     *
     */
    void generateObstacles();

    /** \brief showEnemies
     * Fonction temporaire
     * Affiche à l'écran la liste des ennemis
     * \return void
     *
     */
    void showEnemies();

    /** \brief showAttaques
     * Fonction temporaire
     * Affiche à l'écran la liste des attaques
     * \return void
     *
     */
    void showAttacks();

    /** \brief showObstacles
     * Fonction temporaire
     * Affiche à l'écran la liste des obstacles
     * \return void
     *
     */
    void showObstacles();

    /** \brief showPlayers
     * Fonction temporaire
     * Affiche à l'écran la liste des joueurs
     * \return void
     *
     */
    void showPlayers();

    /** \brief getRequiredPoints
     *  Retourne le nombre de points requis pour finir le niveau
     * \return int nombre de points requis
     *
     */
    int getRequiredPoints() const;

    /** \brief entityExists
     *  retourne si l'entité passée en paramètres existe dans le niveau courant
     * \param Entity const Entity*
     * \return bool
     *
     */
    bool entityExists(const Entity *Entity) const;

    /** \brief reset
     *  Remet le niveau courant à zéro
     * \return void
     *
     */
    void reset();


    /** \brief getLevelNumber
     * Retourne le numéro du niveau courant
     * \return int
     *
     */
    int getLevelNumber() const;
};

#endif
