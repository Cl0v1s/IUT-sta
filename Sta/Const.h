#ifndef CONST_H
#define CONST_H

#include <string>

//temps devant s'écouler entre deux frames (contrôle de framerate)
const int TIME_LAST_FRAME = 16;

//Seed du premier niveau
const int GAME_SEED_INIT = 2810 ; //010111111010

//Code signifiant que le joueur a perdu car plus de vie
const int GAME_LOOSE_CODE = 1;
//Code signifiant que le joueur a gagné la partie
const int GAME_WIN_CODE = 2;

//Largeur de la fenetre
const int WINDOW_WIDTH = 800;
//hauteur de la fenetre
const int WINDOW_HEIGHT = 600;

//Chemin du fichier de sauvgarde
const std::string SAVE_FILE = "save.txt";

//Chemin du fichier de musique
const std::string MUSIC_FILE = "assets/0r4 - ZeroErreQuattro - 03 NaN Oddysee.ogg";

#endif // CONST_H
