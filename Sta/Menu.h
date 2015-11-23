#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>


#include <iostream>

class Scene;

class Menu
{
friend class RenderMenu;

private:
    //image de fond des menus (à définir)
    static std::string backgroundImage;

    //Scene cntenant le menu
    Scene* m_parent;
    //Liste des intitulés des entrées
    std::vector<std::string> m_options;
    //Listes des pointeurs de fonction de callbacks
    std::vector<void (*)(Scene*)> m_callbacks;
    //indice de l'option séléctionnée
    unsigned int m_selected;
    //position x du menu
    int m_x;
    //position y du menu
    int m_y;
    //largeur du menu
    int m_width;
    //auteur du menu
    int m_height;

    //vrai si le menu est actif
    bool active;


public:




    /** \brief Menu
     * Créer un nouveau menu
     * \param x int position x du menu
     * \param y int position y du menu
     * \param w int largeur de la fenetre de menu
     * \param h int hauteur de la fenetre de menu
     *
     */
    Menu(Scene* parent,int x, int y, int w, int h);

    ~Menu();


    /** \brief Permet de changer la position du menu
     *
     * \param x const int nouvelle position x du menu
     * \param y const int nouvelle position y du menu
     * \return void
     *
     */
    void setPosition(const int x, const int y);


    /** \brief Permet de changer la taille du menu
     *
     * \param w const int nouvelle largeur du menu
     * \param h const int nouvelle hauteur du menu
     * \return void
     *
     */
    void setSize(const int w, const int h);


    /** \brief setActive
     * permet au menu de passer du mode actif (interractif et visible) au mode passif et vice versa
     * \param act const bool false pour mode passif, true pour mode actif
     * \return void
     *
     */
    void setActive(const bool act);


    /** \brief getActive
     * Retourne le mode d'activité dans lequel se trouve le menu
     * \return bool false pour mode passif, true pour mode actif
     *
     */
    bool getActive() const;

    /** \brief Permet de récupérer le forme du menu
     *
     * \return std::vector<int> surface occupée par le menu
     *
     */
    std::vector<int> getShape() const;



    /** \brief Permet de changer d'option dans le menu
     *
     * \param action int -1 pour changer d'option vers le haut, 1 pour descendre
     * \return void
     *
     */
    void changeOption(int action);

    /** \brief Retourne un string présentant les informations du menu
     *
     * \return std::string informations
     *
     */
    std::string toString() const;

    /** \brief changeEntryName
     * change l'intitulé de l'entrée nommée entry par ne
     * \param entry std::string
     * \param ne std::string
     * \return bool
     *
     */
    bool changeEntryName(std::string entry, std::string ne);


    /** \brief select
     * Déclenche le callback de l'entrée séléctionnée
     * \return void
     *
     */
    void select();

    /** \brief addEntry
     * Ajoute une nouvelle entrée(option) au menu
     * \param  void (*f) (Scene*) Pointeur de fonction renvoyant au callback de la nouvelle entrée
     * \return std::string option Initulé de la nouvelle entrée
     *
     */
    void addEntry(std::string option, void (*f)(Scene *));

};

#endif // MENU_H
