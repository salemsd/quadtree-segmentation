#ifndef __PARTICULE_H
#define __PARTICULE_H

/// @file particule.h
/// @brief Définitions de toutes les fonctions en rapport avec les particules

/**
 * @brief Structure d'une particule (point)
 * 
 */

typedef struct s_particule{
    double x; /* Abscisse */
    double y; /* Ordonnée */
    int vitesse;
    int dx;
    int dy;
} Particule;

// Variable pour vérifier l'arrêt du programme
extern int arret;

/**
 * @brief Genère un point au clic de l'utilisateur
 * 
 * @return Particule La particule crée
 */
Particule getParticuleOnClic();

/**
 * @brief Genère un point aléatoirement dans la fenêtre
 * 
 * @param taille_fenetre La taille de la fenêtre
 * @return Particule La particule crée
 */
Particule getParticule(int taille_fenetre);

#endif