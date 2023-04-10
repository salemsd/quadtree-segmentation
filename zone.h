#ifndef __ZONE_H
#define __ZONE_H

#include "particule.h"

/**
 * @brief Structure de la zone de travail, avec ses paramètres
 * 
 */
typedef struct s_zone{
    int W_H; /* Dimensions de la zone (carré) */
    int wmin; /* La taille minimale d'une feuille (puissance de 4) */
    int Np; /* Nombre de particules */
    int Kp; /* Le nombre max de particules contenu dans une feuille */
    Particule tab_part[10000000];
} Zone;


void init_tab_particule_rand(Zone *zone);

#endif