#ifndef __QUADTREE_H
#define __QUADTREE_H

#include "cellules.h"
#include "zone.h"

/// @file quadtree.h
/// @brief Définitions de toutes les fonctions en rapport avec le quadtree

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

/**
 * @brief Alloue un QuadTree jusqu'à sa capacité maximale
 * 
 * @param zone La zone initiale
 * @return QuadNode* L'adresse du QuadTree alloué
 */
QuadNode *init_quadtree(Zone zone);

/**
 * @brief Insère un nouveau point dans le QuadTree
 * 
 * @param Q La racine du QuadTree
 * @param tab_plist La liste de cellules
 * @param zone L'adresse de la zone
 */
void insert_quadtree(QuadTree Q, ListeCell tab_plist, Zone *zone);

/**
 * @brief Calcule où un nouveau point doit être inséré dans le QuadTree et gère la purge
 * 
 * @param Q La racine du QuadTree
 * @param indice L'indice du fils à traiter actuellement
 * @param indice_tab L'indice du nouveau point dans le tableau
 * @param tab_plist La liste de cellules
 * @param zone L'adresse de la zone
 */
void gestion_insert_qt(QuadTree Q, int indice, int indice_tab, ListeCell tab_plist, Zone *zone);

/**
 * @brief Réinitialise un QuadTree à son état initial
 * 
 * @param Q La racine du QuadTree
 * @param zone La zone
 * @param indice L'indice du fils actuel à traiter
 */
void reset_quadtree(QuadTree Q, Zone zone, int indice);

/**
 * @brief Libère un QuadTree
 * 
 * @param Q La racine du QuadTree
 * @param zone La zone
 */
void free_quadtree(QuadTree Q, Zone zone);

#endif