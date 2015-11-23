#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <string>
#include <vector>
#include <sstream>

#include "ScoreHelper.h"
#include "Scene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "EntityPlayer.h"

class GameOverScene : public Scene
{
private:

    //Image de fond commune à toute les scene de fin de partie
    static std::string backgroundImage;

    //score de la dernière partie
    int m_score;

    //position du score dans le classement
    int m_classement;

    //Meilleur score du classement
    int m_bestScore;

public:
    /** \brief GameOverScene
     * Créer une nouvelle instance de l'écran de fin de partie
     * \param players std::vector<EntityPlayer *> Liste des joueurs ayant participés à la dernière partie
     *
     */
    GameOverScene(std::vector<EntityPlayer *> players);

    /** \brief goToTitle
     * Callback de menu
     * Permet au joueur de retourner au menu principal
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void goToTitle(Scene *scene);

    /** \brief restartOnePlayer
     * callback de menu
     * Permet au joueur de relancer une nouvelle partie pour un joueur
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void restartOnePlayer(Scene *scene);

    /** \brief restartTwoPlayers
     * callback de menu
     * Permet au joueur de relancer une nouvelle partie pour deux joueurs
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void restartTwoPlayers(Scene *scene);


    /** \brief quit
     * callback de menu
     * Permet au joueur de quitter le jeu
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void quit(Scene *scene);

    /** \brief update
     * Met à jour les informations de la scene de fin de partie
     * \return bool retourne vrai si le jeu doit quitter, faux sinon
     *
     */
    bool update();


    /** \brief inputUpdate
     * Définit les actions à effectuer en réponse des entrées du (des) joueurs
     * \return bool retourne vrai si le jeu doit quitter, faux sinon
     *
     */
    bool inputUpdate();

    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur l'écran de fin de partie
     * \return std::string informations
     *
     */
    std::string toString() const;

};


#endif // GAMEOVERSCENE_H
