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
        int child_size = zone.W_H;
        tas[0].x1 = 0;
        tas[0].y1 = 0;
        tas[0].x2 = zone.W_H;
        tas[0].y2 = zone.W_H;
        
        for (int i = 0; i < nb_noeud; i++){
            tas[i].nbp = 0;
            tas[i].plist = NULL;
            
            if (child_size > 1){
                child_size = child_size / 2;
            }
            
            int x1_children[4] = {tas[i].x1, tas[i].x1 + child_size, tas[i].x1 + child_size, tas[i].x1};
            int y1_children[4] = {tas[i].y1, tas[i].y1, tas[i].y1 + child_size, tas[i].y1 + child_size};

            int x2_children[4] = {tas[i].x1 + child_size, tas[i].x2, tas[i].x2, tas[i].x1 + child_size};
            int y2_children[4] = {tas[i].y1 + child_size, tas[i].y1 + child_size, tas[i].y2, tas[i].y2};
            
            tas[i].n1 = &(tas[4*i + 1]);
            tas[i].n2 = &(tas[4*i + 2]);
            tas[i].n3 = &(tas[4*i + 3]);
            tas[i].n4 = &(tas[4*i + 4]);

            tas[i].n1->x1 = x1_children[0];
            tas[i].n1->x2 = x2_children[0];
            tas[i].n1->y1 = y1_children[0];
            tas[i].n1->y2 = y2_children[0];

            tas[i].n2->x1 = x1_children[1];
            tas[i].n2->x2 = x2_children[1];
            tas[i].n2->y1 = y1_children[1];
            tas[i].n2->y2 = y2_children[1];
            
            tas[i].n3->x1 = x1_children[2];
            tas[i].n3->x2 = x2_children[2];
            tas[i].n3->y1 = y1_children[2];
            tas[i].n3->y2 = y2_children[2];

            tas[i].n4->x1 = x1_children[3];
            tas[i].n4->x2 = x2_children[3];
            tas[i].n4->y1 = y1_children[3];
            tas[i].n4->y2 = y2_children[3];
        }
    }

    return tas;
}

// void insert_quadtree(QuadTree *Q, int indice, Zone *zone){
//     if ((*Q)->nbp <= zone->Kp || (*Q)->x2 - (*Q)->x1 == zone->wmin){
//         insere_plist(&((*Q)->plist), &(zone->tab_part[zone->Np]));
//         (*Q)->nbp++;
//     }
//     else if ((*Q)->nbp == zone->Kp){
//         insere_plist(&((*Q)->plist), &(zone->tab_part[zone->Np]));
//         (*Q)->nbp++;
//         insert_quadtree(Q, indice, zone);
//     }
//     else if ((*Q)->nbp > zone->Kp){
//         (*Q)->nbp++;
//         ListeCell parcours = (*Q)->plist;
        
//         double xmid = ((Q)[indice]->x1 + (Q)[indice]->x2) / 2.0;
//         double ymid = ((Q)[indice]->y1 + (Q)[indice]->y2) / 2.0;
//         for (; parcours; parcours = parcours->next){
//             double dist ;
//             int min_child = 1 ;

//             double min_dist = MAX(abs(parcours->part->x - ((Q)[indice]->x1 + xmid)/2), abs(parcours->part->y - ((Q)[indice]->y1 + ymid)/2));

//             dist = MAX(abs(parcours->part->x - ((Q)[indice]->x2 + xmid)/2), abs(parcours->part->y - (ymid + (Q)[indice]->y1)/2));

//             if(dist < min_dist){
//                 min_dist = dist ;
//                 min_child = 2 ; 
//             }

//             dist = MAX(abs(parcours->part->x - (xmid + (Q)[indice]->x2)/2), abs(parcours->part->y - (ymid + (Q)[indice]->y2)/2));

//             if(dist < min_dist){
//                 min_dist = dist ;
//                 min_child = 3 ;
//             }

//             dist = MAX(abs(parcours->part->x - (xmid + (Q)[indice]->x1)/2), abs(parcours->part->y - (ymid + (Q)[indice]->y2)/2));
//             if(dist < min_dist){
//                 min_dist = dist ;
//                 min_child = 4 ;
//             }

//             insert_quadtree(Q, 4 * indice + min_child, zone);
//         }
//     }
// }



