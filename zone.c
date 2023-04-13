#include <stdlib.h>

#include "zone.h"

Zone init_zone(int W_H, int wmin, int Kp){
    Zone zone;
    
    zone.Np = 0;
    zone.Kp = Kp;
    zone.W_H = W_H;
    zone.wmin = wmin;
    zone.tab_part = (Particule *) malloc(NMAX * sizeof(Particule));

    return zone;
}

void free_tab_part(Zone *zone){
    free(zone->tab_part);
    zone->tab_part = NULL;
}

void init_tab_particule_rand(Zone *zone){
    for(int i = 0 ; i < zone->Np; i++){
        zone->tab_part[i] = getParticule(zone->W_H);
    }
}