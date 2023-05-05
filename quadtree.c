#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "quadtree.h"
#include "cellules.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

QuadNode *init_quadtree(Zone zone){
    int h = log2(zone.W_H);
    int nb_noeud =  (pow(4, h + 1) - 1) / 3;
    
    QuadNode *tas = (QuadNode *) malloc(nb_noeud * sizeof(QuadNode));
    
    if(tas){
        tas[0].x1 = 0;
        tas[0].y1 = 0;
        tas[0].x2 = zone.W_H;
        tas[0].y2 = zone.W_H;
        
        for (int i = 0; i < nb_noeud; i++){
            tas[i].nbp = 0;
            tas[i].plist = NULL;
            
            tas[i].n1 = &(tas[4*i + 1]);
            tas[i].n2 = &(tas[4*i + 2]);
            tas[i].n3 = &(tas[4*i + 3]);
            tas[i].n4 = &(tas[4*i + 4]);
        }
    }

    return tas;
}

void insert_quadtree(QuadTree Q, ListeCell tab_plist, Zone *zone){
    gestion_insert_qt(Q, 0, zone->Np, tab_plist, zone);

    return;
}

void gestion_insert_qt(QuadTree Q, int indice, int indice_tab, ListeCell tab_plist, Zone *zone) {
    if(Q[indice].nbp + 1 < zone->Kp || Q[indice].x2 - Q[indice].x1 <= zone->wmin){
        tab_plist[indice_tab].next = (Q[indice].plist);
        Q[indice].plist = &(tab_plist[indice_tab]);

        Q[indice].nbp++;
        return ;
    }
    // ON PURGE
    else if (Q[indice].nbp + 1 == zone->Kp){
        Q[indice].nbp++;
        
        tab_plist[indice_tab].next = (Q[indice].plist);
        Q[indice].plist = &(tab_plist[indice_tab]);
        
        int i ;
        while(Q[indice].plist){
            i = Q[indice].plist->indice ;
            Q[indice].plist = Q[indice].plist->next;
            gestion_insert_qt(Q, indice, i, tab_plist, zone) ;
        }
    }
    // LE NOEUD A DEJA ETE PURGE
    else{

        double xmid = ((Q[indice]).x1 + (Q[indice]).x2) / 2.0;
        double ymid = ((Q[indice]).y1 + (Q[indice]).y2) / 2.0;

        double dist ;
        int min_child = 1 ;

        Particule p = zone->tab_part[indice_tab];
        double min_dist = MAX(abs(p.x - (Q[indice].x1 + xmid)/2), abs(p.y - (Q[indice].y1 + ymid)/2));

        dist = MAX(abs(p.x - (Q[indice].x2 + xmid)/2), abs(p.y - (ymid + Q[indice].y1)/2));

        if(dist < min_dist){
            min_dist = dist ;
            min_child = 2 ; 
        }

        dist = MAX(abs(p.x - (xmid + Q[indice].x2)/2), abs(p.y - (ymid + Q[indice].y2)/2));

        if(dist < min_dist){
            min_dist = dist ;
            min_child = 3 ;
        }

        dist = MAX(abs(p.x - (xmid + Q[indice].x1)/2), abs(p.y - (ymid + Q[indice].y2)/2));
        if(dist < min_dist){
            min_dist = dist ;
            min_child = 4 ;
        }
        
        switch (min_child) {
            case 1:
                Q[4 * indice + min_child].x1 = Q[indice].x1;
                Q[4 * indice + min_child].y1 = Q[indice].y1;
                Q[4 * indice + min_child].x2 = xmid;
                Q[4 * indice + min_child].y2 = ymid;
                break;
            case 2:
                Q[4 * indice + min_child].x1 = xmid;
                Q[4 * indice + min_child].y1 = Q[indice].y1;
                Q[4 * indice + min_child].x2 = Q[indice].x2;
                Q[4 * indice + min_child].y2 = ymid;
                break;
            case 4:
                Q[4 * indice + min_child].x1 = Q[indice].x1;
                Q[4 * indice + min_child].y1 = ymid;
                Q[4 * indice + min_child].x2 = xmid;
                Q[4 * indice + min_child].y2 = Q[indice].y2;
                break;
            case 3:
                Q[4 * indice + min_child].x1 = xmid;
                Q[4 * indice + min_child].y1 = ymid;
                Q[4 * indice + min_child].x2 = Q[indice].x2;
                Q[4 * indice + min_child].y2 = Q[indice].y2;
                break;
        }

        gestion_insert_qt(Q, (4 * indice  + min_child), indice_tab ,tab_plist, zone);
        
        return ;
    }
}

void reset_quadtree(QuadTree Q, Zone zone, int indice){
    Q[indice].nbp = 0;
    
    if ((Q[indice].plist != NULL) || Q[indice].x2 - Q[indice].x1 <= zone.wmin){
        while(Q[indice].plist){
            ListeCell reset = Q[indice].plist;
            Q[indice].plist = Q[indice].plist->next;
            reset->next = NULL;
        }
        
        Q[indice].plist = NULL;
        
        return;
    }
    else if (Q[indice].plist == NULL){
        reset_quadtree(Q, zone, 4 * indice + 1);
        reset_quadtree(Q, zone, 4 * indice + 2);
        reset_quadtree(Q, zone, 4 * indice + 3);
        reset_quadtree(Q, zone, 4 * indice + 4);
    }
}


void free_quadtree(QuadTree Q, Zone zone){
    free(Q);
    Q = NULL;
    printf("Tous les noeuds du QuadTree ont été libérées\n");
}