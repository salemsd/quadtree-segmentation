#ifndef __PARTICULE_H
#define __PARTICULE_H

/**
 * @brief Structure d'une particule (point)
 * 
 */

typedef struct s_particule{
    double x; /* Abscisse */
    double y; /* Ordonnée */

} Particule;

// extern Particule primaires[100000];

Particule getParticuleOnClic();

Particule getParticule(int taille_fenetre);

#endif