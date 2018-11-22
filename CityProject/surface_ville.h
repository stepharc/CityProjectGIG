/*      Gestion de la surface d'une ville
 *
 *  Le plan de notre ville sera représenté par une surface plane quadrillée de manière uniforme, chaque point du quadrillage mesurant 1*1.
 *  Tous les objets qui seront positionnées dans la villes seront alignées sur cette grille appellé "ville" et leurs dimensions dans le
 *  plans seront donc des entiers.
 *  Les dimensions du plan de la ville sont des attributs de la classe surface_ville: citySizeX et citySizeY.
 *  La ville devra être partitionné en ensemble de blocs.
 *  De ce fait, on commence découper la ville en quatre bloc en positionnant une route horizontale et une route verticale.
 *  Chaque blocs subira à son tour, de la même manière, une succession de subdivision en sous blocs. Ainsi, un blocs ne pourra plus être
 *  découpé quand chacune de ses dimensions est comprise entre minBlockSize et MaxBlockSize.
 *  L'ensemble des blocs de la ville sera stocké dans un tableau de block appelé "blocs_ville".
*/


#ifndef SURFACE_VILLE_H
#define SURFACE_VILLE_H


#include <iostream>
#include <vector>
#include "block.h"

using namespace std;
class surface_ville
{

public:
    //les méthodes de la classe
    //constructeur
    surface_ville(int x,int y);

    /*Pour l'instant teste juste les différents fonction de la classe*/
    void dessiner_ville();

    // retourne une position aléatoire pour tracer une route
    int position_route(int min, int max);

    //Tracer une route, horizontale si h=1 et verticale si h=0, à la position pos de "debut" à "fin"
    void tracer_route(int debut, int fin,int pos, int h);

    int decouper_bloc(Block b);
    /* cette fonction découpe un bloc b si nécessaire en deux ou quatre sous blocs.
     * Si la décomposition n'est pas nécessaire alors retoune 0 sinon retourne 1*/

    void decouper_ville();
    /* Dans cette fonction toutela ville est décomposé en blocs normalisés c'est à dire que chaque bloc
     * de la ville a ses deux disensions comprises entre minBlockSize et maxBlockSize*/

    //affichage de l'ensemble des blocs de la ville (ceux-ci de trouve dans letableau blocs_ville)
    void afficher_blocs_ville();


    //les attributs de la classe
    int citySizeX,citySizeY;
    static int minBlockSize,maxBlockSize;
    vector< vector<int> > ville;
    vector< Block > blocs_ville;

};

#endif // SURFACE_VILLE_H

