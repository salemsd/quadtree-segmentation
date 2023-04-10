#include "graphique.h"

void init_fenetre(int W_H){
    MLV_create_window("Quadtree_Segmentation", "Q", W_H, W_H);
    MLV_clear_window(MLV_COLOR_WHITE);
}

MLV_Color couleur_transparente(MLV_Color couleur, int alpha){
    Uint8 r; Uint8 g; Uint8 b; Uint8 a;
    
    MLV_convert_color_to_rgba(couleur, &r, &g, &b, &a);
    
    MLV_Color couleurTransparente = MLV_convert_rgba_to_color(r, g, b, alpha);

    return couleurTransparente;
}

void dessineZones(QuadTree Q){
    if (!Q){
        return;
    }

    MLV_draw_rectangle(Q->x1, Q->y1, Q->x2 - Q->x1, Q->y2 - Q->y1, MLV_COLOR_ALICEBLUE);
    MLV_draw_filled_rectangle(Q->x1, Q->y1, Q->x2 - Q->x1, Q->y2 - Q->y1, couleur_transparente(MLV_COLOR_ALICEBLUE, 50));
    MLV_actualise_window();

    dessineZones(Q->n1);
    dessineZones(Q->n2);
    dessineZones(Q->n3);
    dessineZones(Q->n4);
}

void dessineParticules(Zone *zone){

    for(int i = 0; i < zone->Np; i++){
        MLV_draw_filled_circle(zone->tab_part[i].x, zone->tab_part[i].y, 3, MLV_COLOR_BLACK);
    }

    MLV_actualise_window();
}