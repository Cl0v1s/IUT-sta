#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#include "Const.h"
#include "Scene.h"
#include "Level.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "UpgradeScene.h"

#include "RenderEntity.h"
#include "RenderText.h"

class GameScene : public Scene
{
private:

    //Niveau courant
    Level m_level;

    //seed du niveau en cours
    int m_seed;

    //Liste de joueur jouant Ã  la partie courante
    std::vector<EntityPlayer *> m_players;

    bool m_isPaused;

    //Liste des fond d'Ã©cran pour permettre leur dÃ©placement
    std::vector<RenderEffect*> m_backgrounds;

public:

    /** \brief GameScene
     * Constructeur de scene de jeu
     * \param const int seed seed du niveau
     * \param players const int Nombre de joueurs participant Ã  la partie (maximum de deux)
     *
     */
    GameScene(const int seed, const int players);

    /** \brief GameScene
     * Constructeur de scene de jeu
     * \param const int seed seed du niveau
     * \param vector<EntityPlayer*> players Liste des joueurs
     *
     */
    GameScene(const int seed, std::vector<EntityPlayer*> players);

    /** \brief update
     * Met Ã  jour les informations de la scene de jeu
     * \return bool retourne vrai si le jeu doit s'arrÃ©ter, faux sinon.
     *
     */
    bool update();

    /** \brief inputUpdate
     * DÃ©finit les actions Ã  effectuer en rÃ©ponse des entrÃ©es du (des) joueurs
     * \return bool retourne vrai si le jeu doit quitter, faux sinon
     *
     */
    bool inputUpdate();

    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur l'Ã©cran de jeu
     * \return std::string informations
     *
     */
    std::string toString() const;


    /** \brief quitPause (callback de menu)
     * Permet de quitter le menu pause
     * \param scene Scene*
     * \return void
     *
     */
    static void quitPause(Scene *scene);

    /** \brief showOptions (callback de menu)
     * Affiche le menu des options
     * \param scene Scene*
     * \return void
     *
     */
    static void showOptions(Scene *scene);

    /** \brief closeOptions (callback de menu)
     *  Ferme le menu des options
     * \param scene Scene*
     * \return void
     *
     */
    static void closeOptions(Scene *scene);

    /** \brief restartLevel (callback de menu)
     *  Permet de redémarrer le niveau courant
     * \param scene Scene*
     * \return void
     *
     */
    static void restarLevel(Scene *scene);

    /** \brief quitGame (callback de menu)
     * Permet de quitter le jeu
     * \param scene Scene*
     * \return void
     *
     */
    static void quitGame(Scene *scene);

    /** \brief manageSound(callback de menu)
     *  Permet de couper/d'activer le son
     * \param scene Scene*
     * \return void
     *
     */
    static void manageSound(Scene *scene);

    /** \brief removeActiveMenu
     *  Supprime le dernier menu de la scene courante
     * \return void
     *
     */
    void removeActiveMenu();
};

#endif // GAMESCENE_H

