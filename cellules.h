#ifndef __CELLULES_H
#define __CELLULES_H

#include "particule.h"
#include "zone.h"

/**
 * @brief Structure d'une liste de cellules pointant vers des particules
 * 
 */
typedef struct s_plist{
    struct s_plist *next; /* Pointeur vers les cellules du même noeud */
    Particule *part; /* Pointeur vers une particule */
    int indice ;
    
} NoeudCell, *ListeCell;

NoeudCell *init_plist(Zone zone);

ListeCell alloue_cellule(Particule *p) ;

void insere_plist(ListeCell * lst,Particule *p) ;

#endif