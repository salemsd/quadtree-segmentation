#include "graphique.h"

void init_fenetre(int W_H){
    MLV_create_window("Quadtree_Segmentation", "Q", W_H, W_H);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_actualise_window();
}

MLV_Color couleur_transparente(MLV_Color couleur, int alpha){
    Uint8 r; Uint8 g; Uint8 b; Uint8 a;
    
    MLV_convert_color_to_rgba(couleur, &r, &g, &b, &a);
    
    MLV_Color couleurTransparente = MLV_convert_rgba_to_color(r, g, b, alpha);

    return couleurTransparente;
}

void gestion_clic(QuadTree *Q, Zone *zone){
    // CHANGER PLUS TARD POUR GERER LA FERMETURE DE LA FENETRE
    while(1){
        zone->tab_part[zone->Np] = getParticuleOnClic();
        insert_quadtree(Q, zone->tab_part[zone->Np], zone);
        zone->Np++;
        // QuadTree a = *Q;
        // while(a->plist == NULL){
        //     a = a->n1 ; 
        // }
        // if( a->plist != NULL){
        // for (; (a)->plist ; (a)->plist = (a)->plist->next){
        //     // printf("x1 %d y1 %d x2 %d y2 %d\n", (a)->n1->x1, (a)->y1, (a)->n1->x2, (a)->n1->y2);
        //     printf("x %g y %g\n", a->plist->part->x, a->plist->part->x);
        // }
        // }
        dessineZones(*Q);
        dessineParticules(zone);
    }
}

void dessineZones(QuadTree Q){
    for (int i = 0; i < 1000; i++){
       if (Q[i].plist != NULL){
            MLV_clear_window(MLV_COLOR_WHITE);

            printf("%d %d %d %d\n", Q[i].x1, Q[i].y1, Q[i].x2, Q[i].y2);

            MLV_draw_rectangle(Q[i].x1, Q[i].y1, Q[i].x2 - Q[i].x1, Q[i].y2 - Q[i].y1, MLV_COLOR_BLUE4);
            MLV_draw_filled_rectangle(Q[i].x1 - 1, Q[i].y1 - 1, Q[i].x2 - Q[i].x1, Q[i].y2 - Q[i].y1, couleur_transparente(MLV_COLOR_BLUE, 64));
            MLV_actualise_window();

            return;
       } 
    }
}

// void dessineZones(QuadTree Q){
//     if ((*Q).plist != NULL){            
//         MLV_clear_window(MLV_COLOR_WHITE);
    
//         printf("%d %d %d %d\n", Q->x1, Q->y1, Q->x2, Q->y2);
        
//         MLV_draw_rectangle(Q->x1, Q->y1, Q->x2 - Q->x1, Q->y2 - Q->y1, MLV_COLOR_BLUE4);
//         MLV_draw_filled_rectangle(Q->x1 - 1, Q->y1 - 1, Q->x2 - Q->x1, Q->y2 - Q->y1, couleur_transparente(MLV_COLOR_BLUE, 64));
//         MLV_actualise_window();

//         return;
//     }

//     dessineZones(Q->n1);
//     dessineZones(Q->n2);
//     dessineZones(Q->n3);
//     dessineZones(Q->n4);
// }

void dessineParticules(Zone *zone){

    for(int i = 0; i < zone->Np; i++){
        MLV_draw_filled_circle(zone->tab_part[i].x, zone->tab_part[i].y, 3, MLV_COLOR_BLACK);
    }

    MLV_actualise_window();
}