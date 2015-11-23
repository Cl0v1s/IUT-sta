/* INFORMATION:
* Si des vecteurs ont été choisis pour récupérer les scores au lieu de set (ce qui aurait pu se réveler plus pratique)
* C'est que nous souhaitions pouvoir afficher des scores ex-aqueo
*/

#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdlib.h>
#include <algorithm>

#include "Const.h"

class ScoreHelper
{
private:

    //adresse du fichier de score
    static std::string file;


public:
    /** \brief readScores
     * Lit les scores depuis le fichier de sauvegarde
     * \return std::vector<int> liste des scores
     *
     */
    static std::vector<int> readScores();

    /** \brief getBestScore
     * Retourne le meilleur score depuis la liste
     * \return int meilleur score
     *
     */
    static int getBestScore();

    /** \brief getBestScore
     * Retourne le meilleur score depuis la liste
     * \param scores std::vector<int> Liste des scores
     * \return int meilleur score
     *
     */
    static int getBestScore(const std::vector<int> &scores);

    /** \brief saveScore
     * Sauvegarde le score passé en paramètre et retourne son index dans le classement
     * \param scores& std::vector<int> Liste des scores
     * \param score const int score à enregistrer
     * \return int index du score dans le classement
     *
     */
    static int saveScore(const std::vector<int> &scores, const int score);

    /** \brief saveScore
     * Sauvegarde le score passé en paramètre et retourne son index dans le classement
     * \param score const int Score à enregistrer
     * \return int index du score dans le classement
     *
     */
    static int saveScore(const int score);

    /** \brief saveFileExists
     * Retourne si le fichier contenant les scores existe ou non
     * \return bool vrai si il existe, faux sinon
     *
     */
    static bool saveFileExists();

    /** \brief createSaveFile
     * Créer le fichier de sauvegarde
     * \return void
     *
     */
    static void createSaveFile();


    /** \brief resetSaveFile
     * Efface tout les scores précedents
     * \return void
     *
     */
    static void resetSaveFile();


    /** \brief comp
     *  compare pour permettre le trie des scores
     * \param i int première valeur
     * \param j int seconde valeur
     * \return bool valeur de la comparaison
     *
     */
    static bool comp(int i, int j);
};


#endif // SCORE_MANAGER_H
