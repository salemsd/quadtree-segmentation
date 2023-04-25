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

void gestion_clic(QuadTree Q, ListeCell tab_plist, Zone *zone){
    // CHANGER PLUS TARD POUR GERER LA FERMETURE DE LA FENETRE
    while(1){
        zone->tab_part[zone->Np] = getParticuleOnClic();
        tab_plist[zone->Np].part = &(zone->tab_part[zone->Np]);
        tab_plist[zone->Np].indice = zone->Np;
        tab_plist[zone->Np].next = NULL;
        
        insert_quadtree(Q, tab_plist, zone);
        zone->Np++;
        
        QuadTree parcours = Q ;
        int indice = 0;

        // while(parcours[indice].plist == NULL ){
        //     printf("dans LE WHILE \n");
        //     indice = (4 * indice) + 1 ;

        //     parcours = parcours + indice;
        // }
        // printf("APRE LE WHILE \n");
        // for(; parcours[indice].plist; parcours[indice].plist = parcours[indice].plist->next){
        //     // printf("x%g y%g\n", parcours[indice].plist->part->x, parcours[indice].plist->part->y);
        //     printf("zebbi\n");
        // }
        // dessineZones(Q, 0);
        dessineParticules(zone);
    }
}

// void dessineZones(QuadTree Q){
//     for (int i = 0; i < 1000; i++){
//        if (Q[i].plist != NULL){
//             MLV_clear_window(MLV_COLOR_WHITE);

//             printf("%d %d %d %d\n", Q[i].x1, Q[i].y1, Q[i].x2, Q[i].y2);

//             MLV_draw_rectangle(Q[i].x1, Q[i].y1, Q[i].x2 - Q[i].x1, Q[i].y2 - Q[i].y1, MLV_COLOR_BLUE4);
//             MLV_draw_filled_rectangle(Q[i].x1 - 1, Q[i].y1 - 1, Q[i].x2 - Q[i].x1, Q[i].y2 - Q[i].y1, couleur_transparente(MLV_COLOR_BLUE, 64));
//             MLV_actualise_window();

//             return;
//        } 
//     }
// }

void dessineZones(QuadTree Q, int indice){
    if (Q[indice].plist != NULL && Q[indice].nbp > 0){
        MLV_clear_window(MLV_COLOR_WHITE);
    
        printf("%d %d %d %d\n", Q[indice].x1, Q[indice].y1, Q[indice].x2, Q[indice].y2);
        
        MLV_draw_rectangle(Q[indice].x1, Q[indice].y1, Q[indice].x2 - Q[indice].x1, Q[indice].y2 - Q[indice].y1, MLV_COLOR_BLUE4);
        MLV_draw_filled_rectangle(Q[indice].x1 - 1, Q[indice].y1 - 1, Q[indice].x2 - Q[indice].x1, Q[indice].y2 - Q[indice].y1, couleur_transparente(MLV_COLOR_BLUE, 64));
        MLV_actualise_window();

        return;
    }

    dessineZones(Q, 4 * indice + 1);
    dessineZones(Q, 4 * indice + 2);
    dessineZones(Q, 4 * indice + 3);
    dessineZones(Q, 4 * indice + 4);
}

void dessineParticules(Zone *zone){

    for(int i = 0; i < zone->Np; i++){
        MLV_draw_filled_circle(zone->tab_part[i].x, zone->tab_part[i].y, 3, MLV_COLOR_BLACK);
    }

    MLV_actualise_window();
}