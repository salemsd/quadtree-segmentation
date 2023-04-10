#include "graphique.h"

void dessineParticules(Particule *tabParticule, int nbParticule){

    for(int i = 0; i < nbParticule; i++){
        MLV_draw_filled_circle(tabParticule[i].x, tabParticule[i].y, 3, MLV_COLOR_BLACK);
    }

}