// void insert_quadtree(QuadTree *Q, Particule p, Zone *zone, ListeCell prev){
//     printf("AQliii deg mezwaru\n");
//     ListeCell insere = insere_plist(&(*Q)->plist, &(zone->tab_part[zone->Np]));
//     // (*Q)->plist = (insere != NULL) ? insere : (*Q)->plist;
        
//     // (*Q)->nbp++;
//     printf("aqli avant n dina\n");

//     gestion_insert_qt(Q, 0 ,p, zone, insere);

//     printf("aqlida\n");

//     return;
// }

// void gestion_insert_qt(QuadTree *Q, int indice, Particule p, Zone *zone, ListeCell prev) {
//     /* Recherche du noeud où insérer la particule */
//     // QuadTree node = find_node(*qt, p);
//     printf("Avant le if \n");
//     Particule part_insere ;
    // double xmid = ((Q)[indice]->x1 + (Q)[indice]->x2) / 2.0;
    // double ymid = ((Q)[indice]->y1 + (Q)[indice]->y2) / 2.0;
//     printf("juste avant le if \n");
    
    

//     if((Q)[indice]->plist != NULL || (Q)[indice]->nbp == 0){
//         printf("avant le < \n");
//         if ( (Q)[indice]->nbp < zone->Kp) {
//             prev->next = (Q)[indice]->plist ;
//             Q[indice]->plist = prev;
//             Q[indice]->nbp ++ ;
//             printf("Apre le chainage \n");
//             return;
//         }
//         else{
//             printf("Aprses le else \n");
//             prev->next = (Q)[indice]->plist ;
//             (Q)[indice]->plist = NULL ;
//             ListeCell tmp = prev ;
//             for( ; tmp->next ; tmp = tmp->next){
//                 part_insere = *(prev->part) ;
//                 gestion_insert_qt(Q,indice,part_insere,zone,tmp);
//                 printf("prev\n");
           
//                 printf("apres prev\n");
//             }
//         }
//     }
//     else {
//         printf("Aprses le else2 \n");
//             double dist ;
//             int min_child = 1 ;

//             double min_dist = MAX(abs(p.x - ((Q)[indice]->x1 + xmid)/2), abs(p.y - ((Q)[indice]->y1 + ymid)/2));

//             dist = MAX(abs(p.x - ((Q)[indice]->x2 + xmid)/2), abs(p.y - (ymid + (Q)[indice]->y1)/2));

//             if(dist < min_dist){
//                 min_dist = dist ;
//                 min_child = 2 ; 
//             }

//             dist = MAX(abs(p.x - (xmid + (Q)[indice]->x2)/2), abs(p.y - (ymid + (Q)[indice]->y2)/2));

//             if(dist < min_dist){
//                 min_dist = dist ;
//                 min_child = 3 ;
//             }

//             dist = MAX(abs(p.x - (xmid + (Q)[indice]->x1)/2), abs(p.y - (ymid + (Q)[indice]->y2)/2));
//             if(dist < min_dist){
//                 min_dist = dist ;
//                 min_child = 4 ;
//             }
//             printf("min child : %d \n",min_child);
//             printf("indice :%d \n",indice);
            
//             gestion_insert_qt(Q, (4 * indice  + min_child), p, zone, prev);
//     }

// }


/** TAGI */

void insert_quadtree(QuadTree *Q, ListeCell tab_plist, Zone *zone){
    printf("AQliii deg mezwaru\n");
    // ListeCell insere = alloue_cellule(&(zone->tab_part[zone->Np]));
    // (*Q)->plist = (insere != NULL) ? insere : (*Q)->plist;
        
    // (*Q)->nbp++;
    printf("aqli avant n dina\n");

    gestion_insert_qt(Q, 0, tab_plist, zone);

    printf("aqlida\n");

    return;
}

