t#include <stdio.h>
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
        zone->tab_part[zone->Np] = getParticule(zone->W_H);
        tab_plist[zone->Np].part = &(zone->tab_part[zone->Np]);
        tab_plist[zone->Np].indice = zone->Np;
        tab_plist[zone->Np].next = NULL;

        zone->Np++;
    }
}
