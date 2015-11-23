#ifndef UPGRADESCENE_H
#define UPGRADESCENE_H

#include <stdexcept>
#include <string>
#include "Game.h"
#include "Scene.h"
#include "EntityPlayer.h"

class UpgradeScene : public Scene
{
private:

    //Liste des joueurs
    std::vector<EntityPlayer*> m_players;

    //seed du niveau précédent
    int m_seed;

    //score des joueurs
    int m_score;

public:
    /** \brief UpgradeScene
     * Créer une nouvelle scène d'amélioration du vaisseau
     * \param lastSeed const int Le seed du niveau précedent l'écran d'upgrade
     * \param players std::vector<EntityPlayer*> Liste des joueurs participants
     *
     */
    UpgradeScene(const int lastSeed, std::vector<EntityPlayer*> players);

    /** \brief UpgradeFirePower
     * Fonction de callback
     * Permet au joueur de payer de ses points pour améliorer sa puissance de feu
     * \param scene Scene* Scene à l'origine du callback
     * \return void
     *
     */
    static void upgradeFirePower(Scene *scene);

    /** \brief UpgradeFireSppe
     * Fonction de callback
     * Permet au joueur de payer de ses points pour améliorer sa cadence de tir
     * \param scene Scene* Scene à l'origine du callback
     * \return void
     *
     */
    static void upgradeFireSpeed(Scene *scene);

    /** \brief UpgradeMovingSpeed
     * Fonction de callback
     * Permet au joueur de payer de ses points pour améliorer sa vitesse de déplacement
     * \param scene Scene* Scene à l'origine du callback
     * \return void
     *
     */
    static void upgradeMovingSpeed(Scene *scene);

    /** \brief UpgradeShield
     * Fonction de callback
     * Permet au joueur de payer de ses points pour améliorer sa puissance de bouclier
     * \param scene Scene* Scene à l'origine du callback
     * \return void
     *
     */
    static void upgradeShield(Scene *scene);

    /** \brief goTONextLevel
     * Fonction de callback
     * Permet au joueur de lancer le niveau suivant
     * \param scene Scene* Scene à l'origine du callback
     * \return void
     *
     */
    static void goToNextLevel(Scene *scene);

    /** \brief buy
     * Gère les méthodes de déduction des points
     * \param amount const int prix à payer
     * \return bool vrai si le joueur peut payer, faux sinon
     *
     */
    bool buy(const int amount);

    /** \brief getPlayers
     * Retourne la liste des joueurs
     * \return std::vector<EntityPlayer*>& Liste des joueurs
     *
     */
    std::vector<EntityPlayer*> &getPlayers();

    /** \brief getScore
     *  Retourne la moyenne des scores gagnés par les deux joueurs
     * \return int moyenne des scores
     *
     */
    int getScore() const;


    /** \brief getSeed
     * Retourne le seed du dernier niveau
     * \return int seed du dernier niveau
     *
     */
    int getSeed() const;

    /** \brief update
     * Mise à jour de la scene
     * \return bool vrai si le jeu s'arrète, faux sinon
     *
     */
    bool update();

    /** \brief inputUpdate
     * Récupère les entrées du joueur et gère les actions correspondantes
     * \return bool vrai si le jeu s'arrète, faux sinon
     *
     */
    bool inputUpdate();

    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur l'écran de jeu
     * \return std::string informations
     *
     */
    std::string toString() const;
};

#endif // UPGRADESCENE_H
