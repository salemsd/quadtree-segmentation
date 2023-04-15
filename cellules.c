#include<stdio.h>
#include<stdlib.h>
#include "cellules.h"

NoeudCell *init_plist(Zone zone){
    NoeudCell *new_plist = (NoeudCell *) malloc(NMAX * sizeof(NoeudCell));
    if( new_plist){
        for(int i = 0 ; i < NMAX; i++){
            new_plist[i].part = &(zone.tab_part[i]);
            new_plist[i].next = NULL;
        }
    }

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
