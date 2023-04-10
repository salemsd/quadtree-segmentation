#ifndef __QUADTREE_H
#define __QUADTREE_H

#include "cellules.h"
#include "zone.h"

/**
 * @brief Structure d'un arbre quartenaire
 * 
 */
typedef struct s_quadtree{
    struct s_quadtree *n1, *n2, *n3, *n4; /* Pointeurs vers les 4 fils */
    int x1, y1, x2, y2; /* Info géométrique pour situer le noeud (Coin haut gauche et bas droite) */
    ListeCell plist; /* Une liste de cellules pointant vers les particules présentes dans le noeud */
    int nbp; /* Un entier inidiquant le nombre de particules dans le noeud */
    
} QuadNode, *QuadTree;

QuadTree init_quadtree(int x1, int y1, int x2, int y2, int nbp);

void insert_quadtree(QuadTree *Q, Particule p, Zone *zone, ListeCell prev);

void gestion_insert_qt(QuadTree *Q, Particule p, Zone *zone, ListeCell prev);

#endif