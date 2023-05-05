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

NoeudCell *init_plist(Zone zone, int nbPoint);

ListeCell alloue_cellule(Particule *p) ;

void insere_plist(ListeCell * lst,Particule *p) ;

void fill_tabs(Zone *zone, ListeCell tab_plist,int nbPoint, int vitesse);

void free_plist(ListeCell tab_plist);

#endif