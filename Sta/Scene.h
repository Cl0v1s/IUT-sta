#ifndef SCENE_H
#define SCENE_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <set>

#include "Menu.h"
#include "RenderEffect.h"


class Scene
{

protected:
    //liste des menus présents dans la scene
    std::vector<Menu*> m_menuList;

public:

    /** \brief Scene
     * Créer une nouvelle instance d'écran
     *
     */
    Scene();

    /** \brief Destructeur
     * Actions à réaliser lors de la destruction d'une scene
     *
     */
    virtual ~Scene();

    /** \brief inputUpdate
     * Définit les actions à effectuer en réponse des entrées du (des) joueurs
     * \return bool retourne vrai si le jeu doit quitter, faux sinon
     *
     */
    virtual bool inputUpdate()=0;

    /** \brief update
     * Met à jour les informations de la scene
     * \return bool retourne vrai si le jeu doit quitter, faux sinon
     *
     */
    virtual bool update()=0;

    /** \brief getMenuList
     * Retourne la liste des menus de la scene courante
     * \return std::vector<Menu*>& Liste des menues
     *
     */
    std::vector<Menu*> & getMenuList();

    /** \brief getCurrentMenu
     * Retourne le premier menu actif de la liste de menu
     * \return Menu* pointeur vers le menu actif
     *
     */
    Menu* getCurrentMenu();

    /** \brief toString
     * Retourne un string contenant l'ensemble des informations sur l'écran
     * \return std::string informations
     *
     */
    virtual std::string toString()const=0;


};

#endif // SCENE_H
