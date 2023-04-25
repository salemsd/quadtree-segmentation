#include <stdio.h>
#include <stdlib.h>
#include "cellules.h"

NoeudCell *init_plist(Zone zone, int nbPoint){
    NoeudCell *new_plist = (NoeudCell *) calloc(nbPoint, sizeof(NoeudCell));

    return new_plist;
}

ListeCell alloue_cellule(Particule *p){
    ListeCell tmp ;

    tmp = (NoeudCell *) malloc(sizeof(NoeudCell));

    if(tmp){
        tmp->part = p;
        tmp->next = NULL;
    }

    return tmp;

}

void insere_plist(ListeCell *lst, Particule *p){
    ListeCell insert = alloue_cellule(p);

    insert->next = *lst;
    insert->part = p;
    *lst = insert;
}

void fill_tabs(Zone *zone, ListeCell tab_plist, int nbPoint){
    for (int i = 0; i < nbPoint; i++){
        zone->tab_part[i] = getParticule(zone->W_H);
        zone->tab_part[i].vitesse = 1;
        zone->tab_part[i].dx = ((rand()%3) - 1) * zone->tab_part[i].vitesse;
        zone->tab_part[i].dy = ((rand()%3) - 1) * zone->tab_part[i].vitesse;
        printf("aaaaa %d %d\n", zone->tab_part[i].dx, zone->tab_part[i].dy);
        
        tab_plist[i].part = &(zone->tab_part[i]);
        tab_plist[i].indice = i;
        tab_plist[i].next = NULL;
    }
}

void reset_plist(ListeCell tab_plist, int nbPoint){
    for (int i = 0; i < nbPoint; i++){
        tab_plist[i].next = NULL;
    }
}
