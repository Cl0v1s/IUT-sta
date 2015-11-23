#ifndef TITLESCENE_H
#define TITLESCENE_H

#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

#include <unistd.h>

#include "ScoreHelper.h"
#include "Game.h"
#include "Scene.h"
#include "GameScene.h"
#include "RenderMenu.h"

class TitleScene : public Scene
{

private:
    //fond d'écran commun à toute les écrans titres
    static std::string backgroundImage;


public:
    /** \brief TitleScene
     * Créer un nouvel écran titre
     *
     */
    TitleScene();

    /** \brief changeToGameSceneAlone
     * callback de menu
     * Permet au joueur de lancer une nouvelle partie pour un joueur
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void changeToGameSceneAlone(Scene* scene);

    /** \brief changeToGameSceneFriend
     * callback de menu
     * Permet au joueur de lancer une nouvelle partie pour deux joueurs
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void changeToGameSceneFriend(Scene* scene);

    /** \brief showScore
     * callback de menu
     * Affiche la liste des meilleurs scores
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void showScore(Scene* scene);


    /** \brief resetScore
     * callback de menu
     * Efface la liste des meilleurs scores
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void resetScore(Scene *scene);

    /** \brief closeScore
     * Callback de menu
     * Permet de fermer la liste des meilleurs scores
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void closeScore(Scene* scene);

    /** \brief showOptions
     * callback de menu
     * Affiche la liste des options
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void showOptions(Scene *scene);

    /** \brief closeOptions
     * callback de menu
     * Ferme la liste des options
     * \param scene Scene* Scene à la source du menu
     * \return void
     *
     */
    static void closeOptions(Scene *scene);


    /** \brief quit
     * callback de menu
     * fait quitter le jeu
     * \param scene Scene* Scene à la source du callback
     * \return void
     *
     */
    static void quit(Scene *scene);

    /** \brief update
     * Met à jour les informations de l'écran titre
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
     * Retourne un string contenant l'ensemble des informations sur l'écran titre
     * \return std::string informations
     *
     */
    std::string toString() const;
};


#endif // TITLESCENE_H
