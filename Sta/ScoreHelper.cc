#include "ScoreHelper.h"

using namespace std;

string ScoreHelper::file = SAVE_FILE;

vector<int> ScoreHelper::readScores()
{
    vector<int> res;

    if(saveFileExists() == false)
        createSaveFile();

    //lecture des scores depuis le fichier
    string s;
    fstream fil;
    fil.open(file, fstream::in);
    if(fil.is_open())
    {
        while(getline(fil,s))
        {
            res.push_back(atoi(s.c_str()));
        }
    }
    else
        throw logic_error("ScoreHelper: readScores, Impossible d'ouvrir le fichier de sauvegarde.");
    fil.close();
    //on trie le score
    sort(res.begin(), res.end(), comp);
    return res;
}

bool ScoreHelper::comp(int i, int j)
{
    return (j<i);
}



int ScoreHelper::getBestScore()
{
    vector<int> s = readScores();
    return getBestScore(s);
}

int ScoreHelper::getBestScore(const vector<int> & scores)
{
    if(scores.size() <= 0)
        return 0;
    int index = 0;
    for(unsigned int i = 0; i<scores.size(); i++)
    {
        if(scores[i] > scores[index])
            index = i;
    }
    return scores[index];
}

int ScoreHelper::saveScore(const int s)
{
    vector<int> scores = readScores();
    return saveScore(scores, s);
}

int ScoreHelper::saveScore(const vector<int> &scores, const int s)
{
    //Récupération de la position du score dans le classement
    int index = 0;
    if(scores.size() > 0)
    {
        for(unsigned int i=0; i<scores.size(); i++)
        {
            if(s < scores[i]) //Si le score courant est plus grand que le score à enregistrer alors il perds une place dans le classement
            {
                index+=1;
            }
        }
    }

    fstream fil;
    fil.open(file, fstream::out | fstream::app);
    if(fil.is_open())
    {
        fil << s << endl;
    }
    else
        throw logic_error("ScoreHelper: saveScore, Impossible d'ouvrir le fichier de sauvegarde.");
    fil.close();
    return index;
}

bool ScoreHelper::saveFileExists()
{
    fstream fil;
    fil.open(file, fstream::in);
    if(fil.is_open())
    {
        fil.close();
        return true;
    }
    fil.close();
    return false;
}

void ScoreHelper::createSaveFile()
{
    fstream fil;
    fil.open(file, ios::out);
    if(!fil.is_open())
        throw logic_error("ScoreHelper: createSaveFile, Impossible de créer le fichier de sauvegarde.");
    fil.close();
}

void ScoreHelper::resetSaveFile()
{
    fstream fil;
    fil.open(file, ios::out | ios::trunc);
    if(!fil.is_open())
        throw logic_error("ScoreHelper: resetSaveFile, Impossible d'ouvrir le fichier de sauvegarde.");
    fil.close();
}
