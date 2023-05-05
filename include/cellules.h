#ifndef __CELLULES_H
#define __CELLULES_H

#include "particule.h"
#include "zone.h"

/// @file cellules.h
/// @brief Définitions de toutes les fonctions en rapport avec les cellules

/**
 * @brief Structure d'une liste de cellules pointant vers des particules
 * 
 */
typedef struct s_plist{
    struct s_plist *next; /* Pointeur vers les cellules du même noeud */
    Particule *part; /* Pointeur vers une particule */
    int indice ;
    
} NoeudCell, *ListeCell;

/**
 * @brief Initialise une liste de cellules
 * 
 * @param zone La zone
 * @param nbPoint Le nombre de points à allouer
 * @return NoeudCell*: La liste
 */
NoeudCell *init_plist(Zone zone, int nbPoint);

/**
 * @brief Remplis le tableau de particules et pointe chaque cellule de la liste vers les élements du tableau
 * 
 * @param zone La zone
 * @param tab_plist Le tableau de cellules
 * @param nbPoint Le nombre de points
 * @param vitesse La vitesse des points
 */
void fill_tabs(Zone *zone, ListeCell tab_plist,int nbPoint, int vitesse);

/**
 * @brief Libère la liste de cellules
 * 
 * @param tab_plist La liste à libérer
 */
void free_plist(ListeCell tab_plist);

#endif