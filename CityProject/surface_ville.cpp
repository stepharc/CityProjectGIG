#include "surface_ville.h"
#include <cstdlib>
#include <ctime>


int surface_ville::maxBlockSize = 4;
int surface_ville::minBlockSize = 2;

surface_ville::surface_ville(int x,int y)
{
    citySizeX = x;
    citySizeY = y;

    for(int i=0;i < y; i++){
        ville.push_back(vector<int>(x,1));
    }

}
void surface_ville::tracer_route(int debut, int fin, int pos, int h){

    if(h == 1)//Tracer une route horizontale
        for(int i = debut; i<fin; i++)
            ville[pos][i] = 0;

    if (h == 0)//Tracer une route verticale
        for(int i = debut; i<fin; i++)
           ville[i][pos] = 0;

}

void surface_ville::dessiner_ville()
{
    Block b(0,0,citySizeX,citySizeY);
    decouper_bloc(b);
    afficher_blocs_ville();
    decouper_ville();
    /*decouper_ville();*/
    for(int i=0; i<citySizeY; i++){
        for(int j = 0; j < citySizeX; j++)
            cout<<ville[i][j]<<" ";
        cout<<""<<endl;
    }

}

int surface_ville::position_route(int min, int max){

    int pos;
    srand(time(NULL));
    do{
        pos  = rand()%max + min;
    }while(!(((pos-min) >= minBlockSize) && ((max- pos-1) >= minBlockSize)));
    return pos;
}

int surface_ville::decouper_bloc(Block b)
{
    int x,y;
    int decoupe = 0;
    bool okX = b.hauteur_block >= minBlockSize && b.hauteur_block <= maxBlockSize,
         okY = b.largeur_block >= minBlockSize && b.largeur_block <= maxBlockSize;
    //cout<<okX<<" "<<okY<<endl;

    if(okX){ //pas de dépcoupage horizontale

        if(okY){               //pas de découpage verticale
            cout<<"pas de découpage nécessaire "<<endl;
            return decoupe;
        }
        else{                  //découpage verticale

            y = position_route(b.debutBlockY,b.largeur_block);

            tracer_route(b.debutBlockX,b.debutBlockX+b.hauteur_block,y,0);
            //rangement des deux blocs

            blocs_ville.push_back(Block(b.debutBlockX, b.debutBlockY, y-b.debutBlockY,b.hauteur_block));

            blocs_ville.push_back(Block(b.debutBlockX, b.debutBlockY+y+1, b.largeur_block - y-1, b.hauteur_block));
            decoupe = 1;

        }

    }
    else{                       //découpage horizontale

        x = position_route(b.debutBlockX,b.hauteur_block);

        tracer_route(b.debutBlockY,b.debutBlockY+b.largeur_block,x,1);

        if(okY){                //pas de découpage verticale
            //rangement des deux blocs
            blocs_ville.push_back(Block(b.debutBlockX, b.debutBlockY, b.largeur_block, x-b.debutBlockY));

            blocs_ville.push_back(Block(b.debutBlockX+x+1, b.debutBlockY, b.largeur_block, b.hauteur_block- x-1));

            decoupe = 1;

        }else{                  //découpage verticale

            y = position_route(b.debutBlockY,b.largeur_block);

            tracer_route(b.debutBlockX,b.debutBlockX+b.hauteur_block,y,0);

            //rangement des quatres blocs dans le tableau
            blocs_ville.push_back(Block(b.debutBlockX, b.debutBlockY, y-b.debutBlockY, x-b.debutBlockY));

            blocs_ville.push_back(Block(b.debutBlockX+x+1, b.debutBlockY, y-b.debutBlockY, b.hauteur_block- x-1));

            blocs_ville.push_back(Block(b.debutBlockX, b.debutBlockY+y+1, b.largeur_block - y-1, x-b.debutBlockY));

            blocs_ville.push_back(Block(b.debutBlockX +x+1, b.debutBlockY +y+1, b.largeur_block - y-1, b.hauteur_block -x-1));

            decoupe = 1;

        }
    }
    return decoupe;
}
void surface_ville::decouper_ville(){

        for(int i = 0; i < blocs_ville.size(); i++){
            cout<<"i = "<<i<<" taille tableau = "<<blocs_ville.size()<<endl;
            int decoupe = decouper_bloc(blocs_ville[i]);
            if(decoupe == 1){
                blocs_ville.erase(blocs_ville.begin()+i);
                i--;
                cout<<"i = "<<i<<" taille tableau = "<<blocs_ville.size()<<endl;

            }
        }
}
void surface_ville::afficher_blocs_ville(){
    for(int i = 0; i<blocs_ville.size();i++)
        blocs_ville[i].afficher_bloc();
}
