#include "graphique.h"
#include "particule.h"
#include "zone.h"
#include <time.h>

void test(){
    int mode = 1; /* Par défaut 0: Clic souris; 1: Aléatoire */
    srand(time(NULL));
    Zone zone;
    QuadNode *Q;
    ListeCell tab_plist;

    /* Clic souris */
    if (mode == 0){
        zone = init_zone(NMAX, 512, 8, 4);
        tab_plist = init_plist(zone, NMAX);
        Q = init_quadtree(zone);

        init_fenetre(zone.W_H);

        gestion_clic(Q, tab_plist, &zone);
    }
    /* Aléatoire */
    else{
        int nbPoint = 5;

        zone = init_zone(nbPoint, 512, 8, 4);
        tab_plist = init_plist(zone, nbPoint);
        Q = init_quadtree(zone);

        init_fenetre(zone.W_H);

        fill_tabs(&zone, tab_plist, nbPoint);
        gestion_aleatoire(Q, tab_plist, &zone, nbPoint);
    }

    MLV_wait_seconds(100);

    free_tab_part(&zone);
    MLV_free_window();
}


int main(void){
    test();
}






