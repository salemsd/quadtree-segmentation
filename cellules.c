#include<stdio.h>
#include<stdlib.h>
#include "cellules.h"

ListeCell alloue_cellule(Particule *p){
    ListeCell tmp ;

    tmp = (NoeudCell *) malloc(sizeof(NoeudCell));

    if( tmp ){
        tmp->part = p;
        tmp->next = NULL;
    }

    return tmp;

}

ListeCell insere_queue(ListeCell * lst,Particule *p){
    ListeCell new_cell = alloue_cellule(p);

    if(new_cell){
        new_cell->next = *lst;
    }

    return new_cell;
}
