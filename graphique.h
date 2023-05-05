#ifndef __GRAPHIQUE_H
#define __GRAPHIQUE_H

#include <MLV/MLV_all.h>

#include "particule.h"
#include "quadtree.h"
#include "zone.h"

/**
 * @brief Initialise la fenêtre
 * 
 * @param W_H La taille de la fenêtre
 */
void init_fenetre(int W_H);

/**
 * @brief Renvoie l'équivalent transparent d'une couleur
 * 
 * @param couleur La couleur
 * @param alpha L'opacité
 * @return MLV_Color La couleur transparente
 */
MLV_Color couleur_transparente(MLV_Color couleur, int alpha);

/**
 * @brief Gère le fonctionnement du clic-souris
 * 
 * @param Q La racine du QuadTree
 * @param tab_plist La liste de cellules
 * @param zone L'adresse de la zone de travail
 */
void gestion_clic(QuadTree Q, ListeCell tab_plist, Zone *zone);

/**
 * @brief Gère le fonctionnement du mode aléatoire
 * 
 * @param Q La racine du QuadTree
 * @param tab_plist La liste de cellules
 * @param zone L'adresse de la zone de travail
 * @param nbPoint Le nombre de points
 */
void gestion_aleatoire(QuadTree Q, ListeCell tab_plist, Zone *zone, int nbPoint);

/**
 * @brief Vérifie si une des particules sur l'écran touche les bords de la fenêtre
 * 
 * @param zone La zone
 * @param i L'indice de la particule
 * @return int 0 si ne touche pas, 1 si touche
 */
int touche_bord(Zone zone, int i);

/**
 * @brief Dessine toutes les zones du QuadTree sur l'écran
 * 
 * @param Q La racine du QuadTree
 * @param zone La zone de travail
 * @param indice L'indice du fils actuel
 */
void dessineZones(QuadTree Q, Zone zone, int indice);

/**
 * @brief Dessine toutes les particules sur l'écran
 * 
 * @param zone La zone de travail
 */
void dessineParticules(Zone *zone);

/**
 * @brief Fonction qui s'éxécute lorsque on appuie sur le bouton fermer de la fenêtre
 * 
 * @param data Variable arrêt
 */
void exit_function(void *data);

#endif