#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test

#include <boost/test/unit_test.hpp>

using namespace std;

#include "Level.h"
#include "EntityPlayer.h"

BOOST_AUTO_TEST_CASE(attack)
{
    vector<Attack *> attack;
    EntityPlayer * entityPlayer = new EntityPlayer(0,0);
    entityPlayer->fire(attack);
    //on teste le bon fonctionnement du spawn du missile
    BOOST_CHECK(attack.size() != 2);
    //Le missile n'a en effet pas spawné puisque le délai de tir du joueur est suppérieur
    BOOST_CHECK(attack.size() == 0);

    delete entityPlayer;
}

BOOST_AUTO_TEST_CASE(moving)
{
    EntityPlayer * entityPlayer = new EntityPlayer(0,0);

    //Le joueur doit se rendre en 10,10
    entityPlayer->moveTo(10,10);
    BOOST_CHECK(entityPlayer->getVelocityX() != 11);
    BOOST_CHECK(entityPlayer->getVelocityX() == 10);
    BOOST_CHECK(entityPlayer->getVelocityY() == 10);

    //Le joueur doit se rendre en -10000, 5
    entityPlayer->moveTo(-10000, 5);

    BOOST_CHECK(entityPlayer->getVelocityX() != 0);
    BOOST_CHECK(entityPlayer->getVelocityX() == -10000);
    BOOST_CHECK(entityPlayer->getVelocityY() == 5);

    //On met à jour la position du joueur
    entityPlayer->update();


    //On vérifie que la vélocité a bien diminué (s'est rapproché de 0)
    BOOST_CHECK(entityPlayer->getVelocityX() > -10000);
    BOOST_CHECK(entityPlayer->getVelocityY() < 5);

    delete entityPlayer;
}
/*
Les tests qui suivent fonctionnement parfaitement en mode terminal
Malheureusement l'ajout d'allocations dynamique dues à l'ajout de render sans initialiser le jeu entier
BOOST_AUTO_TEST_CASE(collision)
{

    vector<Attack *> attack;
    EntityPlayer * entityPlayer = new EntityPlayer(0,0);
    EasyEnemy * easyEnemy = new EasyEnemy(100, 0, 1, entityPlayer);

    entityPlayer->fire(attack);

    //On test la valeur de vie initiale
    BOOST_CHECK(easyEnemy->getLife() == 8);

    while(attack[0]->getBoundingBox().getX() <= 100 )
    {
        attack[0]->update();
    }

    //On teste si la collision a bien eu lieu
    BOOST_CHECK(((attack[0])->collidWith(*easyEnemy)) == true);

    //On test si les dommages ont bein été prit en compte
    BOOST_CHECK(easyEnemy->getLife() == 6);

    //apres un choc une attaque ne possède plus de vie, on peut donc la supprimer dans le foulée
    if(attack[0]->getLife() == 0)
    {
        delete (attack[0]);
        attack.erase(attack.begin());
    }

    //on vérifie que la liste d'attaque a été reduite
    BOOST_CHECK(attack.size() == 0);

    //on change la position de l'ennemi
    easyEnemy->changePosition(100,100);

    //on retire sans changer la position du joueur
    easyEnemy->fire(attack);

    while(attack[0]->getBoundingBox().getX()<=0)
    {
        attack[0]->update();
    }

    //On teste si la collision n'a pas eu lieu
    BOOST_CHECK(((attack[0])->collidWith(*entityPlayer)) == false);

    delete entityPlayer;
    delete easyEnemy;
}
*/

