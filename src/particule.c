#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "particule.h"

int arret = 0;

Particule getParticuleOnClic(){
    double PERTURB = 0.0001/RAND_MAX;
    Particule P;
    int x = -10; int y = -10;
    
    while(x < 0 && y < 0 && !(arret)){
        MLV_wait_mouse_or_seconds(&x,&y, 1);
    }
    
    P.x = x + (rand()%2 ? +1. : -1.) * PERTURB * rand();
    P.y = y + (rand()%2 ? +1. : -1.) * PERTURB * rand();

    return P;
}

Particule getParticule(int taille_fenetre){
    double PERTURB = 0.0001/RAND_MAX;
    Particule P;
    
    P.x = (rand() % taille_fenetre) + (rand()%2 ? +1. : -1.) * PERTURB * rand();
    P.y = (rand() % taille_fenetre) + (rand()%2 ? +1. : -1.) * PERTURB * rand();
    
    return P;
}