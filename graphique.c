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
    while(!arret){
        zone->tab_part[zone->Np] = getParticuleOnClic();
        tab_plist[zone->Np].part = &(zone->tab_part[zone->Np]);
        tab_plist[zone->Np].indice = zone->Np;
        tab_plist[zone->Np].next = NULL;
        
        insert_quadtree(Q, tab_plist, zone);
        zone->Np++;

        MLV_clear_window(MLV_COLOR_WHITE);
        dessineZones(Q, *zone, 0);
        dessineParticules(zone);
    }
}

void gestion_aleatoire(QuadTree Q, ListeCell tab_plist, Zone *zone, int nbPoint){
    while(!arret){
        zone->Np = 0;
        for(int i = 0; i < nbPoint ; i++){
            insert_quadtree(Q, tab_plist, zone);
            zone->Np++;

            // Bord gauche et droit
            if (touche_bord(*zone, i) == 1) {
                zone->tab_part[i].dx = -zone->tab_part[i].dx;
            }
            // Bord haut et bas
            else if (touche_bord(*zone, i) == 2) {
                zone->tab_part[i].dy = -zone->tab_part[i].dy;
            }
            // Bord gauche et doit + bord haut et bas
            else if (touche_bord(*zone, i) == 3){
                zone->tab_part[i].dx = -zone->tab_part[i].dx;
                zone->tab_part[i].dy = -zone->tab_part[i].dy;
            }

            zone->tab_part[i].x += zone->tab_part[i].dx;
            zone->tab_part[i].y += zone->tab_part[i].dy;
        }

        MLV_clear_window(MLV_COLOR_WHITE);
        dessineZones(Q, *zone, 0);
        dessineParticules(zone);
        MLV_wait_milliseconds(25);

        reset_quadtree(Q, *zone, 0);
    }
}

int touche_bord(Zone zone, int i){
    int x_part = zone.tab_part[i].x;
    int y_part = zone.tab_part[i].y;
    
    // Touche bord droit ou gauche ET haut ou bas
    if ((x_part >= (zone.W_H - 1) || x_part <= 0) && (y_part >= (zone.W_H - 1) || y_part <= 0)){
        return 3;
    }
    // Touche bord droit ou gauche
    if (x_part >= (zone.W_H - 1) || x_part <= 0){
        return 1;
    }
    // Touche bord haut ou bas
    if (y_part >= (zone.W_H - 1) || y_part <= 0){
        return 2;
    }

    return 0;
}

void dessineZones(QuadTree Q, Zone zone, int indice){
    if ((Q[indice].nbp < zone.Kp && Q[indice].plist != NULL) || Q[indice].x2 - Q[indice].x1 <= zone.wmin){
        MLV_draw_rectangle(Q[indice].x1, Q[indice].y1, Q[indice].x2 - Q[indice].x1, Q[indice].y2 - Q[indice].y1, MLV_COLOR_BLUE4);
        MLV_draw_filled_rectangle(Q[indice].x1 - 1, Q[indice].y1 - 1, Q[indice].x2 - Q[indice].x1, Q[indice].y2 - Q[indice].y1, couleur_transparente(MLV_COLOR_BLUE, 64));

        return;
    }
    else if (Q[indice].nbp >= zone.Kp && Q[indice].plist == NULL){
        dessineZones(Q, zone, 4 * indice + 1);
        dessineZones(Q, zone, 4 * indice + 2);
        dessineZones(Q, zone, 4 * indice + 3);
        dessineZones(Q, zone, 4 * indice + 4);
    }
}

void dessineParticules(Zone *zone){

    for(int i = 0; i < zone->Np; i++){
        MLV_draw_filled_circle(zone->tab_part[i].x, zone->tab_part[i].y, 3, MLV_COLOR_BLACK);
    }

    MLV_actualise_window();
}

void exit_function(void *data){
    int* arret = (int*) data;
    *arret = 1;
}