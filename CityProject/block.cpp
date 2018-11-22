#include "block.h"

Block::Block(){}

Block::Block(int x,int y,int largeur,int hauteur):
    debutBlockX(x),
    debutBlockY(y),
    largeur_block(largeur),
    hauteur_block(hauteur){}

void Block::afficher_bloc(){

    cout<<"/******************************************/"<<endl;
    cout<<"debut du bloc x = "<<debutBlockX<<" y = "<<debutBlockY<<endl;
    cout<<"largeur du bloc l = "<<largeur_block<<", hauteur du bloc h = "<<hauteur_block<<endl;
}