void gestion_insert_qt(QuadTree *Q, int indice, ListeCell tab_plist, Zone *zone) {
    /* Recherche du noeud où insérer la particule */
    // QuadTree node = find_node(*qt, p);
    if(Q[indice]->nbp < zone->Kp || Q[indice]->x2 - Q[indice]->x1 == zone->wmin){ 
        tab_plist[zone->Np].next = (Q[indice]->plist);
        Q[indice]->plist = &(tab_plist[zone->Np]);

        Q[indice]->nbp++;
    }
    // ON PURGE
    else if (Q[indice]->nbp == zone->Kp){
        Q[indice]->nbp++;
        
        tab_plist[zone->Np].next = (Q[indice]->plist);
        Q[indice]->plist = &(tab_plist[zone->Np]);
        
        for()

        
    }
    // LE NOEUD A DEJA ETE PURGE
    else{
        printf("Avant le if , indice : %d\n", indice);
        printf("Avant le if , x : %d\n", Q[indice]->x1);
        printf("test , indice : %d\n", indice);
        double xmid = ((Q[indice])->x1 + (Q[indice])->x2) / 2.0;
        double ymid = ((Q[indice])->y1 + (Q[indice])->y2) / 2.0;
        printf("juste avant le if \n");

        printf("ccccc\n");
        double dist ;
        int min_child = 1 ;

        Particule p = zone->tab_part[zone->Np];
        double min_dist = MAX(abs(p.x - (Q[indice]->x1 + xmid)/2), abs(p.y - (Q[indice]->y1 + ymid)/2));

        dist = MAX(abs(p.x - (Q[indice]->x2 + xmid)/2), abs(p.y - (ymid + Q[indice]->y1)/2));

        if(dist < min_dist){
            min_dist = dist ;
            min_child = 2 ; 
        }

        dist = MAX(abs(p.x - (xmid + Q[indice]->x2)/2), abs(p.y - (ymid + Q[indice]->y2)/2));

        if(dist < min_dist){
            min_dist = dist ;
            min_child = 3 ;
        }

        dist = MAX(abs(p.x - (xmid + Q[indice]->x1)/2), abs(p.y - (ymid + Q[indice]->y2)/2));
        if(dist < min_dist){
            min_dist = dist ;
            min_child = 4 ;
        }
        printf("min child : %d \n",min_child);
        printf("indice :%d \n",indice);   
        
        
        gestion_insert_qt(Q, (4 * indice  + min_child), tab_plist, zone);
        return ;
    }
}






// void insert_quadtree(QuadTree *Q, Particule p, Zone *zone){
//     printf("AQliii deg mezwaru\n");
//     ListeCell insere = alloue_cellule(&(zone->tab_part[zone->Np]));
//     // (*Q)->plist = (insere != NULL) ? insere : (*Q)->plist;
        
//     // (*Q)->nbp++;
//     printf("aqli avant n dina\n");

//     gestion_insert_qt(Q, 0 ,p, zone, insere);

//     printf("aqlida\n");

//     return;
// }

// void gestion_insert_qt(QuadTree *Q, int indice, Particule p, Zone *zone, ListeCell insere) {
//     /* Recherche du noeud où insérer la particule */
//     // QuadTree node = find_node(*qt, p);
//     printf("Avant le if , indice : %d\n", indice);
//     printf("Avant le if , x : %d\n", Q[indice]->x1);
//     printf("test , indice : %d\n", indice);
//     double xmid = ((Q)[indice]->x1 + (Q)[indice]->x2) / 2.0;
//     double ymid = ((Q)[indice]->y1 + (Q)[indice]->y2) / 2.0;
//     printf("juste avant le if \n");
    
//     if(Q[indice]->nbp < zone->Kp ){
//         printf("aaaaa\n");
//         insere->next = Q[indice]->plist ;
//         Q[indice]->plist = insere ;
//         Q[indice]->nbp ++ ;
//         return ; 
//     }
//     // ON PURGE
//     else if (Q[indice]->nbp == zone->Kp){
//         printf("bbbbb\n");
//         Q[indice]->nbp++;
//         printf("Aprses le else \n");
//         insere->next = (Q)[indice]->plist ;
//         (Q)[indice]->plist = insere ;
        
//         // ListeCell parcours = Q[indice]->plist;
//         while (Q[indice]->plist){
//             NoeudCell *sauv_next = Q[indice]->plist->next;
//             NoeudCell *new_insere = Q[indice]->plist;
//             printf("avant new: %p | newnext: %p | parcours : %p | parcoursnext : %p\n", new_insere, new_insere->next, Q[indice]->plist, Q[indice]->plist->next);
//             new_insere->next = NULL;
//             printf("apres new: %p | newnext: %p | parcours : %p | parcoursnext : %p\n", new_insere, new_insere->next, Q[indice]->plist, Q[indice]->plist->next);
//             gestion_insert_qt(Q, indice, p, zone, new_insere);
            
