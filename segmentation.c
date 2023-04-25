#include "graphique.h"
#include "particule.h"
#include "zone.h"
#include <time.h>

void test(){
    int mode = 0; /* Par défaut 0: Clic souris; 1: Aléatoire */
    srand(time(NULL));
    Zone zone;

    /* Clic souris */
    if (mode == 0){
        zone = init_zone(NMAX, 1024, 4, 5);
        ListeCell tab_plist = init_plist(zone, NMAX);
        QuadNode *Q = init_quadtree(zone);

        init_fenetre(zone.W_H);

        gestion_clic(Q, tab_plist, &zone);
    }
    /* Aléatoire */
    else{
        int nbPoint = 20;

        zone = init_zone(nbPoint, 1024, 4, 5);
        ListeCell tab_plist = init_plist(zone, nbPoint);
        QuadNode *Q = init_quadtree(zone);

        init_fenetre(zone.W_H);

        fill_tabs(&zone, tab_plist, nbPoint);
    }

    MLV_wait_seconds(100);

    free_tab_part(&zone);
    MLV_free_window();
}


int main(void){
    test();
}






