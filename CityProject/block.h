/* Un bloc est un considéré comme un rectanble dont le sommet de départ se trouve au point (debutBlockX, debutBlockY),
 *  de largeur largeur_block et de hauteur hauteur_block.
*/


#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
using namespace std;

class Block
{
public:

    //les méthodes de la classe

    //constructeurs
    Block();
    Block(int x,int y,int largeur,int hauteur);

    //Affichage de tous les attributs d'un bloc
    void afficher_bloc();


    //les attributs de la classe
    int debutBlockX;
    int debutBlockY;
    int largeur_block;
    int hauteur_block;

};

#endif // BLOCK_H
