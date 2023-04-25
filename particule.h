#ifndef __PARTICULE_H
#define __PARTICULE_H

#include "direction.h"

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

Particule getParticuleOnClic();

Particule getParticule(int taille_fenetre);

#endif