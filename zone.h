#ifndef __ZONE_H
#define __ZONE_H

#include "particule.h"

#define NMAX 1000000000
/**
 * @brief Structure de la zone de travail, avec ses paramètres
 * 
 */
typedef struct s_zone{
    int W_H; /* Dimensions de la zone (carré) */
    int wmin; /* La taille minimale d'une feuille (puissance de 4) */
    int Np; /* Nombre de particules */
    int Kp; /* Le nombre max de particules contenu dans une feuille */
    Particule *tab_part;
} Zone;

/**
 * @brief Initialise la zone de travail, alloue le tableau de points
 * 
 * @param nbPoint Nombre de points
 * @param W_H La taille de la zone initiale
 * @param wmin La taille minimale d'une feuille (arrêt de subdivision)
 * @param Kp Le nombre max de particules contenus dans une feuille
 * @return Zone La zone crée
 */
Zone init_zone(int nbPoint, int W_H, int wmin, int Kp);

/**
 * @brief Libère le tableau de points
 * 
 * @param zone L'adresse de la zone de travail
 */
void free_tab_part(Zone *zone);

/**
 * @brief Initialise le tableau de points aléatoirement
 * 
 * @param zone L'adresse de la zone de travail
 */
void init_tab_particule_rand(Zone *zone);

/**
 * @brief Récupère les informations de la zone en demandant à l'utilisateur
 * 
 * @param mode Mode d'éxécution: 0: Clic-souris, 1: Aléatoire
 * @param W_H Adresse de la taille de la fenêtre
 * @param wmin Adresse de la taille minimale d'une feuille
 * @param Kp Adresse du nombre max de particules dans une feuille
 * @param nbPoint Adresse du nb de points
 * @param vitesse Adresse de la vitesse d'une particule
 */
void get_zone_data(int mode, int *W_H, int *wmin, int *Kp, int *nbPoint, int *vitesse);

#endif