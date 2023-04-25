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
        // int child_size = zone.W_H;
        tas[0].x1 = 0;
        tas[0].y1 = 0;
        tas[0].x2 = zone.W_H;
        tas[0].y2 = zone.W_H;
        
        for (int i = 0; i < nb_noeud; i++){
            tas[i].nbp = 0;
            tas[i].plist = NULL;
            
            // int x1_children[4] = {tas[i].x1, tas[i].x1 + child_size, tas[i].x1 + child_size, tas[i].x1};
            // int y1_children[4] = {tas[i].y1, tas[i].y1, tas[i].y1 + child_size, tas[i].y1 + child_size};

            // int x2_children[4] = {tas[i].x1 + child_size, tas[i].x2, tas[i].x2, tas[i].x1 + child_size};
            // int y2_children[4] = {tas[i].y1 + child_size, tas[i].y1 + child_size, tas[i].y2, tas[i].y2};
            
            tas[i].n1 = &(tas[4*i + 1]);
            tas[i].n2 = &(tas[4*i + 2]);
            tas[i].n3 = &(tas[4*i + 3]);
            tas[i].n4 = &(tas[4*i + 4]);

            // tas[i].n1->x1 = x1_children[0];
            // tas[i].n1->x2 = x2_children[0];
            // tas[i].n1->y1 = y1_children[0];
            // tas[i].n1->y2 = y2_children[0];

            // tas[i].n2->x1 = x1_children[1];
            // tas[i].n2->x2 = x2_children[1];
            // tas[i].n2->y1 = y1_children[1];
            // tas[i].n2->y2 = y2_children[1];
            
            // tas[i].n3->x1 = x1_children[2];
            // tas[i].n3->x2 = x2_children[2];
            // tas[i].n3->y1 = y1_children[2];
            // tas[i].n3->y2 = y2_children[2];

            // tas[i].n4->x1 = x1_children[3];
            // tas[i].n4->x2 = x2_children[3];
            // tas[i].n4->y1 = y1_children[3];
            // tas[i].n4->y2 = y2_children[3];
        }
    }

    return tas;
}

void insert_quadtree(QuadTree Q, ListeCell tab_plist, Zone *zone){
    // printf("1A\n");
    // ListeCell insere = alloue_cellule(&(zone->tab_part[zone->Np]));
    // (*Q)->plist = (insere != NULL) ? insere : (*Q)->plist;
        
    // (*Q)->nbp++;
    // printf("1B\n");

    gestion_insert_qt(Q, 0, zone->Np, tab_plist, zone);

    // printf("1C\n");

    return;
}

void gestion_insert_qt(QuadTree Q, int indice, int indice_tab, ListeCell tab_plist, Zone *zone) {
    /* Recherche du noeud où insérer la particule */
    // QuadTree node = find_node(*qt, p);
    // printf("nbp avant if %d\n",Q[indice].nbp);
    if(Q[indice].nbp + 1 < zone->Kp || Q[indice].x2 - Q[indice].x1 <= zone->wmin){
        // printf("indice apre if %d \n", indice);
        tab_plist[indice_tab].next = (Q[indice].plist);
        Q[indice].plist = &(tab_plist[indice_tab]);

        Q[indice].nbp++;
        printf("indice : %d , indice_tab %d , x : %g , y : %g , x1 : %d , x2 : %d, y1 : %d , y2 : %d\n", indice, indice_tab, Q[indice].plist->part->x, Q[indice].plist->part->y,Q[indice].x1,Q[indice].x2,Q[indice].y1,Q[indice].y2);
        // printf("nbp a l'interieur du if %d\n",Q[indice].nbp);
        // printf("nbp if %d\n",Q[indice].nbp);
        return ;
    }
    // ON PURGE
    else if (Q[indice].nbp + 1 == zone->Kp){
        Q[indice].nbp++;
        
        tab_plist[indice_tab].next = (Q[indice].plist);
        Q[indice].plist = &(tab_plist[indice_tab]);
        
        int i ;
        // printf("nbp %d\n",Q[indice].nbp);
        while(Q[indice].plist){
            i = Q[indice].plist->indice ;
            // printf(" x%g : y%g : i %d \n",tab_plist[i].part->x, tab_plist[i].part->y, i);
            // printf("indice avant while %d \n", indice);
            Q[indice].plist = Q[indice].plist->next;
            gestion_insert_qt(Q, indice, i, tab_plist, zone) ;
            // printf("indice apre while %d \n", indice);
        }
        Q[indice].plist = NULL ;
        // printf("rjfrfr\n");
    }
    // LE NOEUD A DEJA ETE PURGE
    else{
        // printf("nbp else %d\n",Q[indice].nbp);
        // printf("Avant le if , indice : %d\n", indice);
        // printf("Avant le if , x : %d\n", Q[indice].x1);
        // printf("test , indice : %d\n", indice);
        double xmid = ((Q[indice]).x1 + (Q[indice]).x2) / 2.0;
        double ymid = ((Q[indice]).y1 + (Q[indice]).y2) / 2.0;
        // printf("juste avant le if \n");

        // printf("ccccc\n");
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
        // printf("min child : %d \n",min_child);
        // printf("indice :%d \n",indice);   
        
        
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
        printf(" minchild : %d \n",min_child);
        gestion_insert_qt(Q, (4 * indice  + min_child), indice_tab ,tab_plist, zone);
        return ;
    }
}