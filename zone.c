#include "zone.h"

void init_tab_particule_rand(Zone *zone){
    for(int i = 0 ; i < zone->Np ; i++){
        zone->tab_part[i] = getParticule(zone->W_H);
    }
}