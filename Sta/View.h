#ifndef VIEW_H
#define VIEW_H

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Const.h"
#include "Render.h"
#include "RenderMenu.h"
#include "RenderText.h"
#include "RenderEntity.h"

#include <vector>

class View
{
private:

    //fenetre de rendu
    static sf::RenderWindow *window;

    //canal de rendu de la musique
    static sf::Music *music;

    //canal de rendu des effets sonores
    static sf::Sound *sound;

    //Liste des render
    static std::vector<Render*> m_renders;

    //fichier d'effets sonores
    static sf::SoundBuffer *fire;
    static sf::SoundBuffer *explosion;
    static sf::SoundBuffer *bonus;
    static sf::SoundBuffer *hurt;


public:

    //vrai si le son est acivé (public can ne nécessite pas de sécurité)
    static bool enableSound;

    /** \brief Initialize
     * Initialise les données nécessaires au rendu
     * \return void
     *
     */
    static void Initialize();


    /** \brief Destroy
     * Détruit les données nécessaires au rendu
     * \return void
     *
     */
    static void Destroy();



    /** \brief getInput
     * Wrapper pour renderWindow get input de la sfml
     * \return const sf::Input&
     *
     */
    static const sf::Input& getInput();


    /** \brief getEvents
     * Retourne la liste des events
     * \param event sf::Event&
     * \return bool
     *
     */
    static bool getEvent(sf::Event &event);


    /** \brief addRender
     * Ajoute un render à la vue
     * \param render Render*
     * \return void
     *
     */
    static void addRender(Render* render);


    /** \brief clearRender
     * Supprime tout les renders
     * \return void
     *
     */
    static void clearRenders();


    /** \brief removeRender
     * Supprime le render à partir de son adresse
     * \param render Render*
     * \return bool
     *
     */
    static bool removeRender(Render* render);


    /** \brief removeRender
     * Supprime le renderMenu à partir de son menu
     * \param render Render*
     * \return bool
     *
     */
    static bool removeRender(Menu *menu);

    /** \brief removeRender
     * Supprime le renderEntity à partir de son entité
     * \param render Render*
     * \return bool
     *
     */
    static bool removeRender(Entity* entity);

    /** \brief removeRender
     * Supprime le renderEffect à partir de son render parent
     * \param render Render*
     * \return bool
     *
     */
    static void removeRenderEffect(Render *render);

    /** \brief removeRender
     * Supprime le renderText à partir de son texte
     * \param render Render*
     * \return bool
     *
     */
    static bool removeRender(std::string text);


    /** \brief getRenderText
     * Retourne un render text à partir de son label
     * \param text std::string
     * \return RenderText*
     *
     */
    static RenderText* getRenderText(std::string text);


    /** \brief draw
     * Dessine la vue
     * \return void
     *
     */
    static void draw();

    /** \brief playMusic
     * Joue de la musique
     * \return void
     *
     */
    static void playMusic();


    /** \brief pauseMusic
     * Met en pause la musique
     * \return void
     *
     */
    static void pauseMusic();


    /** \brief stopMusic
     * Stop la musique
     * \return void
     *
     */
    static void stopMusic();

    /** \brief playSoundEffect
     * Joue un sound effect de la vue à partir de son adresse
     * \param buffer sf::SoundBuffer*
     * \return void
     *
     */
    static void playSoundEffect(sf::SoundBuffer* buffer);


    //Fonctions permettant un accès sécurisé au son (pour éviter un delete hors de la classe)
    static sf::SoundBuffer* getSoundFire();
    static sf::SoundBuffer* getSoundExplosion();
    static sf::SoundBuffer* getSoundHurt();
    static sf::SoundBuffer* getSoundBonus();
};

#endif
