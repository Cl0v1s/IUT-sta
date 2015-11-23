#ifndef GAME_H
#define GAME_H

#include <chrono>


#include "Const.h"

#include "Scene.h"
#include "TitleScene.h"
#include "View.h"

class Game
{
private:
    //Scene (écran de jeu) en cours
    static Scene *currentScene;
    //définit si le jeu est finit ou non
    static bool done;
public:

    /** \brief initialize
     * Prépare les paramètres suite  à un nouveau lancement du jeu
     * \return void
     *
     */
    static void initialize();

    /** \brief run
     * Lance le déroulement du jeu et contrôle celui-ci
     * \return void
     *
     */
    static void run();

    /** \brief changeScene
     * Permet de changer de scene (d'écran de jeu)
     * \param scene Scene* nouvel écran
     * \return void
     *
     */
    static void changeScene(Scene *scene);

    /** \brief destroy
     * Détruit la scene courante en mémoire
     * \return void
     *
     */
    static void destroy();

    /** \brief quit
     * Lance la procédure d'arret du jeu
     * \return void
     *
     */
    static void quit();

    /** \brief isFinished
     * Retourne si le jeu est en phase d'arret ou non
     * \return bool vrai si le jeu est en phase d'arret, faux sinon
     *
     */
    static bool isFinished();
};


#endif // GAME_H
