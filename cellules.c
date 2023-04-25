#include <stdio.h>
#include <stdlib.h>
#include "cellules.h"

NoeudCell *init_plist(Zone zone){
    NoeudCell *new_plist = (NoeudCell *) calloc(NMAX, sizeof(NoeudCell));

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
