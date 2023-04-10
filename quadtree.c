#include <stdlib.h>
#include <stdio.h>

#include "quadtree.h"
#include "cellules.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

QuadTree init_quadtree(int x1, int y1, int x2, int y2, int nbp){
    QuadTree new_tree = (QuadTree) malloc(sizeof(QuadNode));
    if( new_tree){
        new_tree->n1 = new_tree->n2 = new_tree->n3 = new_tree->n4 = NULL;
        new_tree->plist = NULL;
        
        new_tree->nbp = nbp;
        new_tree->x1 = x1;
        new_tree->y1 = y1;
        new_tree->x2 = x2;
        new_tree->y2 = y2;
    }
    
    return new_tree ;
}

void insert_quadtree(QuadTree *Q, Particule p, Zone *zone, ListeCell prev){
    ListeCell insere = insere_plist(&(*Q)->plist, &(zone->tab_part[zone->curlen]));
    (*Q)->plist = (insere != NULL) ? insere : (*Q)->plist;
        
    (*Q)->nbp++;

    gestion_insert_qt(Q, p, zone, ((*Q)->plist));

    return;
}

void gestion_insert_qt(QuadTree *Q, Particule p, Zone *zone, ListeCell prev) {
    /* Recherche du noeud où insérer la particule */
    // QuadTree node = find_node(*qt, p);

    Particule part_insere ;
    double xmid = ((*Q)->x1 + (*Q)->x2) / 2.0;
    double ymid = ((*Q)->y1 + (*Q)->y2) / 2.0;


    if ((*Q)->nbp - 1 < zone->Kp) {
        (*Q)->plist = prev;

        return;
    }
    else {
        ListeCell insere = insere_plist(&(*Q)->plist, &(zone->tab_part[zone->curlen]));
        (*Q)->plist = (insere != NULL) ? insere : (*Q)->plist;
        
        (*Q)->nbp++;
        for(int i = 0; i < (*Q)->nbp; i++){
            part_insere = *((*Q)->plist->part);
            printf("point: %g %g\n", part_insere.x, part_insere.y);
        
        // }
            double dist ;
            int min_child = 1 ;

            double min_dist = MAX(abs(part_insere.x - ((*Q)->x1 + xmid)/2), abs(part_insere.y - ((*Q)->y1 + ymid)/2));

            dist = MAX(abs(part_insere.x - ((*Q)->x2 + xmid)/2), abs(part_insere.y - (ymid + (*Q)->y1)/2));

            if(dist < min_dist){
                min_dist = dist ;
                min_child = 2 ; 
            }

            dist = MAX(abs(part_insere.x - (xmid + (*Q)->x2)/2), abs(part_insere.y - (ymid + (*Q)->y2)/2));

            if(dist < min_dist){
                min_dist = dist ;
                min_child = 3 ;
            }

            dist = MAX(abs(part_insere.x - (xmid + (*Q)->x1)/2), abs(part_insere.y - (ymid + (*Q)->y2)/2));
            if(dist < min_dist){
                min_dist = dist ;
                min_child = 4 ;
            }

            // printf("else: %d\n", (*Q)->nbp);
            switch (min_child) {
                case 1:
                    if (!(*Q)->n1) {
                        (*Q)->n1 = init_quadtree((*Q)->x1, (*Q)->y1, xmid, ymid , 0);
                    }
                    gestion_insert_qt(&((*Q)->n1), part_insere, zone, (*Q)->plist);
                    
                    break;
                case 2:
                    if (!(*Q)->n2) {
                        (*Q)->n2 = init_quadtree(xmid, (*Q)->y1, (*Q)->x2, ymid, 0);
                    }
                    gestion_insert_qt(&((*Q)->n2), part_insere, zone, (*Q)->plist);
                    
                    break;
                case 3:
                    if (!(*Q)->n3) {
                        (*Q)->n3 = init_quadtree(xmid, ymid, (*Q)->x2, (*Q)->y2, 0);
                    }
                    gestion_insert_qt(&((*Q)->n3), part_insere, zone, (*Q)->plist);
                    
                    break;
                case 4:
                    if (!(*Q)->n4) {
                        (*Q)->n4 = init_quadtree((*Q)->x1, ymid, xmid, (*Q)->y2, 0 );
                    }
                    gestion_insert_qt(&((*Q)->n4), part_insere, zone, (*Q)->plist);
                    
                    break;
            }
            
            (*Q)->plist = (*Q)->plist->next;
        }      
    }
}