//             Q[indice]->plist->next = sauv_next;
//         }
        
//         Q[indice]->plist = NULL;

//     }
//     // LE NOEUD A DEJA ETE PURGE
//     else{
//         printf("ccccc\n");
//         double dist ;
//         int min_child = 1 ;

//         double min_dist = MAX(abs(p.x - ((Q)[indice]->x1 + xmid)/2), abs(p.y - ((Q)[indice]->y1 + ymid)/2));

//         dist = MAX(abs(p.x - ((Q)[indice]->x2 + xmid)/2), abs(p.y - (ymid + (Q)[indice]->y1)/2));

//         if(dist < min_dist){
//             min_dist = dist ;
//             min_child = 2 ; 
//         }

//         dist = MAX(abs(p.x - (xmid + (Q)[indice]->x2)/2), abs(p.y - (ymid + (Q)[indice]->y2)/2));

//         if(dist < min_dist){
//             min_dist = dist ;
//             min_child = 3 ;
//         }

//         dist = MAX(abs(p.x - (xmid + (Q)[indice]->x1)/2), abs(p.y - (ymid + (Q)[indice]->y2)/2));
//         if(dist < min_dist){
//             min_dist = dist ;
//             min_child = 4 ;
//         }
//         printf("min child : %d \n",min_child);
//         printf("indice :%d \n",indice);   
//         gestion_insert_qt(Q, (4 * indice  + min_child), p, zone, insere);
//     }
// }















// void insert_quadtree(QuadTree *Q, Particule p, Zone *zone){
//     printf("AQliii deg mezwaru\n");
//     insere_plist(&((*Q)->plist), &(zone->tab_part[zone->Np]));

//     printf("aqli avant n dina\n");

//     gestion_insert_qt(Q, 0 ,p, zone, NULL);

//     printf("aqlida\n");

//     return;
// }

// void gestion_insert_qt(QuadTree *Q, int indice, Particule p, Zone *zone, ListeCell prev) {
//     /* Recherche du noeud où insérer la particule */
//     // QuadTree node = find_node(*qt, p);
//     // printf("Avant le if \n");
//     Particule part_insere ;
//     double xmid = ((Q)[indice]->x1 + (Q)[indice]->x2) / 2.0;
//     double ymid = ((Q)[indice]->y1 + (Q)[indice]->y2) / 2.0;
//     // printf("juste avant le if \n");
    
//     if(Q[indice]->nbp < zone->Kp ){
//         Q[indice]->nbp ++;
//         return ; 
//     }
//     else if( Q[indice]->plist == NULL && Q[indice]->nbp > zone->Kp){
//         double dist ;
//         int min_child = 1 ;

//         double min_dist = MAX(abs(p.x - ((Q)[indice]->x1 + xmid)/2), abs(p.y - ((Q)[indice]->y1 + ymid)/2));

//         dist = MAX(abs(p.x - ((Q)[indice]->x2 + xmid)/2), abs(p.y - (ymid + (Q)[indice]->y1)/2));

//         if(dist < min_dist){
//             min_dist = dist ;
//             min_child = 2 ; 
//         }

//         dist = MAX(abs(p.x - (xmid + (Q)[indice]->x2)/2), abs(p.y - (ymid + (Q)[indice]->y2)/2));

//         if(dist < min_dist){
//             min_dist = dist ;
//             min_child = 3 ;
//         }

//         dist = MAX(abs(p.x - (xmid + (Q)[indice]->x1)/2), abs(p.y - (ymid + (Q)[indice]->y2)/2));
//         if(dist < min_dist){
//             min_dist = dist ;
//             min_child = 4 ;
//         }
//         // printf("min child : %d \n",min_child);
//         // printf("indice :%d \n",indice);
            
//         gestion_insert_qt(Q, (4 * indice  + min_child), p, zone, NULL);

//     }
//     else if (Q[indice]->nbp <= zone->Kp && Q[indice]->plist != NULL){
//         printf("Aprses le else \n");
//         ListeCell parcours = Q[indice]->plist;
//         while(parcours != NULL){
//             parcours = parcours->next;
//             // printf(" tmp : %p : tmp->next : %p : prev : %p \n", tmp, tmp->next, prev);
            
//             gestion_insert_qt(Q, indice, *(parcours->part), zone, NULL);
//         }
//     }
// }