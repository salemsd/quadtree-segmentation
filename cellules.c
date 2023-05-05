#include <stdio.h>
#include <stdlib.h>
#include "cellules.h"

NoeudCell *init_plist(Zone zone, int nbPoint){
    NoeudCell *new_plist = (NoeudCell *) calloc(nbPoint, sizeof(NoeudCell));

    return new_plist;
}

void fill_tabs(Zone *zone, ListeCell tab_plist, int nbPoint, int vitesse){
    for (int i = 0; i < nbPoint; i++){
        zone->tab_part[i] = getParticule(zone->W_H);
        zone->tab_part[i].vitesse = vitesse;
        zone->tab_part[i].dx = ((rand()%3) - 1) * zone->tab_part[i].vitesse;
        zone->tab_part[i].dy = ((rand()%3) - 1) * zone->tab_part[i].vitesse;
        
        tab_plist[i].part = &(zone->tab_part[i]);
        tab_plist[i].indice = i;
        tab_plist[i].next = NULL;
    }
}

void free_plist(ListeCell tab_plist){
    free(tab_plist);
    tab_plist = NULL;
    printf("Toutes les listes ont été libérées\n");
}